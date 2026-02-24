#include <endian/endian.hpp>

#include <cstdlib>
#include <iostream>

static void expect_true(bool v, const char *msg)
{
  if (!v)
  {
    std::cerr << "FAIL: " << msg << "\n";
    std::exit(1);
  }
}

int main()
{
  // Basic sanity: one of them must be true
  expect_true(endian::is_little_endian() || endian::is_big_endian(), "endianness check");

  // bswap
  expect_true(endian::bswap16(0x1122) == 0x2211, "bswap16");
  expect_true(endian::bswap32(0x11223344u) == 0x44332211u, "bswap32");
  expect_true(endian::bswap64(0x0102030405060708ull) == 0x0807060504030201ull, "bswap64");

  // store/load LE
  {
    std::uint8_t buf[8] = {};
    endian::store_le<std::uint32_t>(buf, 0x11223344u);
    const auto v = endian::load_le<std::uint32_t>(buf);
    expect_true(v == 0x11223344u, "load/store le u32");
  }

  // store/load BE
  {
    std::uint8_t buf[8] = {};
    endian::store_be<std::uint32_t>(buf, 0x11223344u);
    const auto v = endian::load_be<std::uint32_t>(buf);
    expect_true(v == 0x11223344u, "load/store be u32");
  }

  // Cross-check bytes layout for known value (independent of host)
  {
    std::uint8_t le[4] = {};
    std::uint8_t be[4] = {};

    endian::store_le<std::uint32_t>(le, 0xA1B2C3D4u);
    endian::store_be<std::uint32_t>(be, 0xA1B2C3D4u);

    expect_true(le[0] == 0xD4 && le[1] == 0xC3 && le[2] == 0xB2 && le[3] == 0xA1, "le bytes");
    expect_true(be[0] == 0xA1 && be[1] == 0xB2 && be[2] == 0xC3 && be[3] == 0xD4, "be bytes");
  }

  std::cout << "ok\n";
  return 0;
}
