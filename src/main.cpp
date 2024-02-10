#include <iop/loop.hpp>

#include "generated/psk.hpp"

namespace config {
constexpr static iop::time::milliseconds interval = 30 * 1000;
constexpr static int8_t timezone = -3;
constexpr static char SSID_RAW[] IOP_ROM = "iop";
static const iop::StaticString SSID = reinterpret_cast<const __FlashStringHelper*>(SSID_RAW);
static const iop::StaticString PSK = reinterpret_cast<const __FlashStringHelper*>(generated::PSK);
}

// Sends empty json object to internet-of-plants server, updating the firmware if possible
auto prepareJson(iop::EventLoop & loop) noexcept -> iop::Api::Json {
  IOP_TRACE();

  auto json = loop.api().makeJson(IOP_FUNC, [](JsonDocument &doc) { (void) doc; });
  iop_assert(json, IOP_STR("Unable to generate request payload, OOM or buffer overflow"));
  return json;
}

auto contactServer(iop::EventLoop &loop, const iop::AuthToken &token) noexcept -> void {
  loop.registerEvent(token, prepareJson(loop));
}

namespace iop {
auto setup(EventLoop &loop) noexcept -> void {
  loop.setAccessPointCredentials(config::SSID, config::PSK);
  loop.setTimezone(config::timezone);
  loop.setAuthenticatedInterval(config::interval, contactServer);
}
}
