#include <SDL.h>

#include <catch.hpp>

#include "cen.hpp"
#include "event.hpp"

namespace {

auto get_events_one_mod_active(cen::key_modifier leftMod,
                               cen::key_modifier rightMod) noexcept
    -> std::pair<cen::keyboard_event, cen::keyboard_event>
{
  const auto createEvent = [](cen::key_modifier modifier) noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.keysym.mod = static_cast<int>(modifier);
    return cen::keyboard_event{sdlEvent};
  };

  const auto left = createEvent(leftMod);
  const auto right = createEvent(rightMod);
  return {left, right};
}

auto get_event_mod_flags(int modifierFlags) noexcept -> cen::keyboard_event
{
  SDL_KeyboardEvent sdlEvent{};
  sdlEvent.keysym.mod = modifierFlags;
  return cen::keyboard_event{sdlEvent};
}

}  // namespace

TEST_CASE("keyboard_event::set_scan_code", "[keyboard_event]")
{
  cen::keyboard_event event;

  event.set_scan_code(SDL_SCANCODE_B);

  CHECK(event.get_scan_code() == SDL_SCANCODE_B);
}

TEST_CASE("keyboard_event::set_key_code", "[keyboard_event]")
{
  cen::keyboard_event event;

  event.set_key_code(SDLK_n);

  CHECK(event.get_key_code() == SDLK_n);
}

TEST_CASE("keyboard_event::set_modifier", "[keyboard_event]")
{
  cen::keyboard_event event;

  const auto shift = cen::key_modifier::left_shift;
  const auto caps = cen::key_modifier::caps;

  event.set_modifier(shift, true);
  CHECK(event.modifier_active(shift));

  event.set_modifier(caps, true);

  CHECK(event.modifier_active(shift));
  CHECK(event.modifier_active(caps));

  event.set_modifier(shift, false);
  CHECK(!event.modifier_active(shift));
  CHECK(event.modifier_active(caps));
}

TEST_CASE("keyboard_event::set_repeated", "[keyboard_event]")
{
  cen::keyboard_event event;

  event.set_repeated(true);
  CHECK(event.repeated());

  event.set_repeated(false);
  CHECK(!event.repeated());
}

TEST_CASE("keyboard_event::set_window_id", "[keyboard_event]")
{
  cen::keyboard_event event;

  const auto id = 79U;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("keyboard_event::is_active", "[keyboard_event]")
{
  const auto createEvent = [](SDL_Scancode scancode,
                              SDL_KeyCode keyCode) noexcept {
    SDL_KeyboardEvent keyboardEvent{};
    keyboardEvent.keysym.scancode = scancode;
    keyboardEvent.keysym.sym = keyCode;
    return keyboardEvent;
  };

  const cen::keyboard_event event{createEvent(SDL_SCANCODE_Q, SDLK_q)};

  CHECK(event.is_active(SDLK_q));
  CHECK(event.is_active(SDL_SCANCODE_Q));

  CHECK(!event.is_active(SDLK_e));
  CHECK(!event.is_active(SDL_SCANCODE_E));
}

TEST_CASE("keyboard_event::modifier_active", "[keyboard_event]")
{
  const auto createEvent = []() noexcept {
    SDL_KeyboardEvent event{};
    SDL_Keysym keysym{};
    keysym.mod = KMOD_LALT | KMOD_CAPS;
    event.keysym = keysym;
    return event;
  };

  const cen::keyboard_event event{createEvent()};

  SECTION("Check that multiple key modifiers can be active at the same time")
  {
    CHECK(event.modifier_active(cen::key_modifier::left_alt));
    CHECK(event.modifier_active(cen::key_modifier::caps));
  }
}

TEST_CASE("keyboard_event::shift_active", "[keyboard_event]")
{
  SECTION("No modifiers")
  {
    const cen::keyboard_event event{{}};
    CHECK(!event.shift_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] = get_events_one_mod_active(
        cen::key_modifier::left_shift, cen::key_modifier::right_shift);
    CHECK(left.shift_active());
    CHECK(right.shift_active());
  }

  SECTION("Both modifiers active")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_LSHIFT | KMOD_RSHIFT);
    CHECK(event.shift_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_LSHIFT | KMOD_RSHIFT | KMOD_CAPS | KMOD_LGUI);
    CHECK(event.shift_active());
  }
}

TEST_CASE("keyboard_event::ctrl_active", "[keyboard_event]")
{
  SECTION("No modifiers")
  {
    const cen::keyboard_event event{{}};
    CHECK(!event.ctrl_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] = get_events_one_mod_active(
        cen::key_modifier::left_ctrl, cen::key_modifier::right_ctrl);
    CHECK(left.ctrl_active());
    CHECK(right.ctrl_active());
  }

  SECTION("Both modifiers active")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_LCTRL | KMOD_RCTRL);
    CHECK(event.ctrl_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_LCTRL | KMOD_RCTRL | KMOD_CAPS | KMOD_LSHIFT);
    CHECK(event.ctrl_active());
  }
}

TEST_CASE("keyboard_event::alt_active", "[keyboard_event]")
{
  SECTION("No modifiers")
  {
    const cen::keyboard_event event{{}};
    CHECK(!event.alt_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] = get_events_one_mod_active(
        cen::key_modifier::left_alt, cen::key_modifier::right_alt);
    CHECK(left.alt_active());
    CHECK(right.alt_active());
  }

  SECTION("Both modifiers active")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_LALT | KMOD_RALT);
    CHECK(event.alt_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_LALT | KMOD_RALT | KMOD_RCTRL | KMOD_RGUI);
    CHECK(event.alt_active());
  }
}

TEST_CASE("keyboard_event::gui_active", "[keyboard_event]")
{
  SECTION("No modifiers")
  {
    const cen::keyboard_event event{{}};
    CHECK(!event.gui_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] = get_events_one_mod_active(
        cen::key_modifier::left_gui, cen::key_modifier::right_gui);
    CHECK(left.gui_active());
    CHECK(right.gui_active());
  }

  SECTION("Both modifiers active")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_LGUI | KMOD_RGUI);
    CHECK(event.gui_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_LGUI | KMOD_RGUI | KMOD_RCTRL | KMOD_RSHIFT);
    CHECK(event.gui_active());
  }
}

TEST_CASE("keyboard_event::caps_active", "[keyboard_event]")
{
  SECTION("No modifiers")
  {
    const cen::keyboard_event event{{}};
    CHECK(!event.caps_active());
  }

  SECTION("Active")
  {
    cen::keyboard_event event;
    event.set_modifier(cen::key_modifier::caps, true);
    CHECK(event.caps_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_RCTRL | KMOD_RSHIFT | KMOD_CAPS);
    CHECK(event.caps_active());
  }
}

TEST_CASE("keyboard_event::num_active", "[keyboard_event]")
{
  SECTION("No modifiers")
  {
    const cen::keyboard_event event{{}};
    CHECK(!event.num_active());
  }

  SECTION("Active")
  {
    cen::keyboard_event event;
    event.set_modifier(cen::key_modifier::num, true);
    CHECK(event.num_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const cen::keyboard_event event =
        get_event_mod_flags(KMOD_RGUI | KMOD_RSHIFT | KMOD_NUM);
    CHECK(event.num_active());
  }
}

TEST_CASE("keyboard_event::repeated", "[keyboard_event]")
{
  const auto createEvent = [](int repeats) noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.repeat = repeats;
    return cen::keyboard_event{sdlEvent};
  };

  const auto noRepeat = createEvent(0);
  const auto oneRepeat = createEvent(1);
  const auto twoRepeats = createEvent(2);

  CHECK(!noRepeat.repeated());
  CHECK(oneRepeat.repeated());
  CHECK(twoRepeats.repeated());
}

TEST_CASE("keyboard_event::state", "[keyboard_event]")
{
  SECTION("Check valid state")
  {
    const auto createEvent = []() noexcept {
      SDL_KeyboardEvent event{};

      event.keysym.sym = SDLK_ESCAPE;
      event.state = SDL_PRESSED;

      return cen::keyboard_event{event};
    };

    const auto event = createEvent();
    CHECK(event.state() == cen::button_state::pressed);
  }

  SECTION("Default button state")
  {
    const cen::keyboard_event event{{}};
    CHECK(event.state() == cen::button_state::released);
  }
}

TEST_CASE("keyboard_event::released", "[keyboard_event]")
{
  SECTION("Check released")
  {
    const auto createEvent = []() noexcept {
      SDL_KeyboardEvent event{};

      event.keysym.sym = SDLK_g;
      event.keysym.scancode = SDL_SCANCODE_G;
      event.state = SDL_RELEASED;

      return cen::keyboard_event{event};
    };

    const auto event = createEvent();
    CHECK(event.released());
    CHECK(event.state() == cen::button_state::released);
  }

  SECTION("Not released")
  {
    const auto createEvent = []() noexcept {
      SDL_KeyboardEvent event{};

      event.state = SDL_PRESSED;

      return cen::keyboard_event{event};
    };

    const auto event = createEvent();
    CHECK(!event.released());
    CHECK(event.pressed());
  }
}

TEST_CASE("keyboard_event::pressed", "[keyboard_event]")
{
  SECTION("Check pressed")
  {
    const auto createEvent = []() noexcept {
      SDL_KeyboardEvent event{};

      event.keysym.sym = SDLK_o;
      event.keysym.scancode = SDL_SCANCODE_O;
      event.state = SDL_PRESSED;

      return cen::keyboard_event{event};
    };

    const auto event = createEvent();
    CHECK(event.pressed());
    CHECK(event.state() == cen::button_state::pressed);
  }

  SECTION("Not pressed")
  {
    const auto createEvent = []() noexcept {
      SDL_KeyboardEvent event{};

      event.state = SDL_RELEASED;

      return cen::keyboard_event{event};
    };

    const auto event = createEvent();
    CHECK(!event.pressed());
    CHECK(event.released());
  }
}

TEST_CASE("keyboard_event::get_scan_code", "[keyboard_event]")
{
  cen::keyboard_event event;
  const cen::scan_code original{SDL_SCANCODE_Q};

  event.set_scan_code(original);
  const auto code = event.get_scan_code();

  CHECK(original == code);
}

TEST_CASE("keyboard_event::get_key_code", "[keyboard_event]")
{
  cen::keyboard_event event;
  const cen::key_code original{SDLK_x};

  event.set_key_code(original);
  const auto code = event.get_key_code();

  CHECK(original == code);
}

TEST_CASE("keyboard_event::window_id", "[keyboard_event]")
{
  const auto windowID = 72;
  const auto createEvent = [windowID]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.windowID = windowID;
    return cen::keyboard_event{sdlEvent};
  };

  const auto event = createEvent();
  CHECK(event.window_id() == windowID);
}