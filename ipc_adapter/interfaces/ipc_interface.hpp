#pragma once
#include "ipc_types.hpp"

void startMessageReceiver();
Result_t getApplianceStatus(UiApplianceStatus_t* status);
void registerApplianceStatusCallback(void (*callback)(const UiApplianceStatus_t*));
void registerSystemErrorCallback(void (*callback)(const char*));