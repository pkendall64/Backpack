#include <Arduino.h>

#include "common.h"
#include "device.h"
#include "config.h"
#include "logging.h"

#include "button.h"
#include "hardware.h"

static Button button;

extern unsigned long rebootTime;
void RebootIntoWifi(wifi_service_t service);

static void shortPress()
{
    if (connectionState == wifiUpdate)
    {
        rebootTime = millis();
    }
    else
    {
        RebootIntoWifi(WIFI_SERVICE_UPDATE);
    }
}

static bool initialize()
{
    if (GPIO_PIN_BUTTON == UNDEF_PIN)
    {
        return false;
    }
    button.init(GPIO_PIN_BUTTON, false);
    button.OnShortPress = shortPress;
    return true;
}

static int start()
{
    return DURATION_IMMEDIATELY;
}

static int timeout()
{
    return button.update();
}

device_t Button_device = {
    .initialize = initialize,
    .start = start,
    .event = nullptr,
    .timeout = timeout
};
