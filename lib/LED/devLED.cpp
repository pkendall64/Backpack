#include <Arduino.h>
#include "common.h"
#include "device.h"
#include "hardware.h"

#if defined(TARGET_RX)
extern bool connectionHasModelMatch;
#endif

constexpr uint8_t LEDSEQ_WIFI_UPDATE[] = { 2, 3 };     // 20ms on, 30ms off
constexpr uint8_t LEDSEQ_BINDING[] = { 10, 10, 10, 100 };   // 2x 100ms blink, 1s pause

static bool blipLED;

static const uint8_t *_durations;
static uint8_t _count;
static uint8_t _counter = 0;

static uint16_t updateLED()
{
    if(_counter % 2 == 1)
        digitalWrite(GPIO_PIN_LED, LOW ^ GPIO_PIN_LED_INVERTED);
    else
        digitalWrite(GPIO_PIN_LED, HIGH ^ GPIO_PIN_LED_INVERTED);
    if (_counter >= _count)
    {
        _counter = 0;
    }
    return _durations[_counter++] * 10;
}

static uint16_t flashLED(const uint8_t durations[], uint8_t count)
{
    _counter = 0;
    _durations = durations;
    _count = count;
    return updateLED();
}

static bool initialize()
{
    if (GPIO_PIN_LED == UNDEF_PIN)
    {
        return false;
    }
    pinMode(GPIO_PIN_LED, OUTPUT);
    digitalWrite(GPIO_PIN_LED, HIGH ^ GPIO_PIN_LED_INVERTED);
    return true;
}

static int timeout()
{
    if (connectionState == running && blipLED)
    {
        blipLED = false;
        digitalWrite(GPIO_PIN_LED, HIGH ^ GPIO_PIN_LED_INVERTED);
        return DURATION_NEVER;
    }
    return updateLED();
}

static int event()
{
    if (connectionState == running && blipLED)
    {
        digitalWrite(GPIO_PIN_LED, LOW ^ GPIO_PIN_LED_INVERTED);
        return 50; // 50ms off
    }
    if (connectionState == binding)
    {
        return flashLED(LEDSEQ_BINDING, sizeof(LEDSEQ_BINDING));
    }
    if (connectionState == wifiUpdate)
    {
        return flashLED(LEDSEQ_WIFI_UPDATE, sizeof(LEDSEQ_WIFI_UPDATE));
    }
    return DURATION_NEVER;
}

void turnOffLED()
{
    digitalWrite(GPIO_PIN_LED, LOW ^ GPIO_PIN_LED_INVERTED);
}

void blinkLED()
{
  blipLED = true;
  devicesTriggerEvent(EVENT_LED_ACTIVATED);
}

device_t LED_device = {
    .initialize = initialize,
    .start = event,
    .event = event,
    .timeout = timeout,
    .subscribe = EVENT_LED_ACTIVATED
};
