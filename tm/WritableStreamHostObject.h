#pragma once

#include <jsi/jsi.h>

#include "base64.h"

using namespace facebook;

// WritableStreamHostObject is a JSI HostObject that allows JS-side to send back
// responses for a bidirectional gRPC stream.
class WritableStreamHostObject : public jsi::HostObject {
private:
    uintptr_t streamPtr;

public:
    WritableStreamHostObject(uintptr_t ptr) : streamPtr(ptr) {}

    jsi::Value send(jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) {
        if (count < 1 || !arguments[0].isString()) {
            throw jsi::JSError(runtime, "send method expects a base64 encoded string argument");
        }

        std::string base64Data = arguments[0].asString(runtime).utf8(runtime);
        std::vector<uint8_t> decodedData = base64_decode(base64Data);

        int sendResult = SendStreamC(streamPtr, reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()));
        return jsi::Value(sendResult == 0);
    }

    jsi::Value stop(jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) {
        int stopResult = StopStreamC(streamPtr);
        return jsi::Value(stopResult == 0);
    }

    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime& rt) override {
        std::vector<jsi::PropNameID> result;
        result.push_back(jsi::PropNameID::forAscii(rt, "send"));
        result.push_back(jsi::PropNameID::forAscii(rt, "stop"));
        return result;
    }

    jsi::Value get(jsi::Runtime& rt, const jsi::PropNameID& pid) override {
        auto name = pid.utf8(rt);
        if (name == "send") {
            return jsi::Function::createFromHostFunction(rt, pid, 1, [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) {
                return this->send(runtime, thisValue, arguments, count);
            });
        } else if (name == "stop") {
            return jsi::Function::createFromHostFunction(rt, pid, 0, [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) {
                return this->stop(runtime, thisValue, arguments, count);
            });
        }
        return jsi::Value::undefined();
    }
};
