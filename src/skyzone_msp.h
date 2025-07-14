#pragma once

#include "msp.h"
#include "msptypes.h"
#include "module_base.h"
#include <Arduino.h>

class SkyzoneMSP : public MSPModuleBase
{
public:
    SkyzoneMSP(Stream *port) : MSPModuleBase(port) {};
    void Init();
    int BootDelay() { return 2000; }
    void SendIndexCmd(uint8_t index);
    uint8_t GetChannelIndex();
    void SetChannelIndex(uint8_t index);
    uint8_t GetRecordingState();
    void SetRecordingState(uint8_t recordingState, uint16_t delay);
    void SetOSD(mspPacket_t *packet);
    void SendHeadTrackingEnableCmd(bool enable);
    void Loop(uint32_t now);

private:
    void SendRecordingState();

    uint8_t     m_recordingState;
    uint16_t    m_delay;
    uint32_t    m_delayStartMillis;
};
