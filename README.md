# Default Internet-of-Plants Firmware

If credentials aren't available, opens captive portal to obtain the WiFi credentials and the internet-of-plants server credentials.

The Access Point created for the Captive Portal will have "iop" as SSID and a PSK generated during the first local compilation, stored in `include/generated/psk.hpp`.

After connecting to the WiFi and authenticating to the internet-of-plants server, it will constantly fetch for updates from it.

Used as starting point to configure devices with https://web.internet-of-plants.org.

The `board` field in `platformio.ini` should be updated according to the device you have in the appropriate environment.

## License

[GNU Affero General Public License version 3 or later (AGPL-3.0+)](https://github.com/internet-of-plants/default-firmware/blob/main/LICENSE.md)