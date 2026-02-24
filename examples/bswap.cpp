#include <endian/endian.hpp>

#include <cstdint>
#include <iostream>

int main()
{
  const std::uint32_t v = 0x11223344u;
  const std::uint32_t s = endian::bswap32(v);

  std::cout << "v    : 0x" << std::hex << v << "\n";
  std::cout << "swap : 0x" << std::hex << s << "\n";
  return 0;
}
