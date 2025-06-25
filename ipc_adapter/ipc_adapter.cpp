#include "ipc_client.hpp"

void startMessageReceiver() { 
    IpcClient::instance().start(); 
}

Result_t getApplianceStatus(UiApplianceStatus_t* status) {
    if (!status) return RESULT_FAIL;
    return IpcClient::instance().sendRequest("getStatus", *status);
}

void registerApplianceStatusCallback(void (*cb)(const UiApplianceStatus_t*)) {
    IpcClient::instance().registerStatusCallback(cb);
}

void registerSystemErrorCallback(void (*cb)(const char*)) {
    IpcClient::instance().registerErrorCallback(cb);
}