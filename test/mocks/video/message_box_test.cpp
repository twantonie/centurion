#include "video/message_box.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

// clang-format off
extern "C" {
FAKE_VALUE_FUNC(int, SDL_ShowSimpleMessageBox, Uint32, const char*, const char*, SDL_Window*)
FAKE_VALUE_FUNC(int, SDL_ShowMessageBox, const SDL_MessageBoxData*, int*)
}
// clang-format on

class MessageBoxTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_DestroyWindow)
    RESET_FAKE(SDL_CreateWindow)
    RESET_FAKE(SDL_ShowSimpleMessageBox)
    RESET_FAKE(SDL_ShowMessageBox)
  }
};

TEST_F(MessageBoxTest, ShowStatic)
{
  const std::string title{"foo"};
  const std::string message{"bar"};

  {  // With defaults
    cen::message_box::show(title, message);
    ASSERT_EQ(1u, SDL_ShowSimpleMessageBox_fake.call_count);

#if SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT | SDL_MESSAGEBOX_INFORMATION,
              static_cast<int>(SDL_ShowSimpleMessageBox_fake.arg0_val));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    ASSERT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    ASSERT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    ASSERT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }

  {  // With custom type
    cen::message_box::show(title, message, cen::message_box_type::error);
    ASSERT_EQ(2u, SDL_ShowSimpleMessageBox_fake.call_count);

#if SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT | SDL_MESSAGEBOX_ERROR,
              static_cast<int>(SDL_ShowSimpleMessageBox_fake.arg0_val));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    ASSERT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    ASSERT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    ASSERT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }

  {  // With custom type and button order
    cen::message_box::show(title,
                           message,
                           cen::message_box_type::error,
                           cen::button_order::right_to_left);
    ASSERT_EQ(3u, SDL_ShowSimpleMessageBox_fake.call_count);

#if SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT | SDL_MESSAGEBOX_ERROR,
              static_cast<int>(SDL_ShowSimpleMessageBox_fake.arg0_val));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    ASSERT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    ASSERT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    ASSERT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }
}

TEST_F(MessageBoxTest, Show)
{
  cen::message_box mb;

  mb.show();
  ASSERT_EQ(1u, SDL_ShowMessageBox_fake.call_count);

  cen::window_handle window{nullptr};
  mb.show(window);
  ASSERT_EQ(2u, SDL_ShowMessageBox_fake.call_count);
}