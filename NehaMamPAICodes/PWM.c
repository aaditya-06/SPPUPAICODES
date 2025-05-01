#include&lt;pic18f458.h&gt;

void main(void)
{

TRISCbits.RC2 = 0; // 00101100 to Select PWM mode; Duty cycle LSB
CCP1CONbits.CCP1M = 0b1100; //CCP1CON&lt;4:5&gt; = &lt;1:1&gt;

TMR2ON = 0;
while(1)
{
PR2 = 74;
CCPR1L = 18;
TMR2ON = 1;
}
}