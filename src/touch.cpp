#include "touch.hpp"

namespace centurion::touch {

auto num_devices() noexcept -> int
{
  return SDL_GetNumTouchDevices();
}

auto get_device(int index) noexcept -> std::optional<SDL_TouchID>
{
  const auto device = SDL_GetTouchDevice(index);
  if (device == 0) {
    return nothing;
  } else {
    return device;
  }
}

auto type_of(SDL_TouchID id) noexcept -> device_type
{
  return static_cast<device_type>(SDL_GetTouchDeviceType(id));
}

auto num_fingers(SDL_TouchID id) noexcept -> int
{
  return SDL_GetNumTouchFingers(id);
}

auto get_finger(SDL_TouchID id, int index) noexcept -> std::optional<SDL_Finger>
{
  const auto* finger = SDL_GetTouchFinger(id, index);
  if (finger) {
    return *finger;
  } else {
    return nothing;
  }
}

}  // namespace centurion::touch
