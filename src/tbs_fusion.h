#pragma once

#include "module_base.h"
#include <Arduino.h>

class Fusion : public ModuleBase
{
public:
    void Init();
    int BootDelay() { return 1000; }
    void SendIndexCmd(uint8_t index);
    void SendLinkTelemetry(uint8_t *rawCrsfPacket);
    void SendBatteryTelemetry(uint8_t *rawCrsfPacket);
};
