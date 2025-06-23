#pragma once
#include "ipc_interface.hpp"
#include <atomic>

class IpcClient {
public:
    static IpcClient& instance();

    Result_t getStatus(UiApplianceStatus_t& status);
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