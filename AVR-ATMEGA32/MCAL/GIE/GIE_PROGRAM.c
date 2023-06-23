void GIE_Enable(){
    asm("SEI"); // Enable Global Interrupt Instruction
}
void GIE_Disable(){
    asm("CLI"); // Disable Global Interrupt Instruction
}
