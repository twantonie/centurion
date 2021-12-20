#include "input/haptic_feature.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"

TEST(HapticFeature, Values)
{
  ASSERT_EQ(SDL_HAPTIC_CONSTANT, cen::ToUnderlying(cen::haptic_feature::constant));
  ASSERT_EQ(SDL_HAPTIC_SINE, cen::ToUnderlying(cen::haptic_feature::sine));
  ASSERT_EQ(SDL_HAPTIC_LEFTRIGHT, cen::ToUnderlying(cen::haptic_feature::left_right));
  ASSERT_EQ(SDL_HAPTIC_TRIANGLE, cen::ToUnderlying(cen::haptic_feature::triangle));
  ASSERT_EQ(SDL_HAPTIC_SAWTOOTHUP, cen::ToUnderlying(cen::haptic_feature::sawtooth_up));
  ASSERT_EQ(SDL_HAPTIC_SAWTOOTHDOWN, cen::ToUnderlying(cen::haptic_feature::sawtooth_down));
  ASSERT_EQ(SDL_HAPTIC_RAMP, cen::ToUnderlying(cen::haptic_feature::ramp));
  ASSERT_EQ(SDL_HAPTIC_SPRING, cen::ToUnderlying(cen::haptic_feature::spring));
  ASSERT_EQ(SDL_HAPTIC_DAMPER, cen::ToUnderlying(cen::haptic_feature::damper));
  ASSERT_EQ(SDL_HAPTIC_INERTIA, cen::ToUnderlying(cen::haptic_feature::inertia));
  ASSERT_EQ(SDL_HAPTIC_FRICTION, cen::ToUnderlying(cen::haptic_feature::friction));
  ASSERT_EQ(SDL_HAPTIC_CUSTOM, cen::ToUnderlying(cen::haptic_feature::custom));
  ASSERT_EQ(SDL_HAPTIC_GAIN, cen::ToUnderlying(cen::haptic_feature::gain));
  ASSERT_EQ(SDL_HAPTIC_AUTOCENTER, cen::ToUnderlying(cen::haptic_feature::autocenter));
  ASSERT_EQ(SDL_HAPTIC_STATUS, cen::ToUnderlying(cen::haptic_feature::status));
  ASSERT_EQ(SDL_HAPTIC_PAUSE, cen::ToUnderlying(cen::haptic_feature::pause));
}

TEST(HapticFeature, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::haptic_feature>(1u << 16u)), cen::Error);

  ASSERT_EQ("constant", cen::to_string(cen::haptic_feature::constant));
  ASSERT_EQ("sine", cen::to_string(cen::haptic_feature::sine));
  ASSERT_EQ("left_right", cen::to_string(cen::haptic_feature::left_right));
  ASSERT_EQ("triangle", cen::to_string(cen::haptic_feature::triangle));
  ASSERT_EQ("sawtooth_up", cen::to_string(cen::haptic_feature::sawtooth_up));
  ASSERT_EQ("sawtooth_down", cen::to_string(cen::haptic_feature::sawtooth_down));
  ASSERT_EQ("ramp", cen::to_string(cen::haptic_feature::ramp));
  ASSERT_EQ("spring", cen::to_string(cen::haptic_feature::spring));
  ASSERT_EQ("damper", cen::to_string(cen::haptic_feature::damper));
  ASSERT_EQ("inertia", cen::to_string(cen::haptic_feature::inertia));
  ASSERT_EQ("friction", cen::to_string(cen::haptic_feature::friction));
  ASSERT_EQ("custom", cen::to_string(cen::haptic_feature::custom));
  ASSERT_EQ("gain", cen::to_string(cen::haptic_feature::gain));
  ASSERT_EQ("autocenter", cen::to_string(cen::haptic_feature::autocenter));
  ASSERT_EQ("status", cen::to_string(cen::haptic_feature::status));
  ASSERT_EQ("pause", cen::to_string(cen::haptic_feature::pause));

  std::clog << "Haptic feature example: " << cen::haptic_feature::spring << '\n';
}
