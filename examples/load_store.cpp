#include <endian/endian.hpp>

#include <cstdint>
#include <iostream>

static void print_bytes(const std::uint8_t *p, std::size_t n)
{
  std::cout << std::hex;
  for (std::size_t i = 0; i < n; ++i)
  {
    std::cout << (i ? " " : "") << static_cast<unsigned>(p[i]);
  }
  std::cout << std::dec << "\n";
}

int main()
{
  std::uint8_t le[4] = {};
  std::uint8_t be[4] = {};

  const std::uint32_t value = 0xA1B2C3D4u;

  endian::store_le<std::uint32_t>(le, value);
  endian::store_be<std::uint32_t>(be, value);

  std::cout << "value : 0x" << std::hex << value << std::dec << "\n";

  std::cout << "LE bytes: ";
  print_bytes(le, 4);

  std::cout << "BE bytes: ";
  print_bytes(be, 4);

  const auto v1 = endian::load_le<std::uint32_t>(le);
  const auto v2 = endian::load_be<std::uint32_t>(be);

  std::cout << "load_le: 0x" << std::hex << v1 << "\n";
  std::cout << "load_be: 0x" << std::hex << v2 << "\n";

  return 0;
}
