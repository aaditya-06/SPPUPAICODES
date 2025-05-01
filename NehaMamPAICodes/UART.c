#include &lt;PIC18F458.h&gt;
void main()
{
unsigned char a[]=&quot;WELCOME&quot;; ///character array to transmit
int i;
TRISB=0;
TRISCbits.RC6=0;
TRISCbits.RC7=1;
SPBRG=0X4D;//to set baud rate
RCSTAbits.SPEN = 1; // Enable USART module
TXSTAbits.TXEN = 1;//receive status and control register

for(i=0;i&lt;=6;i++)
{
while(PIR1bits.TXIF==0); //check whether data is transmitted or not
TXREG=a[i];
PIR1bits.TXIF=0;
}
while(1);
}