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

    static void promiseOnResponseStatic(void* context, const char* data, int length) {
        TURBOLND_LOG_DEBUG("promiseOnResponseStatic");
        uint64_t id = reinterpret_cast<uint64_t>(context);
        std::string encoded = base64_encode(data, length);
        PromiseKeeper::getInstance().resolvePromise(id, std::move(encoded));
    }

    static void promiseOnErrorStatic(void* context, const char* error) {
        TURBOLND_LOG_ERROR("promiseOnErrorStatic");
        uint64_t id = reinterpret_cast<uint64_t>(context);
        PromiseKeeper::getInstance().rejectPromise(id, std::string(error));
    }

    static void callbackOnResponseStatic(void* context, const char* data, int length) {
        TURBOLND_LOG_DEBUG("callbackOnResponseStatic");
        uint64_t id = reinterpret_cast<uint64_t>(context);
        std::string encoded = base64_encode(data, length);
        CallbackKeeper::getInstance().invokeResponseCallback(id, std::move(encoded));
    }

    static void callbackOnErrorStatic(void* context, const char* error) {
        TURBOLND_LOG_ERROR("callbackOnErrorStatic");
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

    facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getInfo(jsi::Runtime &rt, jsi::String data) {
        auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
        uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

        CCallback callback = {
            .onResponse = &promiseOnResponseStatic,
            .onError = &promiseOnErrorStatic,
            .responseContext = reinterpret_cast<void*>(promiseId),
            .errorContext = reinterpret_cast<void*>(promiseId)
        };

        std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));

        ::getInfo(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

        return *promise;
    }

    facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::listPeers(jsi::Runtime &rt, jsi::String data) {
        auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
        uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

        CCallback callback = {
            .onResponse = &promiseOnResponseStatic,
            .onError = &promiseOnErrorStatic,
            .responseContext = reinterpret_cast<void*>(promiseId),
            .errorContext = reinterpret_cast<void*>(promiseId)
        };

        std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));

        ::listPeers(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

        return *promise;
    }

    facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::connectPeer(jsi::Runtime &rt, jsi::String data) {
        auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
        uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

        CCallback callback = {
            .onResponse = &promiseOnResponseStatic,
            .onError = &promiseOnErrorStatic,
            .responseContext = reinterpret_cast<void*>(promiseId),
            .errorContext = reinterpret_cast<void*>(promiseId)
        };

        std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
        ::connectPeer(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

        return *promise;
    }

    facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::listChannels(jsi::Runtime &rt, jsi::String data) {
        auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
        uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

        CCallback callback = {
            .onResponse = &promiseOnResponseStatic,
            .onError = &promiseOnErrorStatic,
            .responseContext = reinterpret_cast<void*>(promiseId),
            .errorContext = reinterpret_cast<void*>(promiseId)
        };

        std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
        ::listChannels(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

        return *promise;
    }

    facebook::jsi::Function NativeSampleModuleCxx::subscribeState(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
        ::subscribeState(emptyArray, length, recvStream);

        // Create and return an unsubscribe function
        auto unsubscribeFunc = jsi::Function::createFromHostFunction(
            rt,
            jsi::PropNameID::forAscii(rt, "unsubscribe"),
            0,  // no arguments
            [callbackId](jsi::Runtime& rt, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {
                CallbackKeeper::getInstance().removeCallbacks(callbackId);
                return jsi::Value::undefined();
            }
        );

        return unsubscribeFunc;
    }

    jsi::Object NativeSampleModuleCxx::channelAcceptor(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
        auto sharedOnResponse = std::make_shared<AsyncCallback2<std::string>>(std::move(onResponse));
        auto sharedOnError = std::make_shared<AsyncCallback2<std::string>>(std::move(onError));
        uint64_t callbackId = CallbackKeeper::getInstance().addCallbacks(sharedOnResponse, sharedOnError);

        CRecvStream recvStream = {
            .onResponse = &callbackOnResponseStatic,
            .onError = &callbackOnErrorStatic,
            .responseContext = reinterpret_cast<void*>(callbackId),
            .errorContext = reinterpret_cast<void*>(callbackId),
        };


        uintptr_t streamPtr = ::channelAcceptor(recvStream);

        if (streamPtr != 0) {
            TURBOLND_LOG_DEBUG("Bidi stream started");
            auto hostObject = std::make_shared<WritableStreamHostObject>(streamPtr);
            return jsi::Object::createFromHostObject(rt, hostObject);
        } else {
            TURBOLND_LOG_ERROR("Bidi stream fail");
            throw jsi::JSError(rt, "Failed to start channel acceptor");
        }
    }

} // namespace facebook::react
