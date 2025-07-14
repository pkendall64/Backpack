#pragma once

#include "module_base.h"

class HDZero : public MSPModuleBase
{
public:
    explicit HDZero(Stream *port) : MSPModuleBase(port) {};
    void Init();
    int BootDelay() override { return 7000; }
    void SendIndexCmd(uint8_t index);
    uint8_t GetChannelIndex();
    void SetChannelIndex(uint8_t index);
    uint8_t GetRecordingState();
    void SetRecordingState(uint8_t recordingState, uint16_t delay);
    void SendHeadTrackingEnableCmd(bool enable);
    void SetOSD(mspPacket_t *packet);
    void SetRTC();
};
