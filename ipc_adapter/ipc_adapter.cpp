#include "ipc_client.hpp"

extern "C" {
    void run() { IpcClient::instance().start(); }
    Result_t getApplianceStatus(UiApplianceStatus_t* status) {
        return status ? IpcClient::instance().getStatus(*status) : RESULT_FAIL;
    }
    void registerApplianceStatusCallback(void (*cb)(const UiApplianceStatus_t*)) {
        IpcClient::instance().registerStatusCallback(cb);
    }
    void registerSystemErrorCallback(void (*cb)(const char*)) {
        IpcClient::instance().registerErrorCallback(cb);
    }
}