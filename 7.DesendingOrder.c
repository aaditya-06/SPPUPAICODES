#include <xc.h>

#define SIZE 5  // Number of elements to sort

void main(void) {
    unsigned char arr[SIZE] = {5, 2, 9, 1, 6};
    unsigned char temp;
    unsigned char i, j;
    
    TRISD = 0;   // Set PORTD as output (optional, for displaying)
    LATD = 0;    // Clear PORTD

    // Bubble Sort in Descending Order
    for(i = 0; i < SIZE - 1; i++) {
        for(j = 0; j < SIZE - i - 1; j++) {
            if(arr[j] < arr[j+1]) {
                // Swap elements
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    
    // Example: Display first sorted element on PORTD
    PORTD = arr[0]; // Just output the largest element
    while(1);       // Infinite loop
}
