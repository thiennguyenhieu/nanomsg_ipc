#include "ipc_interface.hpp"
#include <iostream>
#include <thread>

void onStatus(const UiApplianceStatus_t* s) {
    std::cout << "[STATUS] ON=" << s->isOn << ", Temp=" << (int)s->temperature << std::endl;
}

void onError(const char* msg) {
    std::cerr << "[ERROR] " << msg << std::endl;
}

int main() {
    startMessageReceiver();
    registerApplianceStatusCallback(onStatus);
    registerSystemErrorCallback(onError);

    UiApplianceStatus_t status;
    if (getApplianceStatus(&status) == RESULT_OK) {
        std::cout << "Initial Status: ON=" << status.isOn << ", Temp=" << (int)status.temperature << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::minutes(10));
    return 0;
}
