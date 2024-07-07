#ifndef SWAP_H_
#define SWAP_H_

#if defined (__cplusplus)
extern "C" {
#endif // __cplusplus

#include <stddef.h>

void SwapBytes(void* a, void* b, size_t size);

#if defined (__cplusplus)
}
#endif // __cplusplus

#endif // SWAP_H_