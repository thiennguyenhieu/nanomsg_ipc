#include "ipc_client.hpp"
#include "ipc_common.hpp"
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/pubsub.h>
#include <thread>
#include <cstring>

IpcClient& IpcClient::instance() {
    static IpcClient client;
    return client;
}

IpcClient::IpcClient() : running_(false), callback_(nullptr), errorCallback_(nullptr) {}
IpcClient::~IpcClient() { running_ = false; }

Result_t IpcClient::getStatus(UiApplianceStatus_t& status) {
    int sock = nn_socket(AF_SP, NN_REQ);
    nn_connect(sock, REQ_URL);

    const char* req = "getStatus";
    nn_send(sock, req, strlen(req), 0);

    char* buf = nullptr;
    int bytes = nn_recv(sock, &buf, NN_MSG, 0);

    if (bytes == sizeof(UiApplianceStatus_t)) {
        memcpy(&status, buf, sizeof(UiApplianceStatus_t));
        nn_freemsg(buf);
        nn_close(sock);
        return RESULT_OK;
    }

    nn_freemsg(buf);
    nn_close(sock);
    return RESULT_FAIL;
}

void IpcClient::registerStatusCallback(void (*cb)(const UiApplianceStatus_t*)) {
    callback_ = cb;
}

void IpcClient::registerErrorCallback(void (*cb)(const char*)) {
    errorCallback_ = cb;
}

void IpcClient::start() {
    if (running_.exchange(true)) return;

    std::thread([this]() {
        int subSock = nn_socket(AF_SP, NN_SUB);
        nn_connect(subSock, PUB_URL);
        nn_setsockopt(subSock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);

        while (running_) {
            char* buf = nullptr;
            int bytes = nn_recv(subSock, &buf, NN_MSG, 0);
            if (bytes > 0) {
                if (strncmp(buf, "STATUS", 6) == 0 && callback_) {
                    callback_(reinterpret_cast<const UiApplianceStatus_t*>(buf + 6));
                } else if (strncmp(buf, "ERROR", 5) == 0 && errorCallback_) {
                    errorCallback_(buf + 5);
                }
            }
            nn_freemsg(buf);
        }
        nn_close(subSock);
    }).detach();
}