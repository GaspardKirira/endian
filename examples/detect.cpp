#include <endian/endian.hpp>

#include <iostream>

int main()
{
  std::cout << "little_endian: " << (endian::is_little_endian() ? "true" : "false") << "\n";
  std::cout << "big_endian   : " << (endian::is_big_endian() ? "true" : "false") << "\n";
  return 0;
}
