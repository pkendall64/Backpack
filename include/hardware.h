typedef enum {
    HARDWARE_device_type,

    // Basic controls
    HARDWARE_button,
    HARDWARE_led,
    HARDWARE_led_invert,

    // SPI
    HARDWARE_spi_cs,
    HARDWARE_spi_clk,
    HARDWARE_spi_mosi,
    HARDWARE_spi_cs2,

    // I2C for Gyro/OLED
    HARDWARE_i2c_scl,
    HARDWARE_i2c_sda,
    HARDWARE_i2c_int,

    // Servos for AAT
    HARDWARE_servo_azim,
    HARDWARE_servo_elev,

    HARDWARE_LAST
} nameType;

enum device_type_e
{
    DEVICE_NONE,
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

int hardware_pin(nameType name);
bool hardware_flag(nameType name);
int hardware_int(nameType name);

#define UNDEF_PIN (-1)

#define DEVICE_TYPE ((device_type_e)hardware_int(HARDWARE_device_type))
#define DEVICE_TYPE_IS(type) (DEVICE_TYPE == type)
#define HAS_HEAD_TRACKER (hardware_pin(HARDWARE_i2c_int) != UNDEF_PIN)

#define GPIO_PIN_BUTTON hardware_pin(HARDWARE_button)
#define GPIO_PIN_LED hardware_pin(HARDWARE_led)
#define GPIO_PIN_LED_INVERTED hardware_flag(HARDWARE_led_invert)

#define GPIO_PIN_CS hardware_pin(HARDWARE_spi_cs)
#define GPIO_PIN_CLK hardware_pin(HARDWARE_spi_clk)
#define GPIO_PIN_MOSI hardware_pin(HARDWARE_spi_mosi)
#define GPIO_PIN_CS_2 hardware_pin(HARDWARE_spi_cs2)

#define GPIO_PIN_I2C_SCL hardware_pin(HARDWARE_i2c_scl)
#define GPIO_PIN_I2C_SDA hardware_pin(HARDWARE_i2c_sda)
#define GPIO_PIN_I2C_INT hardware_pin(HARDWARE_i2c_int)

#define GPIO_PIN_SERVO_AZIM hardware_pin(HARDWARE_servo_azim)
#define GPIO_PIN_SERVO_ELEV hardware_pin(HARDWARE_servo_elev)
