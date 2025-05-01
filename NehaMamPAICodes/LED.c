#include&lt;xc.h&gt;
void Todelay(void);
#define mybit PORTBbits.RB4
void main(void)
{
TRISBbits.TRISB4=0;
while(1)
{
mybit=1;
Todelay();
mybit=0;
Todelay();
}
}
void Todelay (void)
{
T0CON = 0X01;
TMR0H = 0Xff;
TMR0L = 0XEE;
T0CONbits.TMR0ON=1;
while (INTCONbits.TMR0IF = 0);
T0CONbits.TMR0ON = 1;
INTCONbits.TMR0IF = 0;
}