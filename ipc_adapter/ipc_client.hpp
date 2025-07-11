#pragma once

#include <atomic>
#include <string>
#include <cstring>  // for memcpy
#include "nn.h"
#include "reqrep.h"
#include "ipc_common.hpp"
#include "ipc_interface.hpp"

class IpcClient {
public:
    // Singleton access
    static IpcClient& instance();

    // Generic request-response communication
    template<typename T>
    Result_t sendRequest(const std::string& command, T& outData);

    // Register callbacks for subscription messages
    void registerStatusCallback(void (*cb)(const UiApplianceStatus_t*));
    void registerErrorCallback(void (*cb)(const char*));

    // Start the subscriber loop in a background thread
    void start();

private:
    IpcClient();
    ~IpcClient();

    std::atomic<bool> running_;
    void (*callback_)(const UiApplianceStatus_t*);
    void (*errorCallback_)(const char*);
};

// Template definition must be in header
template<typename T>
Result_t IpcClient::sendRequest(const std::string& command, T& outData) {
    int sock = nn_socket(AF_SP, NN_REQ);
    if (sock < 0) return RESULT_FAIL;

    if (nn_connect(sock, REQ_URL) < 0) {
        nn_close(sock);
        return RESULT_FAIL;
    }

    if (nn_send(sock, command.c_str(), command.size(), 0) < 0) {
        nn_close(sock);
        return RESULT_FAIL;
    }

    char* buf = nullptr;
    int bytes = nn_recv(sock, &buf, NN_MSG, 0);
    if (bytes == sizeof(T)) {
        std::memcpy(&outData, buf, sizeof(T));
        nn_freemsg(buf);
        nn_close(sock);
        return RESULT_OK;
    }

    if (buf) nn_freemsg(buf);
    nn_close(sock);
    return RESULT_FAIL;
}
