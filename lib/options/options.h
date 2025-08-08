#pragma once
#include <Arduino.h>

extern const unsigned char target_name[];
extern const uint8_t target_name_size;
extern const char PROGMEM compile_options[];

typedef struct {
    uint8_t uid[6];
    bool    hasUID;
    char    home_wifi_ssid[33];
    char    home_wifi_password[65];
    char    product_name[65];
} firmware_options_t;

constexpr size_t ELRSOPTS_OPTIONS_SIZE = 512;

extern firmware_options_t firmwareOptions;

extern bool options_init();
extern String& getOptions();
extern String& getHardware();

#include "EspFlashStream.h"
bool options_HasStringInFlash(EspFlashStream &strmFlash);
void options_SetTrueDefaults();
bool hardware_init(EspFlashStream &strmFlash);
