#include "controller.hpp"

#include <catch.hpp>
#include <utility>
#include <vector>

#include "cen.hpp"
#include "event.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("controller_type enum values", "[controller]")
{
  SECTION("operator==")
  {
    CHECK(cen::controller_type::unknown == SDL_CONTROLLER_TYPE_UNKNOWN);
    CHECK(cen::controller_type::xbox_360 == SDL_CONTROLLER_TYPE_XBOX360);
    CHECK(cen::controller_type::xbox_one == SDL_CONTROLLER_TYPE_XBOXONE);
    CHECK(cen::controller_type::ps3 == SDL_CONTROLLER_TYPE_PS3);
    CHECK(cen::controller_type::ps4 == SDL_CONTROLLER_TYPE_PS4);
    CHECK(cen::controller_type::nintendo_switch_pro ==
          SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);

    CHECK(SDL_CONTROLLER_TYPE_UNKNOWN == cen::controller_type::unknown);
    CHECK(SDL_CONTROLLER_TYPE_XBOX360 == cen::controller_type::xbox_360);
    CHECK(SDL_CONTROLLER_TYPE_XBOXONE == cen::controller_type::xbox_one);
    CHECK(SDL_CONTROLLER_TYPE_PS3 == cen::controller_type::ps3);
    CHECK(SDL_CONTROLLER_TYPE_PS4 == cen::controller_type::ps4);
    CHECK(SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO ==
          cen::controller_type::nintendo_switch_pro);
  }

  SECTION("operator!=")
  {
    CHECK(cen::controller_type::ps4 != SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);
    CHECK(SDL_CONTROLLER_TYPE_XBOX360 != cen::controller_type::unknown);
  }
}

TEST_CASE("controller_axis enum values", "[controller]")
{
  SECTION("operator==")
  {
    CHECK(cen::controller_axis::invalid == SDL_CONTROLLER_AXIS_INVALID);
    CHECK(cen::controller_axis::left_x == SDL_CONTROLLER_AXIS_LEFTX);
    CHECK(cen::controller_axis::left_y == SDL_CONTROLLER_AXIS_LEFTY);
    CHECK(cen::controller_axis::right_x == SDL_CONTROLLER_AXIS_RIGHTX);
    CHECK(cen::controller_axis::right_y == SDL_CONTROLLER_AXIS_RIGHTY);
    CHECK(cen::controller_axis::trigger_left ==
          SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    CHECK(cen::controller_axis::trigger_right ==
          SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    CHECK(cen::controller_axis::max == SDL_CONTROLLER_AXIS_MAX);

    CHECK(SDL_CONTROLLER_AXIS_INVALID == cen::controller_axis::invalid);
    CHECK(SDL_CONTROLLER_AXIS_LEFTX == cen::controller_axis::left_x);
    CHECK(SDL_CONTROLLER_AXIS_LEFTY == cen::controller_axis::left_y);
    CHECK(SDL_CONTROLLER_AXIS_RIGHTX == cen::controller_axis::right_x);
    CHECK(SDL_CONTROLLER_AXIS_RIGHTY == cen::controller_axis::right_y);
    CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT ==
          cen::controller_axis::trigger_left);
    CHECK(SDL_CONTROLLER_AXIS_TRIGGERRIGHT ==
          cen::controller_axis::trigger_right);
    CHECK(SDL_CONTROLLER_AXIS_MAX == cen::controller_axis::max);
  }

  SECTION("operator!=")
  {
    CHECK(cen::controller_axis::left_x != SDL_CONTROLLER_AXIS_MAX);
    CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT != cen::controller_axis::right_x);
  }
}

TEST_CASE("controller_button enum values", "[controller]")
{
  SECTION("operator==")
  {
    CHECK(cen::controller_button::invalid == SDL_CONTROLLER_BUTTON_INVALID);
    CHECK(cen::controller_button::a == SDL_CONTROLLER_BUTTON_A);
    CHECK(cen::controller_button::b == SDL_CONTROLLER_BUTTON_B);
    CHECK(cen::controller_button::x == SDL_CONTROLLER_BUTTON_X);
    CHECK(cen::controller_button::y == SDL_CONTROLLER_BUTTON_Y);
    CHECK(cen::controller_button::back == SDL_CONTROLLER_BUTTON_BACK);
    CHECK(cen::controller_button::guide == SDL_CONTROLLER_BUTTON_GUIDE);
    CHECK(cen::controller_button::start == SDL_CONTROLLER_BUTTON_START);
    CHECK(cen::controller_button::left_stick ==
          SDL_CONTROLLER_BUTTON_LEFTSTICK);
    CHECK(cen::controller_button::right_stick ==
          SDL_CONTROLLER_BUTTON_RIGHTSTICK);
    CHECK(cen::controller_button::left_shoulder ==
          SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    CHECK(cen::controller_button::right_shoulder ==
          SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
    CHECK(cen::controller_button::dpad_up == SDL_CONTROLLER_BUTTON_DPAD_UP);
    CHECK(cen::controller_button::dpad_down == SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    CHECK(cen::controller_button::dpad_right ==
          SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    CHECK(cen::controller_button::dpad_left == SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    CHECK(cen::controller_button::max == SDL_CONTROLLER_BUTTON_MAX);
  }

  SECTION("operator!=")
  {
    CHECK(cen::controller_button::right_stick != SDL_CONTROLLER_BUTTON_DPAD_UP);
    CHECK(SDL_CONTROLLER_BUTTON_B != cen::controller_button::guide);
  }
}

TEST_CASE("controller_bind_type enum values", "[controller]")
{
  SECTION("operator==")
  {
    CHECK(cen::controller_bind_type::axis == SDL_CONTROLLER_BINDTYPE_AXIS);
    CHECK(cen::controller_bind_type::button == SDL_CONTROLLER_BINDTYPE_BUTTON);
    CHECK(cen::controller_bind_type::none == SDL_CONTROLLER_BINDTYPE_NONE);
    CHECK(cen::controller_bind_type::hat == SDL_CONTROLLER_BINDTYPE_HAT);

    CHECK(SDL_CONTROLLER_BINDTYPE_AXIS == cen::controller_bind_type::axis);
    CHECK(SDL_CONTROLLER_BINDTYPE_BUTTON == cen::controller_bind_type::button);
    CHECK(SDL_CONTROLLER_BINDTYPE_NONE == cen::controller_bind_type::none);
    CHECK(SDL_CONTROLLER_BINDTYPE_HAT == cen::controller_bind_type::hat);
  }

  SECTION("operator!=")
  {
    CHECK(cen::controller_bind_type::axis != SDL_CONTROLLER_BINDTYPE_HAT);
    CHECK(SDL_CONTROLLER_BINDTYPE_BUTTON != cen::controller_bind_type::none);
  }
}

TEST_CASE("controller load_mappings", "[controller]")
{
  CHECK(cen::controller::load_mappings("resources/gamecontrollerdb.txt") > 0);
}

namespace centurion {

class controller_handler  // TODO worth adding?
{
 public:
  void add_all()
  {
    const auto amount = cen::joystick::amount().value_or(0);
    for (int i = 0; i < amount; ++i) {
      if (cen::controller::is_supported(i)) {
        emplace(i);
      }
    }
  }

  template <typename... Args>
  void emplace(Args&&... args)
  {
    m_controllers.emplace_back(std::forward<Args>(args)...);
  }

  void remove(int index)
  {
    auto erase = [](auto& container, auto&& predicate) {
      container.erase(
          std::remove_if(begin(container), end(container), predicate),
          end(container));
    };

    erase(m_controllers, [=](const cen::controller& c) {
      const auto i = c.index();
      return i && index == *i;
    });
  }

  auto at(int index) -> controller&
  {
    const auto it = find(index);
    if (it != end(m_controllers)) {
      return *it;
    } else {
      throw centurion_exception{"Failed to find controller!"};
    }
  }

 private:
  std::vector<controller> m_controllers;

  [[nodiscard]] auto find(int index) -> std::vector<controller>::iterator
  {
    const auto it = std::find_if(begin(m_controllers),
                                 end(m_controllers),
                                 [=](const cen::controller& c) noexcept {
                                   const auto i = c.index();
                                   return i && index == *i;
                                 });
    return it;
  }
};

}  // namespace centurion

// TODO game controller visualization program

TEST_CASE("interactive controller", "[.controller]")
{
  cen::window window;
  cen::renderer renderer{window};
  cen::event event;
  cen::controller_handler controllers;
  controllers.add_all();

  //  bool running{true};
  //
  //  int colorIndex{};
  //  constexpr std::array<ctn::color, 5> colors{ctn::colors::red,
  //                                             ctn::colors::salmon,
  //                                             ctn::colors::cyan,
  //                                             ctn::colors::dark_sea_green,
  //                                             ctn::colors::orchid};
  //
  //  auto handleDeviceEvent = [&](const ctn::controller_device_event& event) {
  //    if (event.type() == ctn::event_type::controller_device_removed) {
  //      const auto id = event.which();
  //      controllers.remove(id);
  //    } else if (event.type() == ctn::event_type::controller_device_added) {
  //      controllers.emplace(event.which());
  //    }
  //  };
  //
  //  auto handleButtonEvent = [&](const ctn::controller_button_event& event) {
  //    if (event.state() == ctn::button_state::released) {
  //      ++colorIndex;
  //    }
  //  };
  //
  //  window.show();
  //  while (running) {
  //    while (event.poll()) {
  //      if (event.is<ctn::quit_event>()) {
  //        running = false;
  //        break;
  //      } else if (auto* de = event.try_get<ctn::controller_device_event>()) {
  //        handleDeviceEvent(*de);
  //      } else if (auto* be = event.try_get<ctn::controller_button_event>()) {
  //        handleButtonEvent(*be);
  //      }
  //    }
  //
  //    renderer.clear_with(colors.at(colorIndex % colors.size()));
  //
  //    renderer.set_color(ctn::colors::wheat);
  //    renderer.fill_rect<int>({{10, 10}, {100, 100}});
  //
  //    renderer.present();
  //  }
  //  window.hide();
}

// TEST_CASE("load_game_controller_mappings", "[controller]")
//{
//  const auto nAdded =
//      ctn::controller::load_mappings("resources/gamecontrollerdb.txt");
//  CHECK(nAdded > 0);
//}
//
//#include <array>
//

//
// TEST_CASE("Interactive game controller test", "[..controller]")
//{
//  ctn::window window{"Game controller demo"};
//  ctn::renderer renderer{window};
//  ctn::event event;
//
//  ctn::controller::load_mappings("resources/gamecontrollerdb.txt");
//
//  ctn::controller controller{0};
//
//  ctn::frect rect{{0, 0}, {100, 100}};
//
//  float dx{};
//  float dy{};
//
//  constexpr auto deadZone = 8000;
//
//  constexpr std::array<ctn::color, 3> colors{
//      ctn::colors::pink, ctn::colors::steel_blue, ctn::colors::red};
//  int colorIndex{};
//  ctn::color color = colors.at(colorIndex);
//
//  bool running = true;
//  window.show();
//  while (running) {
//    while (event.poll()) {
//      if (event.is<ctn::quit_event>()) {
//        running = false;
//        break;
//      } else if (const auto* cbe =
//                     event.try_get<ctn::controller_button_event>()) {
//        if (cbe->state() == ctn::button_state::released) {
//          ++colorIndex;
//          color = colors.at(colorIndex % int{colors.size()});
//        }
//      } else if (const auto* cae =
//                     event.try_get<ctn::controller_axis_event>()) {
//        const auto axis = cae->axis();
//        const auto value = cae->value();  // -32768 to 32767)
//        const auto fvalue = static_cast<float>(value);
//
//        const auto step = 0.0005f;
//
//        if (axis == ctn::controller_axis::left_x) {
//          if ((value < -deadZone) || (value > deadZone)) {
//            dx = fvalue * step;
//          } else {
//            dx = 0;
//          }
//        } else if (axis == ctn::controller_axis::left_y) {
//          if ((value < -deadZone) || (value > deadZone)) {
//            dy = fvalue * step;
//          } else {
//            dy = 0;
//          }
//        }
//      }
//    }
//
//    rect.set_x(rect.x() + dx);
//    rect.set_y(rect.y() + dy);
//
//    renderer.clear_with(color);
//
//    renderer.set_color(ctn::colors::dark_red);
//    renderer.fill_rect(rect);
//
//    renderer.present();
//  }
//  window.hide();
//}