#pragma once

#include "module_base.h"

class Rapidfire : public ModuleBase
{
public:
    void Init();
    int BootDelay() { return 2000; }
    void SendBuzzerCmd();
    void SendIndexCmd(uint8_t index);
    void SendChannelCmd(uint8_t channel);
    void SendBandCmd(uint8_t band);

private:
    void SendSPI(uint8_t* buf, uint8_t bufLen);
    void EnableSPIMode();
    uint8_t crc8(uint8_t* buf, uint8_t bufLen);
    bool SPIModeEnabled = false;
};
