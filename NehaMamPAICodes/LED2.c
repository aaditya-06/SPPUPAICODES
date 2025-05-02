#include &lt;xc.h&gt;
void delay();
void main(void)
{
TRISB=0X00;
while(1)
{

PORTB=0Xff;
delay();
PORTB=0X00;
delay();
}
}
void delay()
{
for(int i=0;i&lt;=1000;i++)
{
}
}