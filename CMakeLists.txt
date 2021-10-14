cmake_minimum_required(VERSION 3.15)

project(centurion
    VERSION 6.4.0
    HOMEPAGE_URL "https://github.com/albin-johansson/centurion"
    LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if ("${CMAKE_CXX_STANDARD}" STREQUAL "")
  message("No explicit C++ version specified, assuming C++17...")
  set(CMAKE_CXX_STANDARD 17)
else ()
  message("Using C++${CMAKE_CXX_STANDARD}...")
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

include(Dependencies)
include(Utilities)

set(CEN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CEN_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resources)
set(CEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/centurion)
set(CEN_BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CENTURION_VERSION ${CMAKE_PROJECT_VERSION})

message("Centurion version: ${CENTURION_VERSION}")

set(CENTURION_LIB_TARGET libcenturion)
set(CENTURION_TEST_TARGET testcenturion)
set(CENTURION_MOCK_TARGET mockcenturion)

option(CEN_COVERAGE "Enable coverage data" OFF)
option(CEN_TESTS "Build the Centurion tests" ON)
option(CEN_EXAMPLES "Build the examples" ON)
option(CEN_INSTALL OFF)
option(CENTURION_MOCK_FRIENDLY_MODE "Enable more mocked tests" ON)

if (WIN32)
  find_env_var(SDL2DIR SDL2)
  find_env_var(SDL2IMAGEDIR SDL2_image)
  find_env_var(SDL2MIXERDIR SDL2_mixer)
  find_env_var(SDL2TTFDIR SDL2_ttf)
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

if (CEN_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

add_library(${CENTURION_LIB_TARGET} INTERFACE)

set(CEN_HEADER_PREFIX $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/centurion)
target_sources(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
    ${CEN_HEADER_PREFIX}/audio/channels.hpp>
    ${CEN_HEADER_PREFIX}/audio/fade_status.hpp>
    ${CEN_HEADER_PREFIX}/audio/music.hpp>
    ${CEN_HEADER_PREFIX}/audio/music_type.hpp>
    ${CEN_HEADER_PREFIX}/audio/sound_effect.hpp>
    ${CEN_HEADER_PREFIX}/audio/sound_fonts.hpp>

    ${CEN_HEADER_PREFIX}/compiler/compiler.hpp>
    ${CEN_HEADER_PREFIX}/compiler/features.hpp>

    ${CEN_HEADER_PREFIX}/core/cast.hpp>
    ${CEN_HEADER_PREFIX}/core/exception.hpp>
    ${CEN_HEADER_PREFIX}/core/integers.hpp>
    ${CEN_HEADER_PREFIX}/core/is_stateless_callable.hpp>
    ${CEN_HEADER_PREFIX}/core/library.hpp>
    ${CEN_HEADER_PREFIX}/core/log.hpp>
    ${CEN_HEADER_PREFIX}/core/log_category.hpp>
    ${CEN_HEADER_PREFIX}/core/log_macros.hpp>
    ${CEN_HEADER_PREFIX}/core/log_priority.hpp>
    ${CEN_HEADER_PREFIX}/core/macros.hpp>
    ${CEN_HEADER_PREFIX}/core/not_null.hpp>
    ${CEN_HEADER_PREFIX}/core/owner.hpp>
    ${CEN_HEADER_PREFIX}/core/result.hpp>
    ${CEN_HEADER_PREFIX}/core/sdl_log_category_workaround.hpp>
    ${CEN_HEADER_PREFIX}/core/sdl_string.hpp>
    ${CEN_HEADER_PREFIX}/core/sfinae.hpp>
    ${CEN_HEADER_PREFIX}/core/str.hpp>
    ${CEN_HEADER_PREFIX}/core/str_or_na.hpp>
    ${CEN_HEADER_PREFIX}/core/time.hpp>
    ${CEN_HEADER_PREFIX}/core/to_underlying.hpp>
    ${CEN_HEADER_PREFIX}/core/version.hpp>

    ${CEN_HEADER_PREFIX}/detail/address_of.hpp>
    ${CEN_HEADER_PREFIX}/detail/any_eq.hpp>
    ${CEN_HEADER_PREFIX}/detail/array_utils.hpp>
    ${CEN_HEADER_PREFIX}/detail/clamp.hpp>
    ${CEN_HEADER_PREFIX}/detail/convert_bool.hpp>
    ${CEN_HEADER_PREFIX}/detail/czstring_compare.hpp>
    ${CEN_HEADER_PREFIX}/detail/czstring_eq.hpp>
    ${CEN_HEADER_PREFIX}/detail/from_string.hpp>
    ${CEN_HEADER_PREFIX}/detail/hints_impl.hpp>
    ${CEN_HEADER_PREFIX}/detail/lerp.hpp>
    ${CEN_HEADER_PREFIX}/detail/max.hpp>
    ${CEN_HEADER_PREFIX}/detail/min.hpp>
    ${CEN_HEADER_PREFIX}/detail/owner_handle_api.hpp>
    ${CEN_HEADER_PREFIX}/detail/sdl_deleter.hpp>
    ${CEN_HEADER_PREFIX}/detail/sdl_version_at_least.hpp>
    ${CEN_HEADER_PREFIX}/detail/stack_resource.hpp>
    ${CEN_HEADER_PREFIX}/detail/static_bimap.hpp>
    ${CEN_HEADER_PREFIX}/detail/tuple_type_index.hpp>

    ${CEN_HEADER_PREFIX}/events/audio_device_event.hpp>
    ${CEN_HEADER_PREFIX}/events/common_event.hpp>
    ${CEN_HEADER_PREFIX}/events/controller_axis_event.hpp>
    ${CEN_HEADER_PREFIX}/events/controller_button_event.hpp>
    ${CEN_HEADER_PREFIX}/events/controller_device_event.hpp>
    ${CEN_HEADER_PREFIX}/events/controller_sensor_event.hpp>
    ${CEN_HEADER_PREFIX}/events/controller_touchpad_event.hpp>
    ${CEN_HEADER_PREFIX}/events/display_event.hpp>
    ${CEN_HEADER_PREFIX}/events/display_event_id.hpp>
    ${CEN_HEADER_PREFIX}/events/dollar_gesture_event.hpp>
    ${CEN_HEADER_PREFIX}/events/drop_event.hpp>
    ${CEN_HEADER_PREFIX}/events/event.hpp>
    ${CEN_HEADER_PREFIX}/events/event_dispatcher.hpp>
    ${CEN_HEADER_PREFIX}/events/event_type.hpp>
    ${CEN_HEADER_PREFIX}/events/joy_axis_event.hpp>
    ${CEN_HEADER_PREFIX}/events/joy_ball_event.hpp>
    ${CEN_HEADER_PREFIX}/events/joy_button_event.hpp>
    ${CEN_HEADER_PREFIX}/events/joy_device_event.hpp>
    ${CEN_HEADER_PREFIX}/events/joy_hat_event.hpp>
    ${CEN_HEADER_PREFIX}/events/joy_hat_position.hpp>
    ${CEN_HEADER_PREFIX}/events/keyboard_event.hpp>
    ${CEN_HEADER_PREFIX}/events/mouse_button_event.hpp>
    ${CEN_HEADER_PREFIX}/events/mouse_motion_event.hpp>
    ${CEN_HEADER_PREFIX}/events/mouse_wheel_direction.hpp>
    ${CEN_HEADER_PREFIX}/events/mouse_wheel_event.hpp>
    ${CEN_HEADER_PREFIX}/events/multi_gesture_event.hpp>
    ${CEN_HEADER_PREFIX}/events/quit_event.hpp>
    ${CEN_HEADER_PREFIX}/events/sensor_event.hpp>
    ${CEN_HEADER_PREFIX}/events/text_editing_event.hpp>
    ${CEN_HEADER_PREFIX}/events/text_input_event.hpp>
    ${CEN_HEADER_PREFIX}/events/touch_finger_event.hpp>
    ${CEN_HEADER_PREFIX}/events/user_event.hpp>
    ${CEN_HEADER_PREFIX}/events/window_event.hpp>
    ${CEN_HEADER_PREFIX}/events/window_event_id.hpp>

    ${CEN_HEADER_PREFIX}/filesystem/base_path.hpp>
    ${CEN_HEADER_PREFIX}/filesystem/file.hpp>
    ${CEN_HEADER_PREFIX}/filesystem/file_mode.hpp>
    ${CEN_HEADER_PREFIX}/filesystem/file_type.hpp>
    ${CEN_HEADER_PREFIX}/filesystem/preferred_path.hpp>
    ${CEN_HEADER_PREFIX}/filesystem/seek_mode.hpp>

    ${CEN_HEADER_PREFIX}/hints/android_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/apple_tv_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/common_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/controller_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/d3d_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/emscripten_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/enum_hint.hpp>
    ${CEN_HEADER_PREFIX}/hints/hint_priority.hpp>
    ${CEN_HEADER_PREFIX}/hints/hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/joystick_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/mac_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/mouse_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/qtwayland_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/raspberry_pi_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/windows_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/winrt_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/x11_hints.hpp>
    ${CEN_HEADER_PREFIX}/hints/xinput_hints.hpp>

    ${CEN_HEADER_PREFIX}/input/button_state.hpp>
    ${CEN_HEADER_PREFIX}/input/controller.hpp>
    ${CEN_HEADER_PREFIX}/input/controller_axis.hpp>
    ${CEN_HEADER_PREFIX}/input/controller_bind_type.hpp>
    ${CEN_HEADER_PREFIX}/input/controller_button.hpp>
    ${CEN_HEADER_PREFIX}/input/controller_type.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_condition.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_constant.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_custom.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_direction.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_direction_type.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_effect.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_left_right.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_periodic.hpp>
    ${CEN_HEADER_PREFIX}/input/haptic_ramp.hpp>
    ${CEN_HEADER_PREFIX}/input/hat_state.hpp>
    ${CEN_HEADER_PREFIX}/input/joystick.hpp>
    ${CEN_HEADER_PREFIX}/input/joystick_power.hpp>
    ${CEN_HEADER_PREFIX}/input/joystick_type.hpp>
    ${CEN_HEADER_PREFIX}/input/key_code.hpp>
    ${CEN_HEADER_PREFIX}/input/key_modifier.hpp>
    ${CEN_HEADER_PREFIX}/input/keyboard.hpp>
    ${CEN_HEADER_PREFIX}/input/keycodes.hpp>
    ${CEN_HEADER_PREFIX}/input/mouse.hpp>
    ${CEN_HEADER_PREFIX}/input/mouse_button.hpp>
    ${CEN_HEADER_PREFIX}/input/scan_code.hpp>
    ${CEN_HEADER_PREFIX}/input/scancodes.hpp>
    ${CEN_HEADER_PREFIX}/input/sensor.hpp>
    ${CEN_HEADER_PREFIX}/input/sensor_type.hpp>
    ${CEN_HEADER_PREFIX}/input/touch.hpp>
    ${CEN_HEADER_PREFIX}/input/touch_device_type.hpp>

    ${CEN_HEADER_PREFIX}/math/area.hpp>
    ${CEN_HEADER_PREFIX}/math/point.hpp>
    ${CEN_HEADER_PREFIX}/math/rect.hpp>
    ${CEN_HEADER_PREFIX}/math/vector3.hpp>

    ${CEN_HEADER_PREFIX}/system/battery.hpp>
    ${CEN_HEADER_PREFIX}/system/byte_order.hpp>
    ${CEN_HEADER_PREFIX}/system/clipboard.hpp>
    ${CEN_HEADER_PREFIX}/system/counter.hpp>
    ${CEN_HEADER_PREFIX}/system/cpu.hpp>
    ${CEN_HEADER_PREFIX}/system/locale.hpp>
    ${CEN_HEADER_PREFIX}/system/open_url.hpp>
    ${CEN_HEADER_PREFIX}/system/platform.hpp>
    ${CEN_HEADER_PREFIX}/system/power_state.hpp>
    ${CEN_HEADER_PREFIX}/system/ram.hpp>
    ${CEN_HEADER_PREFIX}/system/shared_object.hpp>

    ${CEN_HEADER_PREFIX}/thread/condition.hpp>
    ${CEN_HEADER_PREFIX}/thread/lock_status.hpp>
    ${CEN_HEADER_PREFIX}/thread/mutex.hpp>
    ${CEN_HEADER_PREFIX}/thread/scoped_lock.hpp>
    ${CEN_HEADER_PREFIX}/thread/semaphore.hpp>
    ${CEN_HEADER_PREFIX}/thread/thread.hpp>
    ${CEN_HEADER_PREFIX}/thread/thread_priority.hpp>
    ${CEN_HEADER_PREFIX}/thread/try_lock.hpp>

    ${CEN_HEADER_PREFIX}/video/blend_factor.hpp>
    ${CEN_HEADER_PREFIX}/video/blend_mode.hpp>
    ${CEN_HEADER_PREFIX}/video/blend_op.hpp>
    ${CEN_HEADER_PREFIX}/video/button_order.hpp>
    ${CEN_HEADER_PREFIX}/video/color.hpp>
    ${CEN_HEADER_PREFIX}/video/colors.hpp>
    ${CEN_HEADER_PREFIX}/video/cursor.hpp>
    ${CEN_HEADER_PREFIX}/video/flash_op.hpp>
    ${CEN_HEADER_PREFIX}/video/font.hpp>
    ${CEN_HEADER_PREFIX}/video/font_cache.hpp>
    ${CEN_HEADER_PREFIX}/video/graphics_drivers.hpp>
    ${CEN_HEADER_PREFIX}/video/message_box.hpp>
    ${CEN_HEADER_PREFIX}/video/message_box_type.hpp>
    ${CEN_HEADER_PREFIX}/video/palette.hpp>
    ${CEN_HEADER_PREFIX}/video/pixel_format.hpp>
    ${CEN_HEADER_PREFIX}/video/pixel_format_info.hpp>
    ${CEN_HEADER_PREFIX}/video/renderer.hpp>
    ${CEN_HEADER_PREFIX}/video/renderer_info.hpp>
    ${CEN_HEADER_PREFIX}/video/scale_mode.hpp>
    ${CEN_HEADER_PREFIX}/video/screen.hpp>
    ${CEN_HEADER_PREFIX}/video/surface.hpp>
    ${CEN_HEADER_PREFIX}/video/system_cursor.hpp>
    ${CEN_HEADER_PREFIX}/video/texture.hpp>
    ${CEN_HEADER_PREFIX}/video/texture_access.hpp>
    ${CEN_HEADER_PREFIX}/video/unicode_string.hpp>
    ${CEN_HEADER_PREFIX}/video/window.hpp>
    ${CEN_HEADER_PREFIX}/video/window_utils.hpp>

    ${CEN_HEADER_PREFIX}/video/opengl/gl_attribute.hpp>
    ${CEN_HEADER_PREFIX}/video/opengl/gl_context.hpp>
    ${CEN_HEADER_PREFIX}/video/opengl/gl_core.hpp>
    ${CEN_HEADER_PREFIX}/video/opengl/gl_library.hpp>

    ${CEN_HEADER_PREFIX}/video/vulkan/vk_core.hpp>
    ${CEN_HEADER_PREFIX}/video/vulkan/vk_library.hpp>

    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/everything.hpp>
    )

target_include_directories(${CENTURION_LIB_TARGET}
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>

    PUBLIC INTERFACE
    $<BUILD_INTERFACE:${SDL2_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${SDL2_IMAGE_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${SDL2_TTF_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${SDL2_MIXER_INCLUDE_DIRS}>
    )

target_link_libraries(${CENTURION_LIB_TARGET} PUBLIC INTERFACE
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    )

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${CENTURION_LIB_TARGET} PRIVATE INTERFACE
      /EHsc
      /MP
      /W4
      /Zc:preprocessor # Enable conforming preprocessor
      /Zc:__cplusplus  # Force MSVC to use __cplusplus macro with correct value
      )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${CENTURION_LIB_TARGET} PRIVATE INTERFACE
      /EHsc
      )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${CENTURION_LIB_TARGET} PRIVATE INTERFACE
      -Wall
      -Wextra
      -Wpedantic
      -Wconversion
      -Wc++17-compat
      )
endif ()

if (CEN_TESTS)
  add_subdirectory(test)
endif ()

if (CEN_EXAMPLES)
  add_subdirectory(examples)
endif ()

if (CEN_INSTALL)
  message("Installing...")

  include(CMakePackageConfigHelpers)
  include(GNUInstallDirs)

  set(CEN_PACKAGE_NAME centurion)
  set(CEN_TARGETS_EXPORT_NAME "${CEN_PACKAGE_NAME}-targets")
  set(CEN_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
  set(CEN_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${CEN_PACKAGE_NAME}")

  set(CEN_CONFIG_FILE "${CEN_GENERATED_DIR}/${CEN_PACKAGE_NAME}-config.cmake")
  set(CEN_VERSION_FILE "${CEN_GENERATED_DIR}/${CEN_PACKAGE_NAME}-config-version.cmake")

  write_basic_package_version_file(${CEN_VERSION_FILE}
      VERSION ${CMAKE_PROJECT_VERSION}
      COMPATIBILITY SameMinorVersion
      ARCH_INDEPENDENT)

  configure_package_config_file("${PROJECT_SOURCE_DIR}/centurion-config.cmake.in"
      "${CEN_CONFIG_FILE}"
      INSTALL_DESTINATION ${CEN_CONFIG_INSTALL_DIR})

  # Targets:
  #   * <prefix>/lib/libbar.a
  #   * <prefix>/lib/libbaz.a
  #   * header location after install: <prefix>/include/foo/Bar.hpp
  #   * headers can be included by C++ code `#include <foo/Bar.hpp>`
  install(TARGETS ${CENTURION_LIB_TARGET}
      EXPORT "${CEN_TARGETS_EXPORT_NAME}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
      INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

  # Headers:
  #   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
  #   * Source/foo/Baz.hpp -> <prefix>/include/foo/Baz.hpp
  install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/"
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp")

  # Config
  #   * <prefix>/lib/cmake/Foo/FooConfig.cmake
  #   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
  install(FILES "${CEN_CONFIG_FILE}" "${CEN_VERSION_FILE}"
      DESTINATION "${CEN_CONFIG_INSTALL_DIR}")

  # Config
  #   * <prefix>/lib/cmake/Foo/FooTargets.cmake
  install(EXPORT "${CEN_TARGETS_EXPORT_NAME}"
      NAMESPACE "${CEN_PACKAGE_NAME}::"
      DESTINATION "${CEN_CONFIG_INSTALL_DIR}")
endif ()
