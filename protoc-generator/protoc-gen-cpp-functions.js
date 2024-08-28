#!/usr/bin/env node

const protobuf = require('protobufjs');
const fs = require('fs');
const path = require('path');

async function loadProtoFiles() {
  const protoDir = path.resolve(__dirname, 'protos');
  const descriptorPath = path.resolve(protoDir, 'google', 'protobuf', 'descriptor.proto');
  const pluginPath = path.resolve(protoDir, 'plugin.proto');

  const root = new protobuf.Root();
  await root.load(descriptorPath, { keepCase: true });
  await root.load(pluginPath, { keepCase: true });
  return root;
}

const lowercaseFirst = (str) => str.charAt(0).toLowerCase() + str.slice(1);

function extractComments(filePath) {
  const content = fs.readFileSync("../proto/" + filePath, 'utf8');
  const lines = content.split('\n');
  const comments = {};
  let currentComment = [];
  let isInComment = false;
  let currentMethod = null;

  lines.forEach((line) => {
    const trimmedLine = line.trim();
    if (trimmedLine.startsWith('/*')) {
      isInComment = true;
      currentComment.push(trimmedLine.slice(2).trim());
    } else if (trimmedLine.endsWith('*/')) {
      isInComment = false;
      currentComment.push(trimmedLine.slice(0, -2).trim());
    } else if (isInComment) {
      currentComment.push(trimmedLine);
    } else if (trimmedLine.startsWith('rpc ')) {
      currentMethod = trimmedLine.split(' ')[1];
      if (currentComment.length > 0) {
        comments[currentMethod] = currentComment.join('\n');
        currentComment = [];
      }
    } else {
      currentComment = [];
    }
  });

  return comments;
}

function generateCode(request) {
  const cppResult = [];
  const rnResult = [];
  const cppHeaderResult = [];

  const comments = {};
  request.proto_file.forEach((protoFile) => {
    const filePath = protoFile.name;
    Object.assign(comments, extractComments(filePath));
  });

  request.proto_file.forEach((protoFile) => {
    if (protoFile.service && Array.isArray(protoFile.service)) {
      protoFile.service.forEach((service) => {
        const serviceName = service.name;

        if (service.method && Array.isArray(service.method)) {
          service.method.forEach((method) => {

            let methodName = method.name;
            if (serviceName === 'Lightning' || serviceName === 'WalletUnlocker' || serviceName === 'State') {
              methodName = lowercaseFirst(methodName);
            } else {
              methodName = lowercaseFirst(serviceName + methodName);
            }
            const inputType = method.input_type.split('.').pop();
            const outputType = method.output_type.split('.').pop();
            const isServerStreaming = method.server_streaming;
            const isClientStreaming = method.client_streaming;

            // Get comment from extracted comments
            const comment = comments[method.name]
              ? `/**\n   * ${comments[method.name].split('\n').join('\n   * ')}\n   */`
              : '';


            let cppMethodDeclaration;
            let cppMethodImplementation;
            let rnMethodSpec;

            if (!isServerStreaming && !isClientStreaming) {
              // Unary RPC
              cppMethodDeclaration = `  facebook::react::AsyncPromise2<std::string> ${methodName}(jsi::Runtime &rt, jsi::String data);`;
              cppMethodImplementation = `
facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::${methodName}(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::${methodName}(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}`;
              rnMethodSpec = `  ${comment}\n  ${methodName}(data: ProtobufBase64): Promise<ProtobufBase64>;`;
            } else if (isServerStreaming && !isClientStreaming) {
              // Server streaming RPC
              cppMethodDeclaration = `  facebook::jsi::Function ${methodName}(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);`;
              cppMethodImplementation = `
facebook::jsi::Function NativeSampleModuleCxx::${methodName}(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
    auto sharedOnResponse = std::make_shared<AsyncCallback2<std::string>>(std::move(onResponse));
    auto sharedOnError = std::make_shared<AsyncCallback2<std::string>>(std::move(onError));
    uint64_t callbackId = CallbackKeeper::getInstance().addCallbacks(sharedOnResponse, sharedOnError);

    CRecvStream recvStream = {
        .onResponse = &callbackOnResponseStatic,
        .onError = &callbackOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(callbackId),
        .errorContext = reinterpret_cast<void*>(callbackId),
    };
    char *emptyArray = NULL;
    int length = 0;
    ::${methodName}(emptyArray, length, recvStream);

    auto unsubscribeFunc = jsi::Function::createFromHostFunction(
        rt,
        jsi::PropNameID::forAscii(rt, "unsubscribe"),
        0,
        [callbackId](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
            CallbackKeeper::getInstance().removeCallbacks(callbackId);
            return jsi::Value::undefined();
        }
    );

    return unsubscribeFunc;
}`;
              rnMethodSpec = `  ${comment}\n  ${methodName}(onResponse: OnResponseCallback, onError: OnErrorCallback): UnsubscribeFromStream;`;
            } else if (isClientStreaming && isServerStreaming) {
              // Bidirectional streaming RPC
              cppMethodDeclaration = `  jsi::Object ${methodName}(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);`;
              cppMethodImplementation = `
jsi::Object NativeSampleModuleCxx::${methodName}(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
    auto sharedOnResponse = std::make_shared<AsyncCallback2<std::string>>(std::move(onResponse));
    auto sharedOnError = std::make_shared<AsyncCallback2<std::string>>(std::move(onError));
    uint64_t callbackId = CallbackKeeper::getInstance().addCallbacks(sharedOnResponse, sharedOnError);

    CRecvStream recvStream = {
        .onResponse = &callbackOnResponseStatic,
        .onError = &callbackOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(callbackId),
        .errorContext = reinterpret_cast<void*>(callbackId),
    };

    uintptr_t streamPtr = ::${methodName}(recvStream);

    if (streamPtr != 0) {
        auto hostObject = std::make_shared<WritableStreamHostObject>(streamPtr, callbackId);
        return jsi::Object::createFromHostObject(rt, hostObject);
    } else {
        throw jsi::JSError(rt, "Failed to start ${methodName}");
    }
}`;
              rnMethodSpec = `  ${comment}\n  ${methodName}(onResponse: OnResponseCallback, onError: OnErrorCallback): WriteableStream;`;
            }

            if (cppMethodDeclaration) {
              cppHeaderResult.push(cppMethodDeclaration);
            }
            if (cppMethodImplementation) {
              cppResult.push(cppMethodImplementation);
            }
            if (rnMethodSpec) {
              rnResult.push(rnMethodSpec);
            }
          });
        }
      });
    }
  });

  const cppContent = `
#include "NativeSampleModuleCxx.h"

#include "liblnd.h"

#include "PromiseKeeper.h"
#include "CallbackKeeper.h"
#include "WritableStreamHostObject.h"
#include "base64.h"
#include "log.h"
#include "Promise.h"
#include "Function.h"

namespace facebook::react {

NativeSampleModuleCxx::NativeSampleModuleCxx(std::shared_ptr<CallInvoker> jsInvoker)
    : NativeSampleModuleCxxCxxSpec(std::move(jsInvoker)) {}

void NativeSampleModuleCxx::promiseOnResponseStatic(void* context, const char* data, int length) {
    // TURBOLND_LOG_DEBUG("promiseOnResponseStatic");
    uint64_t id = reinterpret_cast<uint64_t>(context);
    std::string encoded = base64_encode(data, length);
    PromiseKeeper::getInstance().resolvePromise(id, std::move(encoded));
}

void NativeSampleModuleCxx::promiseOnErrorStatic(void* context, const char* error) {
    // TURBOLND_LOG_ERROR("promiseOnErrorStatic");
    uint64_t id = reinterpret_cast<uint64_t>(context);
    PromiseKeeper::getInstance().rejectPromise(id, std::string(error));
}

void NativeSampleModuleCxx::callbackOnResponseStatic(void* context, const char* data, int length) {
    // TURBOLND_LOG_DEBUG("callbackOnResponseStatic");
    uint64_t id = reinterpret_cast<uint64_t>(context);
    std::string encoded = base64_encode(data, length);
    CallbackKeeper::getInstance().invokeResponseCallback(id, std::move(encoded));
}

void NativeSampleModuleCxx::callbackOnErrorStatic(void* context, const char* error) {
    // TURBOLND_LOG_ERROR("callbackOnErrorStatic");
    uint64_t id = reinterpret_cast<uint64_t>(context);
    CallbackKeeper::getInstance().invokeErrorCallback(id, std::string(error));
}

facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::start(jsi::Runtime &rt, jsi::String args) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = [](void* context, const char* data, int length) {
            uint64_t id = reinterpret_cast<uint64_t>(context);
            std::string encoded = base64_encode(data, length);
            PromiseKeeper::getInstance().resolvePromise(id, std::move(encoded));
        },
        .onError = [](void* context, const char* error) {
            uint64_t id = reinterpret_cast<uint64_t>(context);
            PromiseKeeper::getInstance().rejectPromise(id, std::string(error));
        },
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::string argsStr = args.utf8(rt);
    char* mutableArgs = const_cast<char*>(argsStr.c_str());

    ::start(mutableArgs, callback);

    return *promise;
}


${cppResult.join('\n\n')}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::promiseLeakTest(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    const size_t bufferSize = 100 * 1024 * 1024; // 10MB
    std::string largeBuffer(bufferSize, 'A');


    promiseOnResponseStatic(reinterpret_cast<void*>(promiseId), largeBuffer.c_str(), bufferSize);
    // promiseOnResponseStatic(reinterpret_cast<void*>(promiseId), "", 0);

    return *promise;
}
} // namespace facebook::react
`;

  const cppHeaderContent = `
#pragma once

#if __has_include(<React-Codegen/AppSpecsJSI.h>) // CocoaPod headers on Apple
#include <React-Codegen/AppSpecsJSI.h>
#elif __has_include("AppSpecsJSI.h") // CMake headers on Android
#include "AppSpecsJSI.h"
#endif
#include <memory>
#include <string>

#include <react/bridging/Promise.h>
#include "Promise.h"
#include "Function.h"

namespace facebook::react {

class NativeSampleModuleCxx : public NativeSampleModuleCxxCxxSpec<NativeSampleModuleCxx> {
 public:
  explicit NativeSampleModuleCxx(std::shared_ptr<CallInvoker> jsInvoker);

  static void promiseOnResponseStatic(void* context, const char* data, int length);
  static void promiseOnErrorStatic(void* context, const char* error);
  static void callbackOnResponseStatic(void* context, const char* data, int length);
  static void callbackOnErrorStatic(void* context, const char* error);


  facebook::react::AsyncPromise2<std::string> start(jsi::Runtime &rt, jsi::String args);

${cppHeaderResult.join('\n\n')}


  facebook::react::AsyncPromise2<std::string> promiseLeakTest(jsi::Runtime &rt, jsi::String data);
};

} // namespace facebook::react
`;

  const rnContent = `
import type { TurboModule } from 'react-native/Libraries/TurboModule/RCTExport';
import { TurboModuleRegistry } from 'react-native';

type ProtobufBase64 = string;
interface WriteableStream {
  send: (data: ProtobufBase64) => boolean;
  stop: () => boolean;
}
type OnResponseCallback = (data: ProtobufBase64) => void;
type OnErrorCallback = (error: string) => void;
type UnsubscribeFromStream = () => void;

export interface Spec extends TurboModule {
${rnResult.join('\n\n')}
}

export default TurboModuleRegistry.getEnforcing<Spec>('NativeSampleModuleCxx');
`;

  return { cppContent, cppHeaderContent, rnContent };
}

async function main() {
  try {
    const inputBuffer = fs.readFileSync(0);
    const root = await loadProtoFiles();

    const PluginRequest = root.lookupType("google.protobuf.compiler.CodeGeneratorRequest");
    const PluginResponse = root.lookupType("google.protobuf.compiler.CodeGeneratorResponse");

    const request = PluginRequest.decode(inputBuffer);
    const { cppContent, cppHeaderContent, rnContent } = generateCode(request);

    const response = PluginResponse.create({
      file: [
        {
          name: 'NativeSampleModuleCxx.cpp',
          content: cppContent
        },
        {
          name: 'NativeSampleModuleCxx.h',
          content: cppHeaderContent
        },
        {
          name: 'NativeSampleModuleSpec.ts',
          content: rnContent
        }
      ]
    });

    const responseBuffer = PluginResponse.encode(response).finish();
    process.stdout.write(responseBuffer);
  } catch (error) {
    console.error("Error in plugin:", error.stack);
    process.exit(1);
  }
}

main();
