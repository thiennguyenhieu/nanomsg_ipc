#pragma once
#include <stdint.h>

typedef enum {
    RESULT_OK,
    RESULT_FAIL
} Result_t;

typedef struct {
    bool isOn;
    uint8_t temperature;
} UiApplianceStatus_t;