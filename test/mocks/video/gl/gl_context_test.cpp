#include "video/opengl/gl_context.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_GL_MakeCurrent, SDL_Window*, SDL_GLContext)
}

class OpenGLContextTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GL_MakeCurrent)
  }

  cen::gl::context_handle m_context{nullptr};
};

TEST_F(OpenGLContextTest, Construction)
{
  ASSERT_THROW(cen::gl::context{nullptr}, cen::cen_error);
  ASSERT_NO_THROW(cen::gl::context_handle{nullptr});
}

TEST_F(OpenGLContextTest, MakeCurrent)
{
  std::array flags{cen::u32{cen::window::opengl}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, flags.data(), cen::isize(flags));

  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GL_MakeCurrent, values.data(), cen::isize(values));

  cen::window_handle window{nullptr};
  ASSERT_EQ(cen::failure, m_context.make_current(window));
  ASSERT_EQ(cen::success, m_context.make_current(window));
  ASSERT_EQ(2u, SDL_GL_MakeCurrent_fake.call_count);
}
