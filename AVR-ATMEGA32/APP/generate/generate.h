#ifndef GENERATORS_H_
#define GENERATORS_H_

#include "../../LIB/STD_TYPE.h"


// uses ADC to generate random 32-bit number
// Parameters: none
// requires ADC to be initialized and channel to be selected
// Returns: 32-bit random number
u32 rand(void);

#endif
