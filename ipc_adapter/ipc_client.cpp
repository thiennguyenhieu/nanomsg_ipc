#include "ipc_client.hpp"
#include "reqrep.h"
#include "pubsub.h"
#include <thread>
#include <cstring>
#include <iostream>

IpcClient& IpcClient::instance() {
    static IpcClient client;
    return client;
}

IpcClient::IpcClient()
    : running_(false), callback_(nullptr), errorCallback_(nullptr) {}

IpcClient::~IpcClient() {
    running_ = false;
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
        std::cout << "[THREAD] Receiver thread started. Thread ID: " << std::this_thread::get_id() << std::endl;

        int subSock = nn_socket(AF_SP, NN_SUB);
        if (subSock < 0 || nn_connect(subSock, PUB_URL) < 0) {
            std::cerr << "[THREAD] Failed to open/ connect SUB socket\n";
            return;
        }

        nn_setsockopt(subSock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);

        while (running_) {
            char* buf = nullptr;
            int bytes = nn_recv(subSock, &buf, NN_MSG, 0);
            if (bytes > 0 && buf) {
                std::cout << "[THREAD] Received message on thread: " << std::this_thread::get_id() << std::endl;

                if (std::strncmp(buf, "STATUS", 6) == 0 && callback_) {
                    callback_(reinterpret_cast<const UiApplianceStatus_t*>(buf + 6));
                } else if (std::strncmp(buf, "ERROR", 5) == 0 && errorCallback_) {
                    errorCallback_(buf + 5);
                }
                nn_freemsg(buf);
            }
        }

        nn_close(subSock);
    }).detach();
}
