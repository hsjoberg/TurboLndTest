#include "NativeSampleModuleCxx.h"
#include "liblnd.h"
#include "liba.h"
#include <android/log.h>
#include <thread>
#include "RNFPromise.h"
#include <ReactCommon/TurboModuleUtils.h>
#include <mutex>
// #include <functional>


#include <cstdlib>
#include <ctime>

namespace facebook::react {


static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

std::string base64_encode(const char* input, int length) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (length--) {
        char_array_3[i++] = *(input++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; i < 4; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; j < i + 1; j++)
            ret += base64_chars[char_array_4[j]];

        while(i++ < 3)
            ret += '=';
    }

    return ret;
}

std::vector<uint8_t> base64_decode(const std::string& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    uint8_t char_array_4[4], char_array_3[3];
    std::vector<uint8_t> ret;

    while (in_len-- && (encoded_string[in_] != '=') && (isalnum(encoded_string[in_]) || (encoded_string[in_] == '+') || (encoded_string[in_] == '/'))) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret.push_back(char_array_3[i]);
            i = 0;
        }
    }

    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;

        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
    }

    return ret;
}

class PromiseHolder {
public:
    PromiseHolder(jsi::Runtime& rt, std::shared_ptr<facebook::react::CallInvoker> jsInvoker)
        : promise(std::make_shared<facebook::react::AsyncPromise<std::string>>(rt, jsInvoker)) {}

    std::shared_ptr<facebook::react::AsyncPromise<std::string>> promise;
};

class PromiseKeeper {
public:
    static PromiseKeeper& getInstance() {
        static PromiseKeeper instance;
        return instance;
    }

    uint64_t addPromise(std::shared_ptr<facebook::react::AsyncPromise2<std::string>> promise) {
        std::lock_guard<std::mutex> lock(mutex_);
        uint64_t id = nextId_++;
        promises_[id] = promise;
        return id;
    }

    void resolvePromise(uint64_t id, std::string value) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = promises_.find(id);
        if (it != promises_.end()) {
            it->second->resolve(std::move(value));
            promises_.erase(it);
        }
    }

    void rejectPromise(uint64_t id, std::string error) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = promises_.find(id);
        if (it != promises_.end()) {
            it->second->reject(std::move(error));
            promises_.erase(it);
        }
    }

private:
    PromiseKeeper() : nextId_(1) {}
    std::mutex mutex_;
    std::map<uint64_t, std::shared_ptr<facebook::react::AsyncPromise2<std::string>>> promises_;
    uint64_t nextId_;
};

class CallbackKeeper {
public:
    static CallbackKeeper& getInstance() {
        static CallbackKeeper instance;
        return instance;
    }

    struct CallbackPair {
        std::shared_ptr<AsyncCallback2<std::string>> onResponse;
        std::shared_ptr<AsyncCallback2<std::string>> onError;
    };

    uint64_t addCallbacks(std::shared_ptr<AsyncCallback2<std::string>> onResponse,
                          std::shared_ptr<AsyncCallback2<std::string>> onError) {
        std::lock_guard<std::mutex> lock(mutex_);
        uint64_t id = nextId_++;
        callbacks_[id] = {onResponse, onError};
        return id;
    }

    void invokeResponseCallback(uint64_t id, const std::string& data) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = callbacks_.find(id);
        if (it != callbacks_.end() && it->second.onResponse) {
            it->second.onResponse->call(data);
        }
    }

    void invokeErrorCallback(uint64_t id, const std::string& error) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = callbacks_.find(id);
        if (it != callbacks_.end() && it->second.onError) {
            it->second.onError->call(error);
        }
    }

    void removeCallbacks(uint64_t id) {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.erase(id);
    }

private:
    CallbackKeeper() : nextId_(1) {}
    std::mutex mutex_;
    std::map<uint64_t, CallbackPair> callbacks_;
    uint64_t nextId_;
};

class StreamHostObject : public jsi::HostObject {
private:
    uintptr_t streamPtr;

public:
    StreamHostObject(uintptr_t ptr) : streamPtr(ptr) {}

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


static void promiseOnResponseStatic(void* context, const char* data, int length) {
    uint64_t id = reinterpret_cast<uint64_t>(context);
    std::string encoded = base64_encode(data, length);
    PromiseKeeper::getInstance().resolvePromise(id, std::move(encoded));
}

static void promiseOnErrorStatic(void* context, const char* error) {
    uint64_t id = reinterpret_cast<uint64_t>(context);
    PromiseKeeper::getInstance().rejectPromise(id, std::string(error));
}

static void callbackOnResponseStatic(void* context, const char* data, int length) {
    __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "callbackOnResponseStatic");
    uint64_t id = reinterpret_cast<uint64_t>(context);
    std::string encoded = base64_encode(data, length);
    CallbackKeeper::getInstance().invokeResponseCallback(id, std::move(encoded));
}

static void callbackOnErrorStatic(void* context, const char* error) {
    __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "callbackOnErrorStatic");
    uint64_t id = reinterpret_cast<uint64_t>(context);
    CallbackKeeper::getInstance().invokeErrorCallback(id, std::string(error));
}

NativeSampleModuleCxx::NativeSampleModuleCxx(std::shared_ptr<CallInvoker> jsInvoker)
    : NativeSampleModuleCxxCxxSpec(std::move(jsInvoker)) {}


    void myCallback(const char* message) {
        __android_log_write(ANDROID_LOG_ERROR, "turbolndandroid", "from callback");
    }


// jsi::Value NativeSampleModuleCxx::start(jsi::Runtime& rt, std::string input) {
// //   Callback myCallback = {onResponse, onError, nullptr}; // nullptr for context if not needed
// //   GoString args = createGoString("");
// //   GoInterface rpcReady = createGoInterface(&myCallback);
// //   Start(args, rpcReady);


//    // "--lnddir=/data/user/0/com.example.turbolndandroid/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json"
// //    Callback myCallback = {onResponse, onError, nullptr}; // nullptr for context if not needed
// //    GoString args = createGoString("--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill");
// //    GoInterface rpcReady = createGoInterface(&myCallback);
// //    Start(args, rpcReady);

//   return std::string(input.rbegin(), input.rend());
// }

void onResponse(void*, const char*, int) {
    __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "from onResponse");
}

//https://stackoverflow.com/questions/28746744/passing-capturing-lambda-as-function-pointer
//http://bannalia.blogspot.com/2016/07/passing-capturing-c-lambda-functions-as.html
//https://github.com/mfbx9da4/react-native-jsi-promise/blob/9ed4e59a344a7368973eac3af56908fd76f68b80/ios/JsiPromise.mm#L135
//https://github.com/facebook/react-native/issues/44813
    void NativeSampleModuleCxx::start(jsi::Runtime &rt, std::string config, jsi::Function onRes) {
        // auto onResShared = std::make_shared<jsi::Function>(onRes.asFunction(rt));
        // auto onResShared = std::make_shared<jsi::Object>(onRes(rt));


        auto responseCallback = [](const char* data, int length) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseCallback");
        };

        auto responseThunk = [](void* context, const char* data, int length) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseThunk");
            (*static_cast<decltype(responseCallback)*>(context))(data, length);
        };

        CCallback callback = {
            .onResponse = responseThunk,
            .onError = [](void *, const char *) {
                __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onError");
            },
            .responseContext = &responseCallback,
            .errorContext = NULL
        };

        char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
        ::start(args, callback);

        return;
    }

    jsi::Value NativeSampleModuleCxx::startPromise(jsi::Runtime &rt, jsi::String config) {
        // jsInvoker_->invokeAsync([]() {
        //    __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "invokeAsync");
        // });

        jsi::Function promiseConstructor = rt.global().getPropertyAsFunction(rt, "Promise");
        return promiseConstructor.callAsConstructor(
            rt,
            jsi::Function::createFromHostFunction(
                rt,
                jsi::PropNameID::forAscii(rt, "promiseArg"),
                2,
                [invoker = jsInvoker_](
                    jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, std::size_t count) -> jsi::Value {

                    // invoker->invokeAsync([]() {
                    //     __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "invokeAsync");
                    // });

                    auto resolve = std::make_shared<jsi::Value>(runtime, arguments[0]);
                    auto reject = std::make_shared<jsi::Value>(runtime, arguments[1]);


                    // jsi::Function resolve = arguments[0].asObject(runtime).asFunction(runtime);

                    auto responseCallback = [invoker2 = invoker, &runtime, &resolve](const char* data, int length) {
                        __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseCallback");

                        invoker2->invokeAsync([]() {
                            // __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "invokeAsync");
                        });
                        //  resolve.call(runtime, 123);
                        // resolve->asObject(runtime).asFunction(runtime).call(runtime, 123);
                    };

                    auto responseThunk = [](void* context, const char* data, int length) {
                        __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseThunk");

                        (*static_cast<decltype(responseCallback)*>(context))(data, length);
                    };


                    CCallback callback = {
                        .onResponse = responseThunk,
                        .onError = [](void *, const char *) {
                            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onError");
                        },
                        .responseContext = &responseCallback,
                        .errorContext = NULL
                    };


                    char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
                    ::start(args, callback);
                    return jsi::Value::undefined();
                }
            ));
    }

        // std::shared_ptr<facebook::react::AsyncPromise<std::string>> promisePtr = std::make_shared<facebook::react::AsyncPromise<std::string>>(rt, jsInvoker_);
        // bridging::callFromJs(rt,)

    void NativeSampleModuleCxx::log() {
        __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till log");
        this->jsInvoker_->invokeAsync([]() {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till log invokeAsync");
        });
    }

    // works
    facebook::react::AsyncPromise<std::string> NativeSampleModuleCxx::startPromise2(jsi::Runtime &rt) {
        globalPromise = std::make_shared<facebook::react::AsyncPromise<std::string>>(rt, jsInvoker_);

        auto responseCallback = [](const char* data, int length) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseCallback");
        };

        // auto responseThunk = [](void* context, const char* data, int length) {
        //     __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseThunk");

        //     (*static_cast<decltype(responseCallback)*>(context))(data, length);
        // };

        auto responseThunk = [](void* context, const char* data, int length) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseThunk");
            auto* self = static_cast<NativeSampleModuleCxx*>(context);
            self->globalPromise->resolve("test?");
        };

        CCallback callback = {
            .onResponse = responseThunk,
            .onError = [](void *, const char *) {
                __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onError");
            },
            .responseContext =  this,//&responseCallback,
            .errorContext = this
        };


        char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
        ::start(args, callback);


        return *globalPromise;
        // return promise;
    }

    // Works but not delete
    facebook::react::AsyncPromise<std::string> NativeSampleModuleCxx::startPromise3(jsi::Runtime &rt) {
        // Create a shared_ptr to PromiseHolder
        auto holder = std::make_shared<PromiseHolder>(rt, jsInvoker_);

        // Create the CCallback structure
        CCallback callback = {
            .onResponse = [](void* context, const char* data, int length) {
                __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onResponse");
                auto holderPtr = static_cast<std::shared_ptr<PromiseHolder>*>(context);
                (*holderPtr)->promise->resolve("startPromise3 onResponse");
                delete holderPtr;  // Clean up the pointer
            },
            .onError = [](void* context, const char* error) {
                __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onError");
                auto holderPtr = static_cast<std::shared_ptr<PromiseHolder>*>(context);
                (*holderPtr)->promise->resolve("startPromise3 onError");
                delete holderPtr;  // Clean up the pointer
            },
            .responseContext = new std::shared_ptr<PromiseHolder>(holder),
            .errorContext = new std::shared_ptr<PromiseHolder>(holder)
        };

        // Call your async function here, passing the callback
        char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
        ::start(args, callback);

        // Return a copy of the promise
        return *holder->promise;
    }

    // Works but not delete
    facebook::react::AsyncPromise<std::string> NativeSampleModuleCxx::startPromise4(jsi::Runtime &rt) {
        // Create a pointer to AsyncPromise
        auto* promisePtr = new facebook::react::AsyncPromise<std::string>(rt, jsInvoker_);

        // Create the CCallback structure
        CCallback callback = {
            .onResponse = [](void* context, const char* data, int length) {
                auto promise = static_cast<facebook::react::AsyncPromise<std::string>*>(context);
                promise->resolve(std::string(data, length));
                // delete promise;  // Clean up the promise
            },
            .onError = [](void* context, const char* error) {
                auto promise = static_cast<facebook::react::AsyncPromise<std::string>*>(context);
                promise->reject(std::string(error));
                // delete promise;  // Clean up the promise
            },
            .responseContext = promisePtr,
            .errorContext = promisePtr
        };

        // Call your async function here, passing the callback
        char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
        ::start(args, callback);

        // Return a copy of the promise
        return *promisePtr;
    }


    // Works but, promise not always immediately returned
    jsi::Value NativeSampleModuleCxx::startPromise5(jsi::Runtime &rt) {
        auto promise = margelo::Promise::createPromise(rt, [jsInvoker = jsInvoker_](jsi::Runtime& runtime, std::shared_ptr<margelo::Promise> promise) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "createPromise");

            auto onResponseCallback = [jsInvoker, p = std::move(promise)](const char* data, int length) {
                __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onResponseCallback");
                jsInvoker->invokeAsync([p = std::move(p)]() {
                    p->resolve(1);
                });
                // p->resolve(1);
            };

            CCallback c = {
                .onResponse = [](void* context, const char* data, int length) {
                    (*static_cast<decltype(onResponseCallback)*>(context))(data, length);
                },
                .onError = [](void* context, const char* error) {
                },
                .responseContext = new decltype(onResponseCallback)(std::move(onResponseCallback)),//&onResponseCallback, //&rt,// reinterpret_cast<void*>(rt),//contextData.get(),
                .errorContext = nullptr,
            };

            // Call your async function here, passing the callback
            char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
            ::start(args, std::move(c));
        });

        return promise.asObject(rt);
    }


        // auto promisePtr = std::make_shared<facebook::react::AsyncPromise<std::string>>(rt, jsInvoker_);

        // std::thread t([promisePtr]() {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        //     __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till thread");
        //     promisePtr->resolve("test?");
        // });

        // t.detach();
        // return std::move(*promisePtr);

    jsi::Value NativeSampleModuleCxx::startPromise6(jsi::Runtime &rt) {
        auto promiseSetup = [this](jsi::Runtime& rt, std::shared_ptr<react::Promise> promise) {
            // std::thread([this, rt = std::move(&rt), promise = std::move(promise)]() {
                auto responseCallback = [this, rt = std::move(&rt), promise = std::move(promise)](const char* data, int length) {
                    __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseCallback");

                    jsInvoker_->invokeAsync([this, rt = std::move(&rt), promise]() {
                        promise->resolve(jsi::Value(1));
                    });
                };

                CCallback callback = {
                    .onResponse = [](void* context, const char* data, int length) {
                        (*static_cast<decltype(responseCallback)*>(context))(data, length);
                    },
                    .onError = [](void* context, const char* error) {
                        // auto promise = static_cast<react::Promise*>(context);
                        // promise->resolve(jsi::Value(1));
                    },
                    .responseContext = new decltype(responseCallback)(std::move(responseCallback)),
                    .errorContext = nullptr,
                };
                // CCallback callback = {
                //     .onResponse = [](void* context, const char* data, int length) {
                //         auto promise = static_cast<react::Promise*>(context);
                //         promise->resolve(jsi::Value(1));
                //         // promise->resolve(std::string(data, length));
                //         // delete promise;  // Clean up the promise
                //     },
                //     .onError = [](void* context, const char* error) {
                //         auto promise = static_cast<react::Promise*>(context);
                //         promise->resolve(jsi::Value(1));
                //         // promise->reject(std::string(error));
                //         // delete promise;  // Clean up the promise
                //     },
                //     .responseContext = promise.get(),
                //     .errorContext = promise.get(),
                // };
                // Call your async function here, passing the callback
                char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
                ::start(args, callback);

            // }).detach();
        };

        return react::createPromiseAsJSIValue(rt, promiseSetup);
    }


   class ThreadSafeCallback {
   private:
       std::mutex mutex_;
       std::shared_ptr<react::CallInvoker> jsCallInvoker_;
       std::function<void()> callback_;

   public:
       ThreadSafeCallback(std::shared_ptr<react::CallInvoker> jsCallInvoker, std::function<void()> callback)
           : jsCallInvoker_(std::move(jsCallInvoker)), callback_(std::move(callback)) {}

       void operator()() {
           std::lock_guard<std::mutex> lock(mutex_);
           if (jsCallInvoker_) {
               jsCallInvoker_->invokeAsync([this]() {
                   std::lock_guard<std::mutex> callbackLock(mutex_);
                   if (callback_) {
                       callback_();
                   }
               });
           }
       }
   };



    static void handleOnResponse(jsi::Runtime& rt, const std::shared_ptr<react::Promise>& promise, const char* data, int length) {
       __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "Entering handleOnResponse");

       if (promise) {
           __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "Promise is not null, attempting to resolve");
           try {
               jsi::String result = jsi::String::createFromUtf8(rt, std::string(data, length));
               __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "Created jsi::String, resolving promise");
               promise->resolve(jsi::Value(1));
               __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "Promise resolved successfully");
           } catch (const std::exception& e) {
               __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", e.what());
           }
       } else {
           __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "Promise is null in handleOnResponse");
       }

       __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "Exiting handleOnResponse");

        // promise->resolve(jsi::String::createFromUtf8(rt, std::string(data, length)));
    }

    static void handleOnError(jsi::Runtime& rt, const std::shared_ptr<facebook::react::Promise>& promise, const char* error) {
        // promise->reject(jsi::String::createFromUtf8(rt, std::string(error)));
    }

    static void handleOnResponseThunk(void* context, const char* data, int length) {
        __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till handleOnResponseThunk");
        auto* params = static_cast<std::pair<jsi::Runtime*, std::shared_ptr<facebook::react::Promise>*>*>(context);
        handleOnResponse(*params->first, *params->second, data, length);
        // delete params;  // Clean up the context
    }

    static void handleOnErrorThunk(void* context, const char* error) {
        // auto* params = static_cast<std::pair<jsi::Runtime*, std::shared_ptr<facebook::react::Promise>*>*>(context);
        // handleOnError(*params->first, *params->second, error);
        // delete params;  // Clean up the context
    }

    // FINAL
    facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::startPromise7(jsi::Runtime &rt) {
        auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
        uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

        CCallback callback = {
            .onResponse = [](void* context, const char* data, int length) {
                uint64_t id = reinterpret_cast<uint64_t>(context);
                std::string encoded = base64_encode(data, length);
                // std::string response(data, length);
                PromiseKeeper::getInstance().resolvePromise(id, std::move(encoded));
            },
            .onError = [](void* context, const char* error) {
                uint64_t id = reinterpret_cast<uint64_t>(context);
                PromiseKeeper::getInstance().rejectPromise(id, std::string(error));
            },
            .responseContext = reinterpret_cast<void*>(promiseId),
            .errorContext = reinterpret_cast<void*>(promiseId)
        };

        char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill --db.bolt.auto-compact --db.bolt.auto-compact-min-age=0";
        ::start(args, callback);

        return *promise;
    }

    jsi::Value NativeSampleModuleCxx::getInfo3(jsi::Runtime &rt) {
        auto promiseSetup = [this](jsi::Runtime& rt, std::shared_ptr<react::Promise> promise) {
            // /*std::thread(*/[this, rt = std::move(&rt), promise = std::move(promise)]() {
                auto responseCallback = [this, rt = std::move(&rt), promise = std::move(promise)](const char* data, int length) {
                    __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseCallback");

                    jsInvoker_->invokeAsync([this, rt = std::move(&rt), promise]() {
                        promise->resolve(jsi::Value(1));
                    });
                };

                CCallback callback = {
                    .onResponse = [](void* context, const char* data, int length) {
                        (*static_cast<decltype(responseCallback)*>(context))(data, length);
                    },
                    .onError = [](void* context, const char* error) {
                        // auto promise = static_cast<react::Promise*>(context);
                        // promise->resolve(jsi::Value(1));
                    },
                    .responseContext = new decltype(responseCallback)(std::move(responseCallback)),
                    .errorContext = nullptr,
                };

                // Call your async function here, passing the callback
                char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
                char *emptyArray = NULL;
                int length = 0;
                ::getInfo(emptyArray, length, callback);
            // };/*).detach();*/
        };

        return react::createPromiseAsJSIValue(rt, promiseSetup);
    }


    void NativeSampleModuleCxx::callback(jsi::Runtime &rt, AsyncCallback<std::string> callback) {
        std::thread t([callback]() {
            callback.call("test?");
        });
        t.detach();
    }

    // jsi::Value promise(jsi::Runtime& rt) {

    // }


    jsi::Value NativeSampleModuleCxx::promise(jsi::Runtime &rt) {
        auto promiseSetup = [this](jsi::Runtime& rt, std::shared_ptr<react::Promise> promise) {
            std::thread([this, rt = std::move(&rt), promise = std::move(promise)]() {
                // Simulate some async work
                // std::this_thread::sleep_for(std::chrono::seconds(1));


                jsInvoker_->invokeAsync([rt = std::move(&rt), promise]() {
                    promise->resolve(jsi::Value(1));
                });


                // jsInvoker_->invokeAsync([rt = std::move(&rt), promise])() {
                //     promise->resolve(jsi::Value(1));
                //     // promise->resolve(jsi::String::createFromUtf8(rt,"Promise resolved!"));
                // });
            }).detach();
        };

        return react::createPromiseAsJSIValue(rt, promiseSetup);


        // auto promise = facebook::react::AsyncPromise<std::string>(rt, jsInvoker_);

        // std::thread t([promise]() {
        //     // promise.resolve("test");
        // });

        // t.detach();

        // return promise;
    }


    // struct ContextData {
    //     jsi::Runtime* rt;
    //     std::shared_ptr<jsi::Function> callback;
    //     // facebook::react::CallInvoker* jsInvoker;
    // };

    void NativeSampleModuleCxx::startPromiseCallback(jsi::Runtime &rt, AsyncCallback<std::string> callback) {
        // std::thread t([c = std::move(callback)]() {
        //     c.call("testhoho");
        // });

        // t.detach();

        // auto sharedCallback = std::make_shared<AsyncCallback<std::string>>(std::move(callback));

        auto onResponseCallback = [sharedCallback = std::move(callback)](const char* data, int length) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onResponseCallback");
            // (*sharedCallback).call("Yeees det fungerar");
            sharedCallback.call("Yeees det fungerar");
        };

        CCallback c = {
            .onResponse = [](void* context, const char* data, int length) {
                (*static_cast<decltype(onResponseCallback)*>(context))(data, length);
            },
            .onError = [](void* context, const char* error) {
            },
            .responseContext = new decltype(onResponseCallback)(std::move(onResponseCallback)),//&onResponseCallback, //&rt,// reinterpret_cast<void*>(rt),//contextData.get(),
            .errorContext = nullptr,
        };

        char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
        ::start(args, c);
    }

    void NativeSampleModuleCxx::startPromiseCallback2(jsi::Runtime &rt, AsyncCallback<std::string> callback) {
        // Static storage for the callback
        static std::function<void(const char*, int)> staticCallback;

        // Move the callback into the static storage
        staticCallback = [callback = std::move(callback)](const char* data, int length) mutable {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onResponseCallback");
            callback.call("Yeees det fungerar");
        };

        CCallback c = {
            .onResponse = [](void* context, const char* data, int length) {
                staticCallback(data, length);
            },
            .onError = [](void* context, const char* error) {
                // Handle error if needed
            },
            .responseContext = nullptr,  // We don't need to use this anymore
            .errorContext = nullptr,
        };

        char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
        ::start(args, c);
    }

    void NativeSampleModuleCxx::startPromiseCallback3(jsi::Runtime &rt, AsyncCallback<std::string> callback) {
        auto sharedCallback = std::make_shared<AsyncCallback<std::string>>(std::move(callback));

        auto onResponseCallback = [sharedCallback = std::move(sharedCallback)](const char* data, int length) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onResponseCallback");
            (*sharedCallback).call("Yeees det fungerar");
        };


        CCallback c = {
            .onResponse = [](void* context, const char* data, int length) {
                (*static_cast<decltype(onResponseCallback)*>(context))(data, length);
            },
            .onError = [](void* context, const char* error) {
                // Handle error if needed
            },
            .responseContext = &onResponseCallback,
            .errorContext = nullptr,
        };

        char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
        ::start(args, std::move(c));
    }

    facebook::react::AsyncPromise<std::string> NativeSampleModuleCxx::getInfo(jsi::Runtime &rt) {
        auto* promisePtr = new facebook::react::AsyncPromise<std::string>(rt, jsInvoker_);

        CCallback callback = {
            .onResponse = [](void* context, const char* data, int length) {
                auto promise = static_cast<facebook::react::AsyncPromise<std::string>*>(context);
                promise->resolve(std::string(data, length));
                // delete promise;  // Clean up the promise
            },
            .onError = [](void* context, const char* error) {
                auto promise = static_cast<facebook::react::AsyncPromise<std::string>*>(context);
                promise->reject(std::string(error));
                // delete promise;  // Clean up the promise
            },
            .responseContext = promisePtr,
            .errorContext = promisePtr
        };

        char *emptyArray = NULL;
        int length = 0;
        ::getInfo(emptyArray, length, callback);

        return *promisePtr;
    }

        // std::thread([jsInvoker_ = this->jsInvoker_, promise]() mutable {
        //     __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "inside thread");

        //     jsInvoker_->invokeAsync([jsInvoker_, promise]() mutable {
        //         promise.resolve("test?");
        //     });
        // }).detach(); // Detach the thread so it can run independently

        // return promise;


    // FINAL
    facebook::react::AsyncPromise2<std::string> NativeSampleModuleCxx::getInfo4(jsi::Runtime &rt) {
        auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);
        uint64_t promiseId = PromiseKeeper::getInstance().addPromise(promise);

        CCallback callback = {
            .onResponse = [](void* context, const char* data, int length) {
                uint64_t id = reinterpret_cast<uint64_t>(context);
                std::string encoded = base64_encode(data, length);
                // std::string response(data, length);
                PromiseKeeper::getInstance().resolvePromise(id, std::move(encoded));
            },
            .onError = [](void* context, const char* error) {
                uint64_t id = reinterpret_cast<uint64_t>(context);
                PromiseKeeper::getInstance().rejectPromise(id, std::string(error));
            },
            .responseContext = reinterpret_cast<void*>(promiseId),
            .errorContext = reinterpret_cast<void*>(promiseId)
        };

        char *emptyArray = NULL;
        int length = 0;
        ::getInfo(emptyArray, length, callback);

        // Return a copy of the promise
        return *promise;



        // auto promise = std::make_shared<facebook::react::AsyncPromise2<std::string>>(rt, jsInvoker_);

        // // Create a shared_ptr to hold the responseCallback
        // auto callbackPtr = std::make_shared<std::function<void(const char*, int)>>(
        //     [jsInvoker = this->jsInvoker_, promise](const char* data, int length) {
        //         __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseCallback");

        //         jsInvoker->invokeAsync([promise]() {
        //             promise->resolve("test?");
        //         });
        //     }
        // );

        // CCallback callback = {
        //     .onResponse = [](void* context, const char* data, int length) {
        //         auto& callback = *static_cast<std::shared_ptr<std::function<void(const char*, int)>>*>(context);
        //         (*callback)(data, length);
        //     },
        //     .onError = [](void* context, const char* error) {
        //         // Implement error handling here
        //     },
        //     .responseContext = new std::shared_ptr<std::function<void(const char*, int)>>(callbackPtr),
        //     .errorContext = nullptr,
        // };

        // // char *emptyArray = NULL;
        // // int length = 0;
        // // ::getInfo(emptyArray, length, callback);

        // char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
        // ::start(args, callback);

        // return *promise;



        // auto promise = facebook::react::AsyncPromise2<std::string>(rt, jsInvoker_);

        // auto responseCallback = [&rt, jsInvoker_ = this->jsInvoker_, promise](const char* data, int length) mutable {
        //     __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseCallback");

        //     // jsInvoker_->invokeAsync([jsInvoker_, promise]() mutable {
        //         promise.resolve("test?");
        //     // });
        // };

        // CCallback callback = {
        //     .onResponse = [](void* context, const char* data, int length) {
        //         (*static_cast<decltype(responseCallback)*>(context))(data, length);
        //     },
        //     .onError = [](void* context, const char* error) {
        //         // auto promise = static_cast<react::Promise*>(context);
        //         // promise->resolve(jsi::Value(1));
        //     },
        //     .responseContext = &responseCallback,//new decltype(responseCallback)(std::move(responseCallback)), // Needs to fixed. Memory leaks
        //     .errorContext = nullptr,
        // };

        // char *emptyArray = NULL;
        // int length = 0;
        // ::getInfo(emptyArray, length, callback);

        // return promise;
    }

    jsi::Value NativeSampleModuleCxx::getInfo2(jsi::Runtime &rt) {
        auto promise = margelo::Promise::createPromise(rt, [](jsi::Runtime& runtime, std::shared_ptr<margelo::Promise> promise) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "createPromise");

            auto onResponseCallback = [r = std::move(&runtime), p = std::move(promise)](const char* data, int length) {
                __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onResponseCallback");
                p->resolve(jsi::String::createFromUtf8(*r, std::string(data, length)));
            };

            CCallback c = {
                .onResponse = [](void* context, const char* data, int length) {
                    (*static_cast<decltype(onResponseCallback)*>(context))(data, length);
                },
                .onError = [](void* context, const char* error) {
                },
                .responseContext = new decltype(onResponseCallback)(std::move(onResponseCallback)),//&onResponseCallback, //&rt,// reinterpret_cast<void*>(rt),//contextData.get(),
                .errorContext = nullptr,
            };

            char *emptyArray = NULL;
            int length = 0;
            ::getInfo(emptyArray, length, c);
        });

        return promise.asObject(rt);
    }

    // FINAL
    facebook::jsi::Function NativeSampleModuleCxx::getInfoCallback(jsi::Runtime &rt, AsyncCallback2<std::string> onResponse, AsyncCallback2<std::string> onError) {
        auto sharedOnResponse = std::make_shared<AsyncCallback2<std::string>>(std::move(onResponse));
        auto sharedOnError = std::make_shared<AsyncCallback2<std::string>>(std::move(onError));
        uint64_t callbackId = CallbackKeeper::getInstance().addCallbacks(sharedOnResponse, sharedOnError);

        CCallback c = {
            .onResponse = &callbackOnResponseStatic,
            .onError = &callbackOnErrorStatic,
            .responseContext = reinterpret_cast<void*>(callbackId),
            .errorContext = reinterpret_cast<void*>(callbackId),
        };

        // CCallback c = {
        //     .onResponse = [](void* context, const char* data, int length) {
        //         uint64_t id = reinterpret_cast<uint64_t>(context);
        //         CallbackKeeper::getInstance().invokeCallback(id, std::string(data, length));
        //     },
        //     .onError = [](void* context, const char* error) {
        //     },
        //     .responseContext = reinterpret_cast<void*>(callbackId),
        //     .errorContext = reinterpret_cast<void*>(callbackId),
        // };

        char *emptyArray = NULL;
        int length = 0;
        ::getInfo(emptyArray, length, c);

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


        // auto onResponseCallback = [sharedCallback = std::move(callback)](const char* data, int length) {
        //     __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onResponseCallback");
        //     sharedCallback.call(std::string(data, length));
        // };

        // CCallback c = {
        //     .onResponse = [](void* context, const char* data, int length) {
        //         (*static_cast<decltype(onResponseCallback)*>(context))(data, length);
        //     },
        //     .onError = [](void* context, const char* error) {
        //     },
        //     .responseContext = new decltype(onResponseCallback)(std::move(onResponseCallback)),//&onResponseCallback, //&rt,// reinterpret_cast<void*>(rt),//contextData.get(),
        //     .errorContext = nullptr,
        // };

        // char *emptyArray = NULL;
        // int length = 0;
        // ::getInfo(emptyArray, length, c);
    }

    void NativeSampleModuleCxx::reg(jsi::Runtime &rt) {
        auto foo = jsi::Function::createFromHostFunction(
			rt,
			jsi::PropNameID::forAscii(rt, "foo"),
			1,
			[invoker = jsInvoker_](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value
			{
				if (count < 1 || !arguments[0].isObject() || !arguments[0].getObject(runtime).isFunction(runtime))
				{
					throw jsi::JSError(runtime, "Expected a function as the first argument");
				}

				// Create a shared reference to the user callback
				auto userCallbackRef = std::make_shared<jsi::Object>(arguments[0].getObject(runtime));

				// Lambda to be run in the new thread
				auto f = [invoker2 = invoker, &runtime, userCallbackRef](const char* data, int length)
				{
					auto val = std::make_shared<std::string>("hello world");
					auto error = std::make_shared<jsi::Value>(jsi::Value::undefined());

					// Periodically log messages to Android log and sleep for 5 seconds
					// while (true)
					// {
						__android_log_print(ANDROID_LOG_INFO, "MyApp", "Log message to Android");

                        // invoker2->invokeAsync([]() {
                        //     // __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "invokeAsync");
                        // });


                        if (invoker2 == nullptr) {
                            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "invoker2 is null");
                        }

                        if (invoker2 == NULL) {
                            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "invoker2 is null");
                        }
                        // userCallbackRef->asFunction(runtime).call(runtime, *error, *val);
						// std::this_thread::sleep_for(std::chrono::seconds(5));
					// }
				};


                auto responseThunk = [](void* context, const char* data, int length) {
                    __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till responseThunk");

                    (*static_cast<decltype(f)*>(context))(data, length);
                };


                CCallback callback = {
                    .onResponse = responseThunk,
                    .onError = [](void *, const char *) {
                        __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "kommer till onError");
                    },
                    .responseContext = &f,
                    .errorContext = NULL
                };


				// // Launch the lambda in a new thread
				// std::thread thread_object(f);
				// thread_object.detach();


                char* args = "--lnddir=/data/user/0/com.turbolnd/files --noseedbackup --bitcoin.active --bitcoin.mainnet --bitcoin.node=neutrino --feeurl=\"https://nodes.lightning.computer/fees/v1/btc-fee-estimates.json\" --routing.assumechanvalid --tlsdisableautofill";
                ::start(args, callback);

				return jsi::Value::undefined();
			});

		rt.global().setProperty(rt, "foo", std::move(foo));
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
        char *emptyArray = NULL;
        int length = 0;
        uintptr_t streamPtr = ::channelAcceptor(recvStream);

        if (streamPtr != 0) {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "Bidi stream started");
            auto hostObject = std::make_shared<StreamHostObject>(streamPtr);
            return jsi::Object::createFromHostObject(rt, hostObject);
        } else {
            __android_log_write(ANDROID_LOG_ERROR, "com.turbolnd", "Bidi stream fail");
            throw jsi::JSError(rt, "Failed to start channel acceptor");
        }
    }



facebook::react::AsyncPromise<std::string> NativeSampleModuleCxx::prom(jsi::Runtime& rt) {
    auto promise = facebook::react::AsyncPromise<std::string>(rt, jsInvoker_);
    promise.resolve("result!");
    return promise;
}



} // namespace facebook::react




/*
              auto multiply = jsi::Function::createFromHostFunction(
                rt, // JSI runtime instance
                jsi::PropNameID::forAscii(rt, "multiply"), // Internal function name
                1, // Number of arguments in function
                // This is a C++ lambda function, the empty [] at the beginning is used to capture pointer/references so that they don't get de-allocated
                // Then you get another instance of the runtime to use inside the function, a "this" value from the javascript world, a pointer to the arguments (you can treat it as an array) and finally a count for the number of arguments
                // Finally the function needs to return a jsi::Value (read JavaScript value)
                [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {

                // the jsi::Value has a lot of helper methods for you to manipulate the data
                if(!arguments[0].isNumber() || !arguments[1].isNumber()) {
                    // jsi::detail::throwJSError(runtime, "Non number arguments passed to sequel");
                }

                double res = 42;
                return jsi::Value(res);
                }
            );

            // Registers the function on the global object
            rt.global().setProperty(rt, "multiply", std::move(multiply));
*/


//https://github.com/facebook/hermes/issues/564






/*
    void NativeSampleModuleCxx::reg(jsi::Runtime &rt) {
        auto foo = jsi::Function::createFromHostFunction(
			rt,
			jsi::PropNameID::forAscii(rt, "foo"),
			1,
			[](jsi::Runtime &runtime, const jsi::Value &thisValue, const jsi::Value *arguments, size_t count) -> jsi::Value
			{
				if (count < 1 || !arguments[0].isObject() || !arguments[0].getObject(runtime).isFunction(runtime))
				{
					throw jsi::JSError(runtime, "Expected a function as the first argument");
				}

				// Create a shared reference to the user callback
				auto userCallbackRef = std::make_shared<jsi::Object>(arguments[0].getObject(runtime));

				// Lambda to be run in the new thread
				auto f = [&runtime, userCallbackRef]()
				{
					auto val = std::make_shared<std::string>("hello world");
					auto error = std::make_shared<jsi::Value>(jsi::Value::undefined());

					// Periodically log messages to Android log and sleep for 5 seconds
					while (true)
					{
						__android_log_print(ANDROID_LOG_INFO, "MyApp", "Log message to Android");
                        userCallbackRef->asFunction(runtime).call(runtime, *error, *val);
						std::this_thread::sleep_for(std::chrono::seconds(5));
					}
				};

				// // Launch the lambda in a new thread
				std::thread thread_object(f);
				thread_object.detach();

				return jsi::Value::undefined();
			});

		rt.global().setProperty(rt, "foo", std::move(foo));
    }

*/
