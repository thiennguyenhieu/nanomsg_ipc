#pragma once
#include "ipc_interface.hpp"
#include <atomic>
#include <string>

class IpcClient {
public:
    static IpcClient& instance();

    template<typename T>
    Result_t sendRequest(const std::string& command, T& outData);

    void registerStatusCallback(void (*cb)(const UiApplianceStatus_t*));
    void registerErrorCallback(void (*cb)(const char*));
    void start();

private:
    IpcClient();
    ~IpcClient();

    std::atomic<bool> running_;
    void (*callback_)(const UiApplianceStatus_t*);
    void (*errorCallback_)(const char*);
};