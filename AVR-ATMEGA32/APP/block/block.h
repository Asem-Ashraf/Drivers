#ifndef BLOCK_H
#define BLOCK_H

#include "../../LIB/STD_TYPE.h"

#include "../transaction/transaction.h"

#define NUM_OF_TRANSACTIONS_IN_BLOCK 5

typedef struct{
    u32 nonce;   // random number
    u32 prevHash;// hash of the previous block
    u32 target;  // if a hash is lower than target, it is valid
    Transaction transactions[NUM_OF_TRANSACTIONS_IN_BLOCK]; // transactions in the block
} Block;

u32 hashBlock(Block* block);


#endif // BLOCK_H
