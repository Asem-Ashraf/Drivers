#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../../LIB/STD_TYPE.h"

typedef struct{
    u32 sender;
    u32 receiver;
    u32 amount;
} Transaction;

void generateRandomTransaction(Transaction *t);

#endif // TRANSACTION_H
