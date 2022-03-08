bix is yet another ordinary binhex

  The seven bit ASCII hexidecimal encoding of a binary octet
  sequence replaces each four bit nibble with a (seven bit)
  ASCII octet from the set of (0-9) and (A-F).  The binary
  content payload size is doubled in this encoding.

Implementation

  This package defines a pair of coding functions to perform
  that coding.

Notes

  HEX is a seven bit ASCII encoding that doubles the size of
  the eight bit payload binary band.  Base64 is the usual
  alternative (to Base16).

See also

  https://github.com/syntelos/c-endian-bint
  https://github.com/syntelos/lang

Configuration

  Clone with submodule.

    git clone --recurse-submodules <github:syntelos/c-lang-bix>

  Build using "make" (clang SUSv3 POSIX.1-2001).
