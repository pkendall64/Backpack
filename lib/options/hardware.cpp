#if !defined(UNIT_TEST)
#if defined(PLATFORM_ESP8266)
#include <FS.h>
#else
#include <SPIFFS.h>
#endif
#include <ArduinoJson.h>
#include "hardware.h"
#include "options.h"

typedef enum {
    INT,
    BOOL,
} datatype_t;

static const struct {
    const nameType position;
    const char *name;
    const datatype_t type;
} fields[] = {
    {HARDWARE_button, "button", INT},
    {HARDWARE_led, "led", INT},
    {HARDWARE_led_invert, "led_invert", BOOL},

    {HARDWARE_spi_cs, "spi_cs", INT},
    {HARDWARE_spi_sck, "spi_sck", INT},
    {HARDWARE_spi_mosi, "spi_mosi", INT},

    {HARDWARE_i2c_scl, "i2c_scl", INT},
    {HARDWARE_i2c_sda, "i2c_sda", INT},
    {HARDWARE_i2c_int, "i2c_int", INT},

    {HARDWARE_servo_azim, "servo_azim", INT},
    {HARDWARE_servo_elev, "servo_elev", INT},
};

typedef union {
    int int_value;
    bool bool_value;
    float float_value;
    int16_t *array_value;
} data_holder_t;

static data_holder_t hardware[HARDWARE_LAST];
static String builtinHardwareConfig;

String& getHardware()
{
    File file = SPIFFS.open("/hardware.json", "r");
    if (!file || file.isDirectory())
    {
        if (file)
        {
            file.close();
        }
        // Try JSON at the end of the firmware
        return builtinHardwareConfig;
    }
    builtinHardwareConfig = file.readString();
    return builtinHardwareConfig;
}

static void hardware_ClearAllFields()
{
    for (auto field : fields) {
        switch (field.type) {
            case INT:
                hardware[field.position].int_value = -1;
                break;
            case BOOL:
                hardware[field.position].bool_value = false;
                break;
        }
    }
}

static void hardware_LoadFieldsFromDoc(JsonDocument &doc)
{
    for (auto field : fields) {
        if (doc[field.name].is<JsonVariant>()) {
            switch (field.type) {
                case INT:
                    hardware[field.position].int_value = doc[field.name];
                    break;
                case BOOL:
                    hardware[field.position].bool_value = doc[field.name];
                    break;
            }
        }
    }
}

bool hardware_init(EspFlashStream &strmFlash)
{
    hardware_ClearAllFields();
    builtinHardwareConfig.clear();

    Stream *strmSrc;
    JsonDocument doc;
    File file = SPIFFS.open("/hardware.json", "r");
    if (!file || file.isDirectory()) {
        constexpr size_t hardwareConfigOffset = ELRSOPTS_OPTIONS_SIZE;
        strmFlash.setPosition(hardwareConfigOffset);
        if (!options_HasStringInFlash(strmFlash))
        {
            return false;
        }

        strmSrc = &strmFlash;
    }
    else
    {
        strmSrc = &file;
    }

    DeserializationError error = deserializeJson(doc, *strmSrc);
    if (error)
    {
        return false;
    }
    serializeJson(doc, builtinHardwareConfig);

    hardware_LoadFieldsFromDoc(doc);

    return true;
}

int hardware_pin(nameType name)
{
    return hardware[name].int_value;
}

bool hardware_flag(nameType name)
{
    return hardware[name].bool_value;
}

int hardware_int(nameType name)
{
    return hardware[name].int_value;
}
#endif
