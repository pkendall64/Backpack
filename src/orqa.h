#pragma once

#include "module_base.h"

class Orqa : public ModuleBase
{
public:
    void Init();
    void SendIndexCmd(uint8_t index);
    int BootDelay() { return 7000; }
private:
    uint8_t GHSTChannel(uint8_t band, uint8_t channel);
    void SendGHSTUpdate(uint16_t freq, uint8_t ghstChannel);
};