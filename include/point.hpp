/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file point.hpp
 *
 * @brief Provides a simple two-dimensional point class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_POINT_HEADER
#define CENTURION_POINT_HEADER

#include <SDL.h>

#include <cmath>
#include <string>
#include <type_traits>

#include "centurion_api.hpp"
#include "centurion_types.hpp"

namespace centurion {

template <typename T>
class basic_point;

template <typename U>
constexpr bool operator==(const basic_point<U>& lhs,
                          const basic_point<U>& rhs) noexcept;

template <typename U>
constexpr bool operator!=(const basic_point<U>& lhs,
                          const basic_point<U>& rhs) noexcept;

template <typename U>
constexpr basic_point<U> operator-(const basic_point<U>& lhs,
                                   const basic_point<U>& rhs) noexcept;

template <typename U>
constexpr basic_point<U> operator+(const basic_point<U>& lhs,
                                   const basic_point<U>& rhs) noexcept;

/**
 * @class basic_point
 *
 * @brief Represents an integer or floating-point based 2D point.
 *
 * @details There are two pre-defined type aliases pre-defined for this
 * class, `point_i` and `point_f`.
 *
 * @tparam T the type of the components of the point. Must be either integral
 * or real. Defaults to `float`.
 *
 * @since 4.0.0
 *
 * @see `point_i`
 * @see `point_f`
 *
 * @headerfile point.hpp
 */
template <typename T = float>
class basic_point final {
 public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  /**
   * @brief Creates a point with coordinates (0, 0).
   *
   * @since 4.0.0
   */
  constexpr basic_point() noexcept = default;

  /**
   * @brief Creates a point with the specified coordinates.
   *
   * @param px the x-coordinate of the point.
   * @param py the y-coordinate of the point.
   *
   * @since 4.0.0
   */
  constexpr basic_point(T px, T py) noexcept : m_x{px}, m_y{py} {}

  /**
   * @brief Sets the x-coordinate of the point.
   *
   * @param px the new x-coordinate of the point.
   *
   * @since 4.0.0
   */
  constexpr void set_x(T px) noexcept { m_x = px; }

  /**
   * @brief Sets the y-coordinate of the point.
   *
   * @param py the new y-coordinate of the point.
   *
   * @since 4.0.0
   */
  constexpr void set_y(T py) noexcept { m_y = py; }

  /**
   * @brief Sets the values of the x- and y-coordinates of the point.
   *
   * @param px the new x-coordinate of the point.
   * @param py the new y-coordinate of the point.
   *
   * @since 4.0.0
   */
  constexpr void set(T px, T py) noexcept
  {
    m_x = px;
    m_y = py;
  }

  /**
   * @brief Copies the components of the supplied point into this point.
   *
   * @param other the point that will be copied.
   *
   * @since 4.0.0
   */
  constexpr void set(const basic_point<T>& other) noexcept
  {
    m_x = other.m_x;
    m_y = other.m_y;
  }

  /**
   * @brief Calculates and returns the distance from this point to the supplied
   * point.
   *
   * @details It doesn't matter in which order the method call is performed
   * (i.e. `a.distance_to(b) == b.distance_to(a)`)
   *
   * @param other the point to calculate the distance to.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto distance_to(const basic_point<T>& other) const noexcept
      -> T
  {
    return std::sqrt(std::abs(m_x - other.m_x) + std::abs(m_y - other.m_y));
  }

  /**
   * @brief Returns a textual representation of the point.
   *
   * @return a textual representation of the point.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto to_string() const -> std::string
  {
    return "[Point | X: " + std::to_string(m_x) +
           ", Y: " + std::to_string(m_y) + "]";
  }

  /**
   * @brief Returns the x-coordinate of the point.
   *
   * @return the x-coordinate of the point.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto x() const noexcept -> T { return m_x; }

  /**
   * @brief Returns the y-coordinate of the point.
   *
   * @return the y-coordinate of the point.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto y() const noexcept -> T { return m_y; }

  /**
   * @brief Indicates whether or not the point is considered to be equal to the
   * supplied point.
   *
   * @details This method is only available if the points are floating-point
   * based.
   *
   * @param other the other point to compare this point with.
   * @param epsilon the exclusive limit on the maximum allowed absolute
   * difference between the coordinates of the points.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename X = detail::if_floating_t<U>>
  [[nodiscard]] auto equals(const basic_point<T>& other,
                            T epsilon = 0.0001) const noexcept -> bool
  {
    return std::abs(m_x - other.m_x) < epsilon &&
           std::abs(m_y - other.m_y) < epsilon;
  }

  /**
   * @brief Converts to `SDL_Point`.
   *
   * @return an `SDL_Point` instance based on the point.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr explicit operator SDL_Point() const noexcept
  {
    return {static_cast<int>(m_x), static_cast<int>(m_y)};
  }

  /**
   * @brief Converts to `SDL_Point`.
   *
   * @return an `SDL_FPoint` instance based on the point.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr explicit operator SDL_FPoint() const noexcept
  {
    return {static_cast<float>(m_x), static_cast<float>(m_y)};
  }

  /**
   * @brief Creates and returns a point in which the coordinates are the sums
   * obtained by adding the x- and y-coordinates of the supplied points.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   *
   * @return a point in which the coordinates are the sums obtained by adding
   * the x- and y-coordinates of the supplied points.
   *
   * @since 4.0.0
   */
  friend constexpr auto operator+
      <T>(const basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
      -> basic_point<T>;

  /**
   * @brief Converts to `SDL_Point*`.
   *
   * @note This conversion is only available if the point is based on `int`.
   *
   * @tparam U the type parameter, defaults to the type of the point
   * components.
   *
   * @return an `SDL_Point` pointer that is produced by reinterpreting the
   * invoked point.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, int>>
  [[nodiscard]] explicit operator SDL_Point*() noexcept
  {
    return reinterpret_cast<SDL_Point*>(this);
  }

  /**
   * @brief Converts to `const SDL_Point*`.
   *
   * @note This conversion is only available if the point is based on `int`.
   *
   * @tparam U the type parameter, defaults to the type of the point
   * components.
   *
   * @return a `const SDL_Point` pointer that is produced by reinterpreting the
   * invoked point.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, int>>
  [[nodiscard]] explicit operator const SDL_Point*() const noexcept
  {
    return reinterpret_cast<const SDL_Point*>(this);
  }

  /**
   * @brief Converts to `SDL_FPoint*`.
   *
   * @note This conversion is only available if the point is based on `int`.
   *
   * @tparam U the type parameter, defaults to the type of the point
   * components.
   *
   * @return an `SDL_FPoint` pointer that is produced by reinterpreting the
   * invoked point.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, float>>
  [[nodiscard]] explicit operator SDL_FPoint*() noexcept
  {
    return reinterpret_cast<SDL_FPoint*>(this);
  }

  /**
   * @brief Converts to `const SDL_FPoint*`.
   *
   * @note This conversion is only available if the point is based on `int`.
   *
   * @tparam U the type parameter, defaults to the type of the point
   * components.
   *
   * @return a `const SDL_FPoint` pointer that is produced by reinterpreting the
   * invoked point.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, float>>
  [[nodiscard]] explicit operator const SDL_FPoint*() const noexcept
  {
    return reinterpret_cast<const SDL_FPoint*>(this);
  }

  /**
   * @brief Creates and returns a point in which the coordinates are the
   * differences obtained by subtracting the x- and y-coordinates of the
   * supplied points.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   *
   * @return a point in which the coordinates are the differences obtained by
   * subtracting the x- and y-coordinates of the supplied points.
   *
   * @since 4.0.0
   */
  friend constexpr auto operator-
      <T>(const basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
      -> basic_point<T>;

  /**
   * @brief Indicates whether or not two points are considered to be equal.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   *
   * @return `true` if the points are equal; `false` otherwise.
   *
   * @since 4.0.0
   */
  friend constexpr auto operator==
      <T>(const basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
      -> bool;

  /**
   * @brief Indicates whether or not two points aren't considered to be equal.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   *
   * @return `true` if the points aren't equal; `false` otherwise.
   *
   * @since 4.0.0
   */
  friend constexpr auto operator!=
      <T>(const basic_point<T>& lhs, const basic_point<T>& rhs) noexcept
      -> bool;

 private:
  T m_x = 0;
  T m_y = 0;

  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                "Point type must be either integral or floating-point!");
  static_assert(std::is_trivial_v<T>, "Point type must be trivial!");
};

template <typename T>
inline constexpr auto operator+(const basic_point<T>& lhs,
                                const basic_point<T>& rhs) noexcept
    -> basic_point<T>
{
  return basic_point<T>{lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y};
}

template <typename T>
inline constexpr auto operator-(const basic_point<T>& lhs,
                                const basic_point<T>& rhs) noexcept
    -> basic_point<T>
{
  return basic_point<T>{lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y};
}

template <typename T>
inline constexpr auto operator==(const basic_point<T>& lhs,
                                 const basic_point<T>& rhs) noexcept -> bool
{
  return (lhs.m_x == rhs.m_x) && (lhs.m_y == rhs.m_y);
}

template <typename T>
inline constexpr auto operator!=(const basic_point<T>& lhs,
                                 const basic_point<T>& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

static_assert(std::is_nothrow_default_constructible_v<basic_point<float>>);
static_assert(std::is_nothrow_copy_constructible_v<basic_point<float>>);
static_assert(std::is_nothrow_move_constructible_v<basic_point<float>>);
static_assert(std::is_nothrow_copy_assignable_v<basic_point<float>>);
static_assert(std::is_nothrow_move_assignable_v<basic_point<float>>);
static_assert(sizeof(basic_point<int>) == sizeof(SDL_Point));
static_assert(sizeof(basic_point<float>) == sizeof(SDL_FPoint));

/**
 * @typedef point_i
 *
 * @brief Alias for `int` points.
 *
 * @since 4.0.0
 */
using point_i = basic_point<int>;

/**
 * @typedef point_f
 *
 * @brief Alias for `float` points.
 *
 * @since 4.0.0
 */
using point_f = basic_point<float>;

}  // namespace centurion

#endif  // CENTURION_POINT_HEADER