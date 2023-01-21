#if defined(HAS_TELNET)
#include "Telnet.h"
#include "logging.h"

static const telnet_telopt_t options[] = {
    { TELNET_TELOPT_ECHO,           TELNET_WILL, TELNET_DONT },
    { TELNET_TELOPT_SGA,            TELNET_WILL, TELNET_DONT },
    { TELNET_TELOPT_TTYPE,          TELNET_WILL, TELNET_DONT },
    { TELNET_TELOPT_TSPEED,         TELNET_WILL, TELNET_DONT },
    { TELNET_TELOPT_LINEMODE,       TELNET_WONT, TELNET_DONT },
    { TELNET_TELOPT_COMPRESS2,      TELNET_WONT, TELNET_DO   },
    { TELNET_TELOPT_ZMP,            TELNET_WONT, TELNET_DO   },
    { TELNET_TELOPT_MSSP,           TELNET_WONT, TELNET_DO   },
    { TELNET_TELOPT_BINARY,         TELNET_WILL, TELNET_DO   },
    { TELNET_TELOPT_NAWS,           TELNET_WILL, TELNET_DONT },
    { TELNET_TELOPT_NEW_ENVIRON,    TELNET_WILL, TELNET_DONT },
    { -1, 0, 0 }
};

static telnet_t *_telnet = nullptr;

static void handler(telnet_t *telnet, telnet_event_t *event, void *user_data)
{
	switch (event->type) {
	case TELNET_EV_DATA:
        Serial.write(event->data.buffer, event->data.size);
		break;
	case TELNET_EV_SEND:
        ((Telnet*)user_data)->write((uint8_t *)event->data.buffer, event->data.size);
		break;
    default:
		break;
    }
}

static void connectHandler(String str)
{
    telnet_negotiate(_telnet, TELNET_WILL, TELNET_TELOPT_ECHO);
    telnet_negotiate(_telnet, TELNET_WILL, TELNET_TELOPT_SGA);
    telnet_negotiate(_telnet, TELNET_WONT, TELNET_TELOPT_LINEMODE);
    telnet_negotiate(_telnet, TELNET_DO, TELNET_TELOPT_NAWS);
}

static void inputHandler(String str)
{
    telnet_recv(_telnet, str.c_str(), str.length());
}

bool Telnet::hasClient()
{
    return client && isClientConnected(client);
}

void Telnet::handle()
{
    if (!telnetStarted) {
        telnetStarted = ESPTelnetStream::begin(port);
        if (telnetStarted)
        {
            DBGLN("Telnet started");
            _telnet = telnet_init(options, handler, 0, this);
            ESPTelnetStream::onConnect(connectHandler);
            ESPTelnetStream::onInputReceived(inputHandler);
        }
        return;
    }

    ESPTelnetStream::loop();

    int available = Serial.available();
    if (available > 0) {
        uint8_t buf[available];
        Serial.read(buf, available);
        if (_telnet)
        {
            telnet_send(_telnet, (char *)buf, available);
        }
    }
}

size_t Telnet::write(uint8_t *data, size_t size) {
  if (client && isClientConnected(client)) {
    return client.write(data, size);
  } else {
    return 0;
  }
}
#endif
