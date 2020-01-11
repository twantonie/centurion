#pragma once
#include <string>
#include <optional>
#include <SDL_ttf.h>

namespace centurion {

/**
 * The Font class represents a TrueType font.
 *
 * @since 3.0.0
 */
class Font {
 private:
  TTF_Font* font = nullptr;
  int style = 0;
  int size = 0;

  /**
   * Enables the font style associated with the supplied bit mask. The possible values are
   * TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE and TTF_STYLE_STRIKETHROUGH.
   *
   * @param mask the bit mask of the font style to enable.
   * @since 3.0.0
   */
  void add_style(int mask) noexcept;

  /**
   * Removes the font style associated with the supplied bit mask. The possible values are
   * TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE and TTF_STYLE_STRIKETHROUGH.
   *
   * @param mask the bit mask of the font style to disable.
   * @since 3.0.0
   */
  void remove_style(int mask) noexcept;

 public:
  /**
   * @param file the file path of the TrueType font file.
   * @param size the font size, must be greater than zero.
   * @throws std::invalid_argument if the supplied size isn't greater than zero.
   * @throws CenturionException if the font cannot be loaded.
   * @since 3.0.0
   */
  Font(const std::string& file, int size);

  /**
   * The copy constructor is deleted for font instances.
   *
   * @since 3.0.0
   */
  Font(const Font&) noexcept = delete;

  /**
   * Creates a font by moving the supplied font.
   *
   * @param other the font that will have its fields moved.
   * @since 3.0.0
   */
  Font(Font&& other) noexcept;

  virtual ~Font() noexcept;

  /**
   * The copy assignment operator is deleted for font instances.
   *
   * @since 3.0.0
   */
  Font& operator=(const Font&) noexcept = delete;

  /**
   * Moves the supplied font into this font.
   *
   * @param other the font that will have its fields moved.
   * @return the created font.
   * @since 3.0.0
   */
  [[nodiscard]]
  Font& operator=(Font&& other) noexcept;

  /**
   * Resets the style of the font.
   *
   * @since 3.0.0
   */
  void reset() noexcept;

  /**
   * Sets the bold property of the font.
   *
   * @param bold true if the font should be bold; false otherwise.
   * @since 3.0.0
   */
  void set_bold(bool bold) noexcept;

  /**
   * Sets the italic property of the font.
   *
   * @param bold true if the font should be italic; false otherwise.
   * @since 3.0.0
   */
  void set_italic(bool italic) noexcept;

  /**
   * Sets the underlined property of the font.
   *
   * @param bold true if the font should be underlined; false otherwise.
   * @since 3.0.0
   */
  void set_underlined(bool underlined) noexcept;

  /**
   * Sets the strikethrough property of the font.
   *
   * @param bold true if the font should be strikethrough; false otherwise.
   * @since 3.0.0
   */
  void set_strikethrough(bool strikethrough) noexcept;

  /**
   * Sets the outlined property of the font.
   *
   * @param bold true if the font should be outlined; false otherwise.
   * @since 3.0.0
   */
  void set_outlined(bool outlined) noexcept;

  /**
   * Returns the size of the font.
   *
   * @return the size of the font.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_size() const noexcept;

  /**
   * Returns the maximum height of a character in this font. This is usually the same as the
   * point size.
   *
   * @return the maximum height of a character in this font.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_height() const noexcept;

  /**
   * Returns the offset from the baseline to the bottom of the font characters. The returned
   * value is negative, relative to the baseline.
   *
   * @return the offset from the baseline to the bottom of the font characters.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_descent() const noexcept;

  /**
   * Returns the offset from the baseline to the top of the font characters. The returned
   * value is positive, relative to the baseline.
   *
   * @return the offset from the baseline to the top of the font characters.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_ascent() const noexcept;

  /**
   * Returns the recommended pixel height of rendered text in the font. The returned
   * value is usually larger than the height of the font.
   *
   * @return Returns the recommended pixel height of rendered text in the font.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_line_skip() const noexcept;

  /**
   * Returns the number of available font faces in the font.
   *
   * @return the number of available font faces in the font.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_font_faces() const noexcept;

  /**
   * Indicates whether or not the font is bold.
   *
   * @return true if the font is bold; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_bold() const noexcept;

  /**
   * Indicates whether or not the font is italic.
   *
   * @return true if the font is italic; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_italic() const noexcept;

  /**
   * Indicates whether or not the font is underlined.
   *
   * @return true if the font is underlined; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_underlined() const noexcept;

  /**
   * Indicates whether or not the font is a strikethrough font.
   *
   * @return true if the font is a strikethrough font; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_strikethrough() const noexcept;

  /**
   * Indicates whether or not the font is outlined.
   *
   * @return true if the font is outlined; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_outlined() const noexcept;

  /**
   * Indicates whether or not the font is fixed width.
   *
   * @return true if the font is fixed width; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_fixed_width() const noexcept;

  /**
   * Returns the family name of the font.
   *
   * @return the family name of the font.
   * @since 3.0.0
   */
  [[nodiscard]]
  std::string get_family_name() const noexcept;

  /**
   * Returns the font face style name of the font. This information may not be available.
   *
   * @return the font face style name of the font.
   * @since 3.0.0
   */
  [[nodiscard]]
  std::optional<std::string> get_style_name() const noexcept;

  /**
   * Returns the width of the supplied string, if it was rendered using the font.
   *
   * @param s the string to determine the width of.
   * @return the width of the supplied string, if it was rendered using the font.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_string_width(const std::string& s) const noexcept;

  /**
   * Returns the height of the supplied string, if it was rendered using the font.
   *
   * @param s the string to determine the height of.
   * @return the height of the supplied string, if it was rendered using the font.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_string_height(const std::string& s) const noexcept;

  /*implicit*/ operator TTF_Font*() const noexcept;

};

}
