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

namespace facebook::react {

class NativeSampleModule : public NativeSampleModuleCxxSpec<NativeSampleModule> {
private:
    // std::shared_ptr<facebook::react::CallInvoker> jsInvoker_;

    // Static member functions to serve as actual callbacks
    // static void handleOnResponse(jsi::Runtime& rt, const std::shared_ptr<react::Promise>& promise, const char* data, int length) {
    //     promise->resolve(std::string(data, length));
    // }

    // static void handleOnError(jsi::Runtime& rt, const std::shared_ptr<facebook::react::Promise>& promise, const char* error) {
    //     promise->reject(std::string(error));
    // }

    // // Static thunk functions
    // static void handleOnResponseThunk(void* context, const char* data, int length) {
    //     auto* params = static_cast<std::pair<jsi::Runtime*, std::shared_ptr<facebook::react::Promise>*>*>(context);
    //     handleOnResponse(*params->first, *params->second, data, length);
    //     // delete params;  // Clean up the context
    // }

    // static void handleOnErrorThunk(void* context, const char* error) {
    //     auto* params = static_cast<std::pair<jsi::Runtime*, std::shared_ptr<facebook::react::Promise>*>*>(context);
    //     handleOnError(*params->first, *params->second, error);
    //     // delete params;  // Clean up the context
    // }


 public:
  NativeSampleModule(std::shared_ptr<CallInvoker> jsInvoker);

    std::shared_ptr<facebook::react::AsyncPromise<std::string>> globalPromise;

  void start(jsi::Runtime &rt, std::string config, jsi::Function onResponse);
  jsi::Value startPromise(jsi::Runtime &rt, jsi::String config);
  facebook::react::AsyncPromise<std::string> startPromise2(jsi::Runtime &rt);
  facebook::react::AsyncPromise<std::string> startPromise3(jsi::Runtime &rt);
  facebook::react::AsyncPromise<std::string> startPromise4(jsi::Runtime &rt);
  jsi::Value startPromise5(jsi::Runtime &rt);
  jsi::Value startPromise6(jsi::Runtime &rt);
  jsi::Value startPromise7(jsi::Runtime &rt);
  void callback(jsi::Runtime &rt, AsyncCallback<std::string> callback);
  jsi::Value promise(jsi::Runtime &rt);
  void startPromiseCallback(jsi::Runtime &rt, AsyncCallback<std::string> callback);
  void startPromiseCallback2(jsi::Runtime &rt, AsyncCallback<std::string> callback);
  void startPromiseCallback3(jsi::Runtime &rt, AsyncCallback<std::string> callback);
  facebook::react::AsyncPromise<std::string> getInfo(jsi::Runtime &rt);
  facebook::react::AsyncPromise2<std::string> getInfo4(jsi::Runtime &rt);
  jsi::Value getInfo2(jsi::Runtime &rt);
  jsi::Value getInfo3(jsi::Runtime &rt);
  void getInfoCallback(jsi::Runtime &rt, AsyncCallback<std::string> callback);
  void reg(jsi::Runtime &rt);
  facebook::react::AsyncPromise<std::string> prom(jsi::Runtime &rt);
  void a(jsi::Runtime &rt);
  void log();
};

} // namespace facebook::react
