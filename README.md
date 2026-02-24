# endian

Minimal endian utilities for modern C++.

`endian` provides explicit and deterministic tools for handling byte
order.

Header-only. Zero dependencies.

## Download

https://vixcpp.com/registry/pkg/gaspardkirira/endian

## Why endian?

Byte order matters in:

-   Network protocols
-   File formats
-   Cryptography
-   Binary serialization
-   Hashing algorithms
-   Cross-platform systems

This library provides:

-   Endianness detection
-   Byte swapping (16/32/64)
-   Explicit little-endian load/store
-   Explicit big-endian load/store

No hidden behavior. No platform magic.

## Installation

### Using Vix Registry

``` bash
vix add gaspardkirira/endian
vix deps
```

### Manual

``` bash
git clone https://github.com/GaspardKirira/endian.git
```

Add the `include/` directory to your project.

## Quick Examples

### Detect Endianness

``` cpp
#include <endian/endian.hpp>
#include <iostream>

int main()
{
  std::cout << (endian::is_little_endian() ? "little" : "big") << "\n";
}
```

### Byte Swap

``` cpp
#include <endian/endian.hpp>
#include <iostream>

int main()
{
  std::uint32_t v = 0x11223344;
  std::uint32_t swapped = endian::bswap32(v);

  std::cout << std::hex << swapped << "\n";
}
```

Output:
```
    44332211
```
### Store / Load Little Endian

``` cpp
#include <endian/endian.hpp>
#include <iostream>

int main()
{
  std::uint8_t buf[4];

  endian::store_le<std::uint32_t>(buf, 0xA1B2C3D4);

  auto v = endian::load_le<std::uint32_t>(buf);

  std::cout << std::hex << v << "\n";
}
```

### Store / Load Big Endian

``` cpp
#include <endian/endian.hpp>
#include <iostream>

int main()
{
  std::uint8_t buf[4];

  endian::store_be<std::uint32_t>(buf, 0xA1B2C3D4);

  auto v = endian::load_be<std::uint32_t>(buf);

  std::cout << std::hex << v << "\n";
}
```

## API Overview

``` cpp
endian::is_little_endian();
endian::is_big_endian();

endian::bswap16(value);
endian::bswap32(value);
endian::bswap64(value);

endian::load_le<T>(bytes);
endian::load_be<T>(bytes);

endian::store_le<T>(buffer, value);
endian::store_be<T>(buffer, value);
```

Supported types:

-   `std::uint16_t`
-   `std::uint32_t`
-   `std::uint64_t`

## Design Principles

-   Explicit over implicit
-   No hidden host-endian assumptions
-   Deterministic byte layout
-   Minimal surface area
-   Header-only integration

Perfect companion for:

-   `hashing`
-   `hmac`
-   `hex`
-   `secure_random`
-   `uuid`

## Tests

Run:

``` bash
vix build
vix tests
```

Tests verify:

-   Byte swap correctness
-   Load/store roundtrip
-   Deterministic LE/BE layouts
-   Cross-platform correctness

## License

MIT License
Copyright (c) Gaspard Kirira

