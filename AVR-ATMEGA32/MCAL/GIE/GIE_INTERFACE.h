#ifndef GIE_INTERFACE_H
#define GIE_INTERFACE_H

#define GIE_Enable() asm("SEI")

#define GIE_Disable() asm("CLI")

#endif // !GIE_INTERFACE_H
