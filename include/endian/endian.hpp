/**
 * @file endian.hpp
 * @brief Minimal endian utilities for modern C++.
 *
 * Header-only.
 *
 * Provides:
 *   - endian::is_little_endian()
 *   - endian::is_big_endian()
 *   - endian::bswap16/32/64()
 *   - endian::load_le<T>(), endian::load_be<T>()
 *   - endian::store_le<T>(), endian::store_be<T>()
 *
 * Supported types for load/store:
 *   - std::uint16_t, std::uint32_t, std::uint64_t
 *
 * MIT License
 */

#pragma once

#include <cstdint>
#include <type_traits>

namespace endian
{
  /**
   * @brief Check if the host is little-endian.
   */
  inline bool is_little_endian() noexcept
  {
    const std::uint16_t x = 0x0102;
    const auto *p = reinterpret_cast<const std::uint8_t *>(&x);
    return p[0] == 0x02;
  }

  /**
   * @brief Check if the host is big-endian.
   */
  inline bool is_big_endian() noexcept
  {
    return !is_little_endian();
  }

  inline std::uint16_t bswap16(std::uint16_t v) noexcept
  {
    return static_cast<std::uint16_t>((v >> 8) | (v << 8));
  }

  inline std::uint32_t bswap32(std::uint32_t v) noexcept
  {
    return ((v & 0x000000FFu) << 24) |
           ((v & 0x0000FF00u) << 8) |
           ((v & 0x00FF0000u) >> 8) |
           ((v & 0xFF000000u) >> 24);
  }

  inline std::uint64_t bswap64(std::uint64_t v) noexcept
  {
    return ((v & 0x00000000000000FFull) << 56) |
           ((v & 0x000000000000FF00ull) << 40) |
           ((v & 0x0000000000FF0000ull) << 24) |
           ((v & 0x00000000FF000000ull) << 8) |
           ((v & 0x000000FF00000000ull) >> 8) |
           ((v & 0x0000FF0000000000ull) >> 24) |
           ((v & 0x00FF000000000000ull) >> 40) |
           ((v & 0xFF00000000000000ull) >> 56);
  }

  namespace detail
  {
    template <typename T>
    struct is_supported : std::bool_constant<
                              std::is_same_v<T, std::uint16_t> ||
                              std::is_same_v<T, std::uint32_t> ||
                              std::is_same_v<T, std::uint64_t>>
    {
    };

    template <typename T>
    inline T bswap(T v) noexcept
    {
      if constexpr (std::is_same_v<T, std::uint16_t>)
        return static_cast<T>(bswap16(v));
      if constexpr (std::is_same_v<T, std::uint32_t>)
        return static_cast<T>(bswap32(v));
      return static_cast<T>(bswap64(v));
    }
  }

  /**
   * @brief Load unsigned integer from little-endian bytes.
   * @param p Pointer to buffer (at least sizeof(T) bytes)
   */
  template <typename T>
  inline T load_le(const std::uint8_t *p) noexcept
  {
    static_assert(detail::is_supported<T>::value, "endian::load_le<T>: unsupported type");

    T v = 0;
    for (std::size_t i = 0; i < sizeof(T); ++i)
      v |= static_cast<T>(static_cast<T>(p[i]) << (8 * i));

    return v;
  }

  /**
   * @brief Load unsigned integer from big-endian bytes.
   * @param p Pointer to buffer (at least sizeof(T) bytes)
   */
  template <typename T>
  inline T load_be(const std::uint8_t *p) noexcept
  {
    static_assert(detail::is_supported<T>::value, "endian::load_be<T>: unsupported type");

    T v = 0;
    for (std::size_t i = 0; i < sizeof(T); ++i)
      v = static_cast<T>((v << 8) | static_cast<T>(p[i]));

    return v;
  }

  /**
   * @brief Store unsigned integer to little-endian bytes.
   * @param p Pointer to output buffer (at least sizeof(T) bytes)
   */
  template <typename T>
  inline void store_le(std::uint8_t *p, T value) noexcept
  {
    static_assert(detail::is_supported<T>::value, "endian::store_le<T>: unsupported type");

    for (std::size_t i = 0; i < sizeof(T); ++i)
      p[i] = static_cast<std::uint8_t>((value >> (8 * i)) & 0xFF);
  }

  /**
   * @brief Store unsigned integer to big-endian bytes.
   * @param p Pointer to output buffer (at least sizeof(T) bytes)
   */
  template <typename T>
  inline void store_be(std::uint8_t *p, T value) noexcept
  {
    static_assert(detail::is_supported<T>::value, "endian::store_be<T>: unsupported type");

    for (std::size_t i = 0; i < sizeof(T); ++i)
      p[i] = static_cast<std::uint8_t>((value >> (8 * (sizeof(T) - 1 - i))) & 0xFF);
  }

} // namespace endian
