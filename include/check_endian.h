#ifndef CHECK_ENDIAN_H_
#define CHECK_ENDIAN_H_

#if defined (__cplusplus)
extern "C" {
#endif // __cplusplus

typedef enum EndianOrder {
    kUnknownOrder = 0,
    kBigEndian    = 1,
    kLittleEndian = 2,
} EndianOrder;

EndianOrder CheckEndianOrder();

static const char* kUnknownOrderStr = "unknown order";
static const char* kBigEndianStr    = "big endian";
static const char* kLittleEndianStr = "little endian";

const char* CheckEndianOrderStr();

#if defined (__cplusplus)
}
#endif // __cplusplus

#endif // CHECK_ENDIAN_H_