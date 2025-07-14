#pragma once

#include "module_base.h"
#include <Arduino.h>

typedef enum {
    ModeMix = 0,
    ModeDiversity
} videoMode_t;

class SteadyView : public ModuleBase
{
public:
    void Init();
    void SendIndexCmd(uint8_t index);
    void SetMode(videoMode_t mode);

private:
    void rtc6705WriteRegister(uint32_t buf);
    uint32_t rtc6705readRegister(uint8_t readRegister);
    uint8_t currentIndex;
};
