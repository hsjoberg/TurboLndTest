
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



facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletBalance(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletBalance(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::channelBalance(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::channelBalance(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getTransactions(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::getTransactions(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::estimateFee(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::estimateFee(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::sendCoins(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::sendCoins(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::listUnspent(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::listUnspent(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::subscribeTransactions(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::subscribeTransactions(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::sendMany(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::sendMany(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::newAddress(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::newAddress(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signMessage(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signMessage(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::verifyMessage(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::verifyMessage(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

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


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::disconnectPeer(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::disconnectPeer(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

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


facebook::jsi::Function NativeSampleModuleCxx::subscribePeerEvents(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::subscribePeerEvents(emptyArray, length, recvStream);

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


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getRecoveryInfo(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::getRecoveryInfo(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::pendingChannels(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::pendingChannels(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

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


facebook::jsi::Function NativeSampleModuleCxx::subscribeChannelEvents(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::subscribeChannelEvents(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::closedChannels(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::closedChannels(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::openChannelSync(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::openChannelSync(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::openChannel(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::openChannel(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::batchOpenChannel(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::batchOpenChannel(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::fundingStateStep(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::fundingStateStep(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
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
        auto hostObject = std::make_shared<WritableStreamHostObject>(streamPtr, callbackId);
        return jsi::Object::createFromHostObject(rt, hostObject);
    } else {
        throw jsi::JSError(rt, "Failed to start channelAcceptor");
    }
}


facebook::jsi::Function NativeSampleModuleCxx::closeChannel(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::closeChannel(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::abandonChannel(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::abandonChannel(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


jsi::Object NativeSampleModuleCxx::sendPayment(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
    auto sharedOnResponse = std::make_shared<AsyncCallback2<std::string>>(std::move(onResponse));
    auto sharedOnError = std::make_shared<AsyncCallback2<std::string>>(std::move(onError));
    uint64_t callbackId = CallbackKeeper::getInstance().addCallbacks(sharedOnResponse, sharedOnError);

    CRecvStream recvStream = {
        .onResponse = &callbackOnResponseStatic,
        .onError = &callbackOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(callbackId),
        .errorContext = reinterpret_cast<void*>(callbackId),
    };

    uintptr_t streamPtr = ::sendPayment(recvStream);

    if (streamPtr != 0) {
        auto hostObject = std::make_shared<WritableStreamHostObject>(streamPtr, callbackId);
        return jsi::Object::createFromHostObject(rt, hostObject);
    } else {
        throw jsi::JSError(rt, "Failed to start sendPayment");
    }
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::sendPaymentSync(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::sendPaymentSync(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


jsi::Object NativeSampleModuleCxx::sendToRoute(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
    auto sharedOnResponse = std::make_shared<AsyncCallback2<std::string>>(std::move(onResponse));
    auto sharedOnError = std::make_shared<AsyncCallback2<std::string>>(std::move(onError));
    uint64_t callbackId = CallbackKeeper::getInstance().addCallbacks(sharedOnResponse, sharedOnError);

    CRecvStream recvStream = {
        .onResponse = &callbackOnResponseStatic,
        .onError = &callbackOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(callbackId),
        .errorContext = reinterpret_cast<void*>(callbackId),
    };

    uintptr_t streamPtr = ::sendToRoute(recvStream);

    if (streamPtr != 0) {
        auto hostObject = std::make_shared<WritableStreamHostObject>(streamPtr, callbackId);
        return jsi::Object::createFromHostObject(rt, hostObject);
    } else {
        throw jsi::JSError(rt, "Failed to start sendToRoute");
    }
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::sendToRouteSync(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::sendToRouteSync(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::addInvoice(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::addInvoice(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::listInvoices(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::listInvoices(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::lookupInvoice(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::lookupInvoice(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::subscribeInvoices(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::subscribeInvoices(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::decodePayReq(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::decodePayReq(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::listPayments(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::listPayments(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::deletePayment(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::deletePayment(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::deleteAllPayments(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::deleteAllPayments(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::describeGraph(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::describeGraph(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getNodeMetrics(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::getNodeMetrics(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getChanInfo(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::getChanInfo(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getNodeInfo(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::getNodeInfo(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::queryRoutes(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::queryRoutes(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getNetworkInfo(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::getNetworkInfo(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::stopDaemon(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::stopDaemon(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::subscribeChannelGraph(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::subscribeChannelGraph(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::debugLevel(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::debugLevel(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::feeReport(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::feeReport(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::updateChannelPolicy(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::updateChannelPolicy(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::forwardingHistory(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::forwardingHistory(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::exportChannelBackup(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::exportChannelBackup(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::exportAllChannelBackups(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::exportAllChannelBackups(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::verifyChanBackup(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::verifyChanBackup(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::restoreChannelBackups(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::restoreChannelBackups(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::subscribeChannelBackups(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::subscribeChannelBackups(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::bakeMacaroon(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::bakeMacaroon(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::listMacaroonIDs(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::listMacaroonIDs(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::deleteMacaroonID(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::deleteMacaroonID(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::listPermissions(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::listPermissions(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::checkMacaroonPermissions(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::checkMacaroonPermissions(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


jsi::Object NativeSampleModuleCxx::registerRPCMiddleware(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
    auto sharedOnResponse = std::make_shared<AsyncCallback2<std::string>>(std::move(onResponse));
    auto sharedOnError = std::make_shared<AsyncCallback2<std::string>>(std::move(onError));
    uint64_t callbackId = CallbackKeeper::getInstance().addCallbacks(sharedOnResponse, sharedOnError);

    CRecvStream recvStream = {
        .onResponse = &callbackOnResponseStatic,
        .onError = &callbackOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(callbackId),
        .errorContext = reinterpret_cast<void*>(callbackId),
    };

    uintptr_t streamPtr = ::registerRPCMiddleware(recvStream);

    if (streamPtr != 0) {
        auto hostObject = std::make_shared<WritableStreamHostObject>(streamPtr, callbackId);
        return jsi::Object::createFromHostObject(rt, hostObject);
    } else {
        throw jsi::JSError(rt, "Failed to start registerRPCMiddleware");
    }
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::sendCustomMessage(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::sendCustomMessage(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::subscribeCustomMessages(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::subscribeCustomMessages(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::listAliases(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::listAliases(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::lookupHtlcResolution(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::lookupHtlcResolution(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::genSeed(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::genSeed(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::initWallet(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::initWallet(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::unlockWallet(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::unlockWallet(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::changePassword(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::changePassword(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getState(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::getState(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::autopilotStatus(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::autopilotStatus(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::autopilotModifyStatus(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::autopilotModifyStatus(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::autopilotQueryScores(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::autopilotQueryScores(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::autopilotSetScores(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::autopilotSetScores(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::chainNotifierRegisterConfirmationsNtfn(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::chainNotifierRegisterConfirmationsNtfn(emptyArray, length, recvStream);

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
}


facebook::jsi::Function NativeSampleModuleCxx::chainNotifierRegisterSpendNtfn(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::chainNotifierRegisterSpendNtfn(emptyArray, length, recvStream);

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
}


facebook::jsi::Function NativeSampleModuleCxx::chainNotifierRegisterBlockEpochNtfn(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::chainNotifierRegisterBlockEpochNtfn(emptyArray, length, recvStream);

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
}


facebook::jsi::Function NativeSampleModuleCxx::invoicesSubscribeSingleInvoice(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::invoicesSubscribeSingleInvoice(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::invoicesCancelInvoice(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::invoicesCancelInvoice(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::invoicesAddHoldInvoice(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::invoicesAddHoldInvoice(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::invoicesSettleInvoice(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::invoicesSettleInvoice(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::invoicesLookupInvoiceV2(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::invoicesLookupInvoiceV2(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::neutrinoKitStatus(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::neutrinoKitStatus(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::neutrinoKitAddPeer(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::neutrinoKitAddPeer(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::neutrinoKitDisconnectPeer(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::neutrinoKitDisconnectPeer(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::neutrinoKitIsBanned(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::neutrinoKitIsBanned(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::neutrinoKitGetBlockHeader(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::neutrinoKitGetBlockHeader(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::neutrinoKitGetBlock(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::neutrinoKitGetBlock(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::neutrinoKitGetCFilter(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::neutrinoKitGetCFilter(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::neutrinoKitGetBlockHash(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::neutrinoKitGetBlockHash(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::peersUpdateNodeAnnouncement(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::peersUpdateNodeAnnouncement(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::routerSendPaymentV2(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::routerSendPaymentV2(emptyArray, length, recvStream);

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
}


facebook::jsi::Function NativeSampleModuleCxx::routerTrackPaymentV2(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::routerTrackPaymentV2(emptyArray, length, recvStream);

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
}


facebook::jsi::Function NativeSampleModuleCxx::routerTrackPayments(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::routerTrackPayments(emptyArray, length, recvStream);

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
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerEstimateRouteFee(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerEstimateRouteFee(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerSendToRoute(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerSendToRoute(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerSendToRouteV2(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerSendToRouteV2(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerResetMissionControl(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerResetMissionControl(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerQueryMissionControl(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerQueryMissionControl(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerXImportMissionControl(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerXImportMissionControl(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerGetMissionControlConfig(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerGetMissionControlConfig(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerSetMissionControlConfig(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerSetMissionControlConfig(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerQueryProbability(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerQueryProbability(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerBuildRoute(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerBuildRoute(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::jsi::Function NativeSampleModuleCxx::routerSubscribeHtlcEvents(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::routerSubscribeHtlcEvents(emptyArray, length, recvStream);

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
}


facebook::jsi::Function NativeSampleModuleCxx::routerSendPayment(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::routerSendPayment(emptyArray, length, recvStream);

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
}


facebook::jsi::Function NativeSampleModuleCxx::routerTrackPayment(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
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
    ::routerTrackPayment(emptyArray, length, recvStream);

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
}


jsi::Object NativeSampleModuleCxx::routerHtlcInterceptor(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
    auto sharedOnResponse = std::make_shared<AsyncCallback2<std::string>>(std::move(onResponse));
    auto sharedOnError = std::make_shared<AsyncCallback2<std::string>>(std::move(onError));
    uint64_t callbackId = CallbackKeeper::getInstance().addCallbacks(sharedOnResponse, sharedOnError);

    CRecvStream recvStream = {
        .onResponse = &callbackOnResponseStatic,
        .onError = &callbackOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(callbackId),
        .errorContext = reinterpret_cast<void*>(callbackId),
    };

    uintptr_t streamPtr = ::routerHtlcInterceptor(recvStream);

    if (streamPtr != 0) {
        auto hostObject = std::make_shared<WritableStreamHostObject>(streamPtr, callbackId);
        return jsi::Object::createFromHostObject(rt, hostObject);
    } else {
        throw jsi::JSError(rt, "Failed to start routerHtlcInterceptor");
    }
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::routerUpdateChanStatus(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::routerUpdateChanStatus(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerSignOutputRaw(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerSignOutputRaw(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerComputeInputScript(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerComputeInputScript(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerSignMessage(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerSignMessage(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerVerifyMessage(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerVerifyMessage(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerDeriveSharedKey(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerDeriveSharedKey(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerMuSig2CombineKeys(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerMuSig2CombineKeys(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerMuSig2CreateSession(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerMuSig2CreateSession(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerMuSig2RegisterNonces(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerMuSig2RegisterNonces(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerMuSig2Sign(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerMuSig2Sign(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerMuSig2CombineSig(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerMuSig2CombineSig(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::signerMuSig2Cleanup(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::signerMuSig2Cleanup(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::versionerGetVersion(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::versionerGetVersion(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitListUnspent(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitListUnspent(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitLeaseOutput(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitLeaseOutput(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitReleaseOutput(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitReleaseOutput(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitListLeases(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitListLeases(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitDeriveNextKey(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitDeriveNextKey(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitDeriveKey(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitDeriveKey(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitNextAddr(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitNextAddr(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitListAccounts(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitListAccounts(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitRequiredReserve(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitRequiredReserve(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitListAddresses(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitListAddresses(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitSignMessageWithAddr(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitSignMessageWithAddr(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitVerifyMessageWithAddr(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitVerifyMessageWithAddr(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitImportAccount(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitImportAccount(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitImportPublicKey(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitImportPublicKey(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitImportTapscript(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitImportTapscript(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitPublishTransaction(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitPublishTransaction(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitSendOutputs(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitSendOutputs(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitEstimateFee(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitEstimateFee(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitPendingSweeps(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitPendingSweeps(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitBumpFee(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitBumpFee(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitListSweeps(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitListSweeps(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitLabelTransaction(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitLabelTransaction(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitFundPsbt(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitFundPsbt(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitSignPsbt(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitSignPsbt(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::walletKitFinalizePsbt(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::walletKitFinalizePsbt(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::watchtowerGetInfo(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::watchtowerGetInfo(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::watchtowerClientAddTower(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::watchtowerClientAddTower(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::watchtowerClientRemoveTower(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::watchtowerClientRemoveTower(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::watchtowerClientListTowers(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::watchtowerClientListTowers(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::watchtowerClientGetTowerInfo(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::watchtowerClientGetTowerInfo(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::watchtowerClientStats(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::watchtowerClientStats(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::watchtowerClientPolicy(jsi::Runtime &rt, jsi::String data) {
    auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
    uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

    CCallback callback = {
        .onResponse = &promiseOnResponseStatic,
        .onError = &promiseOnErrorStatic,
        .responseContext = reinterpret_cast<void*>(promiseId),
        .errorContext = reinterpret_cast<void*>(promiseId)
    };

    std::vector<uint8_t> decodedData = base64_decode(data.utf8(rt));
    ::watchtowerClientPolicy(reinterpret_cast<char*>(decodedData.data()), static_cast<int>(decodedData.size()), callback);

    return *promise;
}


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
