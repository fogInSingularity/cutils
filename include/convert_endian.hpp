#ifndef CONVERT_ENDIAN_HPP_
#define CONVERT_ENDIAN_HPP_

#include <cstdint>

uint64_t ConvertOrder(uint64_t num);
uint32_t ConvertOrder(uint32_t num);
uint16_t ConvertOrder(uint16_t num);
uint8_t  ConvertOrder(uint8_t  num);

#endif // CONVERT_ENDIAN_HPP_