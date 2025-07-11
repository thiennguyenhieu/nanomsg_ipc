#include <thread>
#include <chrono>
#include <cstring>
#include <iostream>
#include "ipc_common.hpp"
#include "ipc_types.hpp"
#include "nn.h"
#include "reqrep.h"
#include "pubsub.h"

void handleRequests() {
    int sock = nn_socket(AF_SP, NN_REP);
    nn_bind(sock, REQ_URL);

    while (true) {
        char* buf = nullptr;
        int bytes = nn_recv(sock, &buf, NN_MSG, 0);
        if (bytes > 0 && strncmp(buf, "getStatus", 9) == 0) {
            UiApplianceStatus_t status = {true, 55};
            nn_send(sock, &status, sizeof(status), 0);
        }
        nn_freemsg(buf);
    }
}

void publishUpdates() {
    int pubSock = nn_socket(AF_SP, NN_PUB);
    nn_bind(pubSock, PUB_URL);

    while (true) {
        UiApplianceStatus_t s = {true, static_cast<uint8_t>(rand() % 100)};
        char msg[6 + sizeof(s)];
        memcpy(msg, "STATUS", 6);
        memcpy(msg + 6, &s, sizeof(s));
        nn_send(pubSock, msg, sizeof(msg), 0);

        if (rand() % 4 == 0) {
            const char* err = "Fan failure!";
            char errMsg[5 + 128] = {0};
            memcpy(errMsg, "ERROR", 5);
            strcpy(errMsg + 5, err);
            nn_send(pubSock, errMsg, 5 + strlen(err) + 1, 0);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main() {
    std::thread(handleRequests).detach();
    std::thread(publishUpdates).detach();

    // prevent the program from exiting immediately for testing purpose
    std::this_thread::sleep_for(std::chrono::hours(1));

    return 0;
}
