#include <xc.h>

int subtract(int a, int b);

void main(void) {
    int num1 = 15;
    int num2 = 7;
    int result;

    result = subtract(num1, num2);

    while (1) {
        NOP(); // No Operation - keeps the MCU running
    }
}

int subtract(int a, int b) {
    return a - b;
}