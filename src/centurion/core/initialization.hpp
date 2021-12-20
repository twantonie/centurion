#ifndef CENTURION_CORE_INITIALIZATION_HPP_
#define CENTURION_CORE_INITIALIZATION_HPP_

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional

#include "../common.hpp"
#include "exception.hpp"
#include "features.hpp"

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

namespace cen {

struct SDLConfig final {
  Uint32 flags{SDL_INIT_EVERYTHING};
};

class SDLLibrary final {
 public:
  explicit SDLLibrary(const SDLConfig& cfg = {})
  {
    if (SDL_Init(cfg.flags) < 0) {
      throw SDLError{};
    }
  }

  ~SDLLibrary() noexcept { SDL_Quit(); }
};

#ifndef CENTURION_NO_SDL_IMAGE

struct IMGConfig final {
  int flags{IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP};
};

class IMGLibrary final {
 public:
  explicit IMGLibrary(const IMGConfig& cfg = {})
  {
    if (!IMG_Init(cfg.flags)) {
      throw IMGError{};
    }
  }

  ~IMGLibrary() noexcept { IMG_Quit(); }
};

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

struct MixConfig final {
  int flags{MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID | MIX_INIT_MOD |
            MIX_INIT_OPUS};
  int frequency{MIX_DEFAULT_FREQUENCY};
  Uint16 format{MIX_DEFAULT_FORMAT};
  int channels{MIX_DEFAULT_CHANNELS};
  int chunk_size{4096};
};

class MixLibrary final {
 public:
  explicit MixLibrary(const MixConfig& cfg = {})
  {
    if (!Mix_Init(cfg.flags)) {
      throw MixError{};
    }

    if (Mix_OpenAudio(cfg.frequency, cfg.format, cfg.channels, cfg.chunk_size) == -1) {
      throw MixError{};
    }
  }

  ~MixLibrary() noexcept
  {
    Mix_CloseAudio();
    Mix_Quit();
  }
};

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

class TTFLibrary final {
 public:
  TTFLibrary()
  {
    if (TTF_Init() == -1) {
      throw TTFError{};
    }
  }

  ~TTFLibrary() noexcept { TTF_Quit(); }
};

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen

#endif  // CENTURION_CORE_INITIALIZATION_HPP_
