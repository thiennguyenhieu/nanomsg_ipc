#include "ipc_interface.hpp"
#include <iostream>
#include <thread>

void onStatus(const UiApplianceStatus_t* s) {
    std::cout << "[STATUS] Thread ID: " << std::this_thread::get_id()
              << ", ON=" << s->isOn << ", Temp=" << static_cast<int>(s->temperature) << std::endl;
}

void onError(const char* msg) {
    std::cerr << "[ERROR] Thread ID: " << std::this_thread::get_id()
              << ", Msg=" << msg << std::endl;
}

int main() {
    std::cout << "[MAIN] Thread ID: " << std::this_thread::get_id() << std::endl;

    startMessageReceiver();
    registerApplianceStatusCallback(onStatus);
    registerSystemErrorCallback(onError);

    UiApplianceStatus_t status;
    if (getApplianceStatus(&status) == RESULT_OK) {
        std::cout << "Initial Status: ON=" << status.isOn << ", Temp=" << (int)status.temperature << std::endl;
    }

    // prevent the program from exiting immediately for testing purpose
    std::this_thread::sleep_for(std::chrono::minutes(10));

    return 0;
}
