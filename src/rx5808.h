#pragma once

#include "module_base.h"

class RX5808 : public ModuleBase
{
public:
    void Init();
    void SendIndexCmd(uint8_t index);

private:
    void rtc6705WriteRegister(uint32_t buf);
    uint32_t rtc6705readRegister(uint8_t readRegister);
    void EnableSPIMode();
    bool SPIModeEnabled = false;
};
