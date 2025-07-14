#pragma once

#include <Arduino.h>
#include "crsf_protocol.h"
#include "msp.h"

class ModuleBase
{
public:
    virtual ~ModuleBase() = default;

    virtual void Init() {}
    virtual int BootDelay() { return 0; }
    virtual void SendIndexCmd(uint8_t index) {}
    virtual void SetRecordingState(uint8_t recordingState, uint16_t delay) {}
    virtual void SetOSD(mspPacket_t *packet) {}
    virtual void SendHeadTrackingEnableCmd(bool enable) {}
    virtual void SetRTC() {}
    virtual void SendLinkTelemetry(uint8_t *rawCrsfPacket) {}
    virtual void SendBatteryTelemetry(uint8_t *rawCrsfPacke) {}
    virtual void SendGpsTelemetry(crsf_packet_gps_t *packet) {}
    virtual void Loop(uint32_t now);
};

class MSPModuleBase : public ModuleBase
{
public:
    explicit MSPModuleBase(Stream *port) : m_port(port) {}
    void Loop(uint32_t) override;

private:
    void sendResponse(uint16_t function, const uint8_t *response, uint32_t responseSize);

protected:
    Stream *m_port;
    MSP msp;
};