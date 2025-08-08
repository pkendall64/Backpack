#pragma once

#if defined(TARGET_VRX_BACKPACK)

#include <cstdint>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

void WebAatAppendConfig(ArduinoJson::JsonDocument &json);
void WebAatInit(AsyncWebServer &server);

#endif /* defined(TARGET_VRX_BACKPACK) */
