# Backpack types

This groups the firmware by **backpack role/family**.

| Backpack type | Kind | Used for                                                                                                                                                                                                                                    | Repo hints |
| --- | --- |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------| --- |
| TX Backpack | TX-side backpack | Lives on the ExpressLRS transmitter side. Talks ESP-NOW to other backpacks, forwards VTX config and head-tracking packets to receiver-side backpacks, and can switch into WiFi/MAVLink telemetry mode.                                      | `README.md`, `src/Tx_main.cpp`, `targets/txbp_esp.ini` |
| Timer | Race timer backpack | Backpack target for a race timer module. This backpack connects to a RotorHazard timer and sends OSD messages to pilots goggles via their VRx backpack.                                                                                     | `html/timer_index.html`, `targets/timer.ini`, `src/Timer_main.cpp` |
| VRX Backpack (generic) | Video receiver backpack | Adds backpack networking to a video receiver so the TX can remotely push band/channel changes. Depending on the VRX family, it may also handle DVR recording, OSD packets, head-tracking control, RTC sync, and CRSF telemetry passthrough. | `README.md`, `src/Vrx_main.cpp` |
| RapidFire | VRX subtype | Controls ImmersionRC RapidFire receivers over the RapidFire SPI protocol. The repo also has head-tracking target variants for this family.                                                                                                  | `src/rapidfire.cpp`, `targets/rapidfire.ini` |
| RX5808 | VRX subtype | Tunes RX5808-based analog receivers. The repo also has diversity and head-tracking target variants for this family.                                                                                                                         | `src/rx5808.cpp`, `targets/rx5808.ini` |
| Skyzone SteadyView | VRX subtype | Tunes Skyzone SteadyView analog receivers and initializes SteadyView-specific receiver mode handling.                                                                                                                                       | `src/steadyview.cpp`, `targets/skyzone.ini` |
| TBS Fusion | VRX subtype | Controls built-in TBS Fusion receivers and forwards CRSF link/battery telemetry into Fusion's serial protocol.                                                                                                                              | `src/tbs_fusion.cpp`, `targets/fusion.ini` |
| HDZero | VRX subtype | Controls HDZero receivers/goggles over MSP: channel changes, DVR recording state, head-tracking enable, OSD packets, and RTC sync.                                                                                                          | `src/hdzero.cpp`, `targets/hdzero.ini` |
| Skyzone MSP / Onboard | VRX subtype | Controls Skyzone onboard/MSP-capable receiver hardware over MSP, including channel changes, DVR recording, OSD packets, and head-tracking enable.                                                                                           | `src/skyzone_msp.cpp`, `targets/skyzone.ini` |
| Orqa | VRX subtype | Controls Orqa VRX hardware by sending GHST-style frequency/channel updates. The repo also has head-tracking target variants for this family.                                                                                                | `src/orqa.cpp`, `targets/orqa.ini` |
| AAT | Tracker backpack | Automatic antenna tracker. Uses GPS telemetry to drive azimuth/elevation servos toward the model, with AAT-specific config and optional OLED status UI.                                                                                     | `targets/aat.ini`, `src/module_aat.cpp`, `src/devwifi_proxy_aat.cpp` |
| MFD Crossbow | Tracker backpack | Feeds GPS telemetry to an MFD Crossbow tracker using MAVLink heartbeat, GPS, and global-position messages.                                                                                                                                  | `targets/mfd_crossbow.ini`, `src/mfd_crossbow.cpp` |

# Target defines

| Define                 | Main code      |
|------------------------|----------------|
| TARGET_TX_BACKPACK     | Tx_main.cpp    |
| TARGET_TIMER_BACKPACK  | Timer_main.cpp |
| TARGET_VRX_BACKPACK    | VRx_main.cpp   |
| TARGET_AAT_BACKPACK    | VRx_main.cpp   |

VRx_main.cpp should be renamed to Periph_main.cpp?

## Things to look into

- -DNO_AUTOBIND (used by HDZero as it's built-in, should be a hardware flag)
