#include "../../LIB/STD_TYPE.h"
#include "transaction.h"

#include "../generate/generate.h"

void generateRandomTransaction(Transaction *t){
    t->sender = rand();
    t->receiver = rand();
    t->amount = rand();
}
