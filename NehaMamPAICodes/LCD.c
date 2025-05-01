#include &lt;PIC18F458.h&gt;
#define ldata PORTB //define name ldata to PORTB
#define rs PORTCbits.RC1 //definne name rs(egister select) for RC0 pin of
PORTC
#define en PORTCbits.RC0 //definne name en(enable) for RC1 pin of
PORTC
void delay();
void lcdcmd(unsigned char);
void lcdval(unsigned char);
void main()
{
unsigned char xc;
TRISB=0; //make PORTB as output
TRISC=0; //make PORTC as output
lcdcmd(0x38); //command to initialise LCD.
lcdcmd(0x0E); //command to make Display on cursor blinking
lcdcmd(0x01); //command to clear display screen
lcdcmd(0x06); //command to increment cursor
lcdcmd(0xC0); //command to set cursor at 1st line 6th position
lcdval(&#39;H&#39;);
lcdval(&#39;E&#39;);
lcdval(&#39;L&#39;);
lcdval(&#39;L&#39;);
while(1);
}
void lcdcmd(unsigned char y)
{
rs=0;
ldata=y;
en=1;
delay();
en=0;
delay();
}
// lcdval fuction used to select DATA REGISTER of LCD by making,
// rs=1 and en=1 to 0 edge AND sends 8 bit command to PORTB
void lcdval(unsigned char y)
{
rs=1;
ldata=y;

en=1;
delay();
en=0;
delay();
}
void delay()
{
for(int i=0;i&lt;=2000;i++)
{}
}