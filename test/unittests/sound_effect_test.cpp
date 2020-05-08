#ifndef CENTURION_NOAUDIO

#include <catch.hpp>

#include "audio.h"
#include "centurion_exception.h"
#include "log.h"
#include "timer.h"

using namespace centurion;
using namespace audio;

static constexpr auto path = "resources/click.wav";

TEST_CASE("SoundEffect(file)", "[SoundEffect]")
{
  CHECK_THROWS_AS(SoundEffect("somebadpath"), CenturionException);
}

TEST_CASE("SoundEffect(SoundEffect&&)", "[SoundEffect]")
{
  SoundEffect sound{path};
  SoundEffect sound2{std::move(sound)};

  Mix_Chunk* sdlSound = sound;
  CHECK(!sdlSound);
}

TEST_CASE("SoundEffect smart pointer factory methods", "[SoundEffect]")
{
  CHECK(SoundEffect::unique(path));
  CHECK(SoundEffect::shared(path));
  CHECK_THROWS_AS(SoundEffect::unique(""), CenturionException);
  CHECK_THROWS_AS(SoundEffect::shared(""), CenturionException);
}

TEST_CASE("SoundEffect::play", "[SoundEffect]")
{
  SoundEffect sound{path};

  CHECK(!sound.playing());

  sound.play();
  CHECK(sound.playing());

  sound.stop();
  CHECK(!sound.playing());

  sound.play(5);
  CHECK(sound.playing());
}

TEST_CASE("SoundEffect looping", "[SoundEffect]")
{
  SoundEffect sound{path};
  sound.set_volume(1);

  sound.play(10);
  CHECK(sound.playing());
  sound.stop();

  CHECK(loopForever < 0);

  CHECK_NOTHROW(sound.play(loopForever));
  CHECK(sound.playing());

  sound.stop();
  CHECK(!sound.playing());
}

TEST_CASE("SoundEffect::stop", "[SoundEffect]")
{
  SoundEffect sound{path};

  sound.play();
  sound.stop();
  CHECK(!sound.playing());
}

TEST_CASE("SoundEffect::fade_in", "[SoundEffect]")
{
  SoundEffect sound{path};

  sound.fade_in(-1);
  sound.stop();

  CHECK_NOTHROW(sound.fade_in(0));
  CHECK(!sound.playing());

  sound.fade_in(100);
  CHECK(sound.playing());
}

TEST_CASE("SoundEffect::fade_out", "[SoundEffect]")
{
  SoundEffect sound{path};

  CHECK_NOTHROW(sound.fade_out(0));
  CHECK(!sound.playing());

  sound.play();
  sound.fade_out(10);
  CHECK(sound.playing());

  Timer::delay(1000);
  CHECK(!sound.playing());
}

TEST_CASE("SoundEffect:set_volume", "[SoundEffect]")
{
  SoundEffect sound{path};

  SECTION("Valid volume")
  {
    const auto volume = 27;
    sound.set_volume(volume);
    CHECK(volume == sound.volume());
  }

  SECTION("Volume underflow")
  {
    const auto volume = -1;
    sound.set_volume(volume);
    CHECK(sound.volume() == 0);
  }

  SECTION("Volume overflow")
  {
    const auto volume = maxVolume + 1;
    sound.set_volume(volume);
    CHECK(sound.volume() == maxVolume);
  }
}

TEST_CASE("SoundEffect::volume", "[SoundEffect]")
{
  SoundEffect sound{path};
  CHECK(sound.volume() == maxVolume);
  CHECK(sound.volume() == 128);  // because of the documentation guarantee
  CHECK(maxVolume == MIX_MAX_VOLUME);
}

TEST_CASE("SoundEffect::playing", "[SoundEffect]")
{
  SoundEffect sound{path};

  CHECK(!sound.playing());
  sound.play(2);
  CHECK(sound.playing());
}

TEST_CASE("SoundEffect::to_string", "[SoundEffect]")
{
  SoundEffect sound{path};
  Log::msgf(Category::Test, "%s", sound.to_string().c_str());
}

TEST_CASE("SoundEffect::max_volume", "[SoundEffect]")
{
  CHECK(SoundEffect::max_volume() == MIX_MAX_VOLUME);
}

#endif