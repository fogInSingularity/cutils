#if defined (__cplusplus)
extern "C" {
#endif // __cplusplus

#include "swap.h"

#include <stdint.h>
#include <stddef.h>
#include <memory.h>
#include <assert.h>

void Swapuint8_ts(void* a, void* b, size_t size) {
    assert(a != NULL);
    assert(b != NULL);

    if (a == b) { return; }

    size_t nFullOps = size >> 3; // колво шагов по 8
    size_t trailer = size & 0b111UL; // оставшиеся 7 байт

    uint8_t* aMove = (uint8_t*)a;
    uint8_t* bMove = (uint8_t*)b;
    for (int64_t i = 0; i < nFullOps; i++) {
        uint64_t temp = 0;
        memcpy(&temp, aMove, sizeof(uint64_t));
               memcpy(aMove, bMove, sizeof(uint64_t));
                      memcpy(bMove, &temp, sizeof(uint64_t));
        aMove += sizeof(uint64_t);
        bMove += sizeof(uint64_t);
    }

    if (trailer & 0b100UL) {
        uint32_t temp = 0;
        memcpy(&temp, aMove, sizeof(uint32_t));
               memcpy(aMove, bMove, sizeof(uint32_t));
                      memcpy(bMove, &temp, sizeof(uint32_t));
        aMove += sizeof(uint32_t);
        bMove += sizeof(uint32_t);
    }
    if (trailer & 0b010UL) {
        uint16_t temp = 0;
        memcpy(&temp, aMove, sizeof(uint16_t));
               memcpy(aMove, bMove, sizeof(uint16_t));
                      memcpy(bMove, &temp, sizeof(uint16_t));
        aMove += sizeof(uint16_t);
        bMove += sizeof(uint16_t);
    }
    if (trailer & 0b001UL) {
        uint8_t temp = 0;
        memcpy(&temp, aMove, sizeof(uint8_t));
               memcpy(aMove, bMove, sizeof(uint8_t));
                      memcpy(bMove, &temp, sizeof(uint8_t));
    }
}

#if defined (__cplusplus)
}
#endif // __cplusplus
