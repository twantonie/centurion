#include <gtest/gtest.h>

#include <iostream>  // clog

#include "message_box.hpp"

TEST(MessageBoxType, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_INFORMATION, cen::ToUnderlying(cen::MessageBoxType::Information));
  ASSERT_EQ(SDL_MESSAGEBOX_WARNING, cen::ToUnderlying(cen::MessageBoxType::Warning));
  ASSERT_EQ(SDL_MESSAGEBOX_ERROR, cen::ToUnderlying(cen::MessageBoxType::Error));
}

TEST(MessageBoxType, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::MessageBoxType>(0x41)), cen::Error);

  ASSERT_EQ("Information", cen::to_string(cen::MessageBoxType::Information));
  ASSERT_EQ("Error", cen::to_string(cen::MessageBoxType::Error));
  ASSERT_EQ("Warning", cen::to_string(cen::MessageBoxType::Warning));

  std::clog << "Message box type example: " << cen::MessageBoxType::Information << '\n';
}
