typedef enum {
    // Basic controls
    HARDWARE_button,
    HARDWARE_led,
    HARDWARE_led_invert,

    // SPI
    HARDWARE_spi_cs,
    HARDWARE_spi_sck,
    HARDWARE_spi_mosi,

    // I2C for Gyro/OLED
    HARDWARE_i2c_scl,
    HARDWARE_i2c_sda,
    HARDWARE_i2c_int,

    // Servos for AAT
    HARDWARE_servo_azim,
    HARDWARE_servo_elev,

    HARDWARE_LAST
} nameType;

int hardware_pin(nameType name);
bool hardware_flag(nameType name);
int hardware_int(nameType name);
