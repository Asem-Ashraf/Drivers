#include "../LIB/STD_TYPE.h"

void floatToString(f64 num, char* str, int precision) {
    int integerPart = (int)num;
    f64 decimalPart = num - (f64)integerPart;
    int   i = 0;

    // Convert integer part to string
    if (integerPart == 0) {
        str[i++] = '0';
    }
    else {
        int temp = integerPart;
        while (temp != 0) {
            int digit = temp % 10;
            str[i++] = digit + '0';
            temp /= 10;
        }
        int len = i;
        for (int j = 0; j < len / 2; j++) {
            char temp = str[j];
            str[j] = str[len - j - 1];
            str[len - j - 1] = temp;
        }
    }

    // Add decimal point and convert decimal part to string
    if (precision != 0) {
        str[i++] = '.';
        for (int j = 0; j < precision; j++) {
            decimalPart *= 10;
            int digit = (int)decimalPart;
            str[i++] = digit + '0';
            decimalPart -= (f64)digit;
        }
    }

    // Add null terminator
    str[i] = '\0';
}

void integerToString(u32 num, char* str) {
    u32 i = 0;
    if (num == 0) {
        str[i++] = '0';
    }
    else {
        u32 temp = num;
        while (temp != 0) {
            u32 digit = temp % 10;
            str[i++] = digit + '0';
            temp /= 10;
        }
        u32 len = i;
        for (u32 j = 0; j < len / 2; j++) {
            char temp = str[j];
            str[j] = str[len - j - 1];
            str[len - j - 1] = temp;
        }
    }
    str[i] = '\0';
}
