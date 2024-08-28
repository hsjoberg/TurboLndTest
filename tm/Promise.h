/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <react/bridging/Error.h>
#include <react/bridging/Function.h>
#include <react/bridging/LongLivedObject.h>
#include <mutex>
#include <optional>

#include "log.h"

namespace facebook::react {

template <typename T>
class AsyncPromise2 {
 public:
  AsyncPromise2(jsi::Runtime& rt, const std::shared_ptr<CallInvoker>& jsInvoker)
      : state_(std::make_shared<SharedState>()) {

    //TURBOLND_LOG_DEBUG("Constructor AsyncPromise");
    auto constructor = rt.global().getPropertyAsFunction(rt, "Promise");

    auto promise = constructor.callAsConstructor(
        rt,
        bridging::toJs(
            rt,
            // Safe to capture this since this is called synchronously.
            [this](AsyncCallback<T> resolve, AsyncCallback<Error> reject) {
              state_->resolve = std::move(resolve);
              state_->reject = std::move(reject);
            },
            jsInvoker));

    auto promiseHolder =
        std::make_shared<PromiseHolder>(rt, promise.asObject(rt));
    LongLivedObjectCollection::get(rt).add(promiseHolder);

    // The shared state can retain the promise holder weakly now.
    state_->promiseHolder = promiseHolder;
  }

  void resolve(T value) {
    //TURBOLND_LOG_DEBUG("resolving promise");
    std::lock_guard<std::mutex> lock(state_->mutex);
    //TURBOLND_LOG_DEBUG("after mutex lock");
    if (state_->resolve) {
      //TURBOLND_LOG_DEBUG("calling promise resolve");
      state_->resolve->call(std::move(value));
      //TURBOLND_LOG_DEBUG("Clearing promise");
      state_->resolve.reset();
      state_->reject.reset();
      //TURBOLND_LOG_DEBUG("Cleared promise");
    }
    //TURBOLND_LOG_DEBUG("after if");
  }

  void reject(Error error) {
    std::lock_guard<std::mutex> lock(state_->mutex);

    if (state_->reject) {
      state_->reject->call(std::move(error));
      state_->reject.reset();
      state_->resolve.reset();
    }
  }

  jsi::Object get(jsi::Runtime& rt) const {
    if (auto holder = state_->promiseHolder.lock()) {
      return jsi::Value(rt, holder->promise).asObject(rt);
    } else {
      throw jsi::JSError(rt, "Failed to get invalidated promise");
    }
  }

 private:
  struct PromiseHolder : LongLivedObject {
    PromiseHolder(jsi::Runtime& runtime, jsi::Object p)
        : LongLivedObject(runtime), promise(std::move(p)) {}

    jsi::Object promise;
  };

  struct SharedState {
    ~SharedState() {
      //TURBOLND_LOG_DEBUG("Destructor SharedState");
      if (auto holder = promiseHolder.lock()) {
        //TURBOLND_LOG_DEBUG("promiseHolder release");
        holder->allowRelease();
        //TURBOLND_LOG_DEBUG("Released");
      }
    }

    std::mutex mutex;
    std::weak_ptr<PromiseHolder> promiseHolder;
    std::optional<AsyncCallback<T>> resolve;
    std::optional<AsyncCallback<Error>> reject;
  };

  std::shared_ptr<SharedState> state_;
};

template <typename T>
struct Bridging<AsyncPromise2<T>> {
  static jsi::Object toJs(jsi::Runtime& rt, const AsyncPromise2<T>& promise) {
    return promise.get(rt);
  }
};

} // namespace facebook::react
