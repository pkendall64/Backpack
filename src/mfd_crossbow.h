#pragma once

#include "module_base.h"

class MFDCrossbow : public ModuleBase
{
public:
    MFDCrossbow(HardwareSerial *port);
    void SendGpsTelemetry(crsf_packet_gps_t *packet);
    void Loop(uint32_t now);

private:
    void SendHeartbeat();
    void SendGpsRawInt();
    void SendGlobalPositionInt();

    HardwareSerial *m_port;
    uint32_t gpsLastSent;
    uint32_t gpsLastUpdated;

    int16_t heading;    // Geographical heading angle in degrees
    float lat;          // GPS latitude in degrees (example: 47.123456)
    float lon;          // GPS longitude in degrees
    float alt;          // Relative flight altitude in m
    float groundspeed;  // Groundspeed in m/s
    int16_t gps_sats;   // Number of visible GPS satellites
    int32_t gps_alt;    // GPS altitude (Altitude above MSL)
    float gps_hdop;     // GPS HDOP
    uint8_t fixType;    // GPS fix type. 0-1: no fix, 2: 2D fix, 3: 3D fix
};
