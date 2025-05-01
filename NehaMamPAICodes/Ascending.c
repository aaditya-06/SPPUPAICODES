
PRACTICAL CODE FILE
Neha Dasgude
•
Apr 17

1. Sum of Array.c
C

2. Multiplication & Division of 2 Numbers.c
C

3. Sorting in Ascending Order.c
C

4. Sorting in Descending Order.c
C

5. Memory Transfer Internal to Internal.c
C

6. Memory Exchange.c
C

7. Interfacing of LED.docx
Microsoft Word

8.Interfacing of LCD.docx
Microsoft Word

9. Interface of DC Motor.docx
Microsoft Word

10. Interface of Serial Communication.docx
Microsoft Word

11. Interfacing of Temperature.docx
Microsoft Word

addd1.c
C
Class comments

Add class comment…

#include<pic18f4550.h>
#include <stdio.h>
#include <stdlib.h>

void main(void)
{
   int temp , i , j ;
   int num[] = {10,2,5,1,6} ;
   for(i = 0 ; i < 5 ; i++) // USE ANY OTHER SORTING TECHNIQUE
   {
       for (j = i + 1 ; j < 5 ; j++)
       {
           if(num[i] > num[j])
           {
               temp = num[i] ;
               num[i] = num[j] ;
               num[j] = temp ;
           }
       }
    }
    TRISA = 0 ;
    TRISB = 0 ;
    TRISC = 0 ;
    TRISD = 0 ;
    TRISE = 0 ;
    PORTA = num[0] ;
    PORTB = num[1] ;
    PORTC = num[2] ;
    PORTD = num[3] ;
    PORTE = num[4] ;
}