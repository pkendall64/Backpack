#pragma once

extern const unsigned char target_name[];
extern const uint8_t target_name_size;
extern const char PROGMEM compile_options[];

enum device_type_e
{
    DEVICE_RAPIDFIRE,
    DEVICE_RX5808,
    DEVICE_STEADYVIEW,
    DEVICE_FUSION,
    DEVICE_HDZERO,
    DEVICE_SKYZONE_MSP,
    DEVICE_ORQA,
    DEVICE_DIY_AAT,
    DEVICE_MFD_CROSSBOW
};

typedef struct {
    uint8_t uid[6];
    bool    hasUID;
    char    home_wifi_ssid[33];
    char    home_wifi_password[65];
    char    product_name[65];
    device_type_e     deviceType;
} firmware_options_t;

extern firmware_options_t firmwareOptions;

extern bool options_init();