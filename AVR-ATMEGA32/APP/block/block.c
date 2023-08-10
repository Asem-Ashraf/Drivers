#include "../../LIB/STD_TYPE.h"

#include "block.h"


// FNV-1a 32-bit prime
#define FNV_PRIME 0x01000193 

u32 fnv1a_32_hash(const char *data, u32 len) {

    u32 hval = 0x811C9DC5; // FNV offset basis

    for(u32 i = 0; i < len; i++) {

        // XOR next byte into lower 8 bits
        hval ^= (u32)data[i];

        // Multiply by prime
        hval *= FNV_PRIME;
    }

    return hval;
}


u32 hashBlock(Block* block) {
    return fnv1a_32_hash((const char *)block, sizeof(Block));
}
