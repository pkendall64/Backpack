#pragma once

#include "device.h"

extern device_t WIFI_device;

extern const char *VERSION;

#if defined(TARGET_TX_BACKPACK)
bool SendTxBackpackTelemetryViaUDP(const uint8_t *data, uint16_t size);
#endif
