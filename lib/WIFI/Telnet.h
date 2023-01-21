#include "ESPTelnetStream.h"
#include "libtelnet.h"

class Telnet : public ESPTelnetStream {
public:
    Telnet(uint16_t telnetPort) : port(telnetPort) {};
    bool hasClient();
    void handle();
    size_t write(uint8_t *data, size_t size);

private:
    uint16_t port;
    bool telnetStarted = false;
};