#ifndef PNG_HEADER_TYPES_HPP_
#define PNG_HEADER_TYPES_HPP_

#include <cstdint>

// revers order
static const uint32_t header_IHDR = 0x52'44'48'49; 
static const uint32_t header_PLTE = 0x45'54'4c'50;
static const uint32_t header_IDAT = 0x54'41'44'49;
static const uint32_t header_IEND = 0x44'4e'45'49;

#endif // PNG_HEADER_TYPES_HPP_