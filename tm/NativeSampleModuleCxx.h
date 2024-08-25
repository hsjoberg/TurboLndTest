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
  NativeSampleModuleCxx(std::shared_ptr<CallInvoker> jsInvoker);

  facebook::react::AsyncPromise2<std::string> start(jsi::Runtime &rt, jsi::String args);
  facebook::react::AsyncPromise2<std::string> getInfo(jsi::Runtime &rt, jsi::String data);
  facebook::react::AsyncPromise2<std::string> listPeers(jsi::Runtime &rt, jsi::String data);
  facebook::react::AsyncPromise2<std::string> connectPeer(jsi::Runtime &rt, jsi::String data);
  facebook::react::AsyncPromise2<std::string> listChannels(jsi::Runtime &rt, jsi::String data);
  facebook::jsi::Function subscribeState(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);
  jsi::Object channelAcceptor(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError);
};

} // namespace facebook::react
