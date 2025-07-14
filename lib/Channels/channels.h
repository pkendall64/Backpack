#pragma once

#include <Arduino.h>

extern const uint16_t frequencyTable[48];

uint16_t GetFrequency(uint8_t index);
uint8_t GetBand(uint8_t index);
uint8_t GetChannel(uint8_t index);