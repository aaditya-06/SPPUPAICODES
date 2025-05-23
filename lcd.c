#include<xc.h>
#include<pic18f4550.h>
#define LCD_RS LATAbits.LA1
#define LCD_EN LATAbits.LA0
#define LCDPORT LATB

void lcd_delay(unsigned int time)
{
    unsigned int i,j;
    for(i=0;i<time;i++)
    {
        for(j=0;j<100;j++){}
    }
}

void SendInstruction(unsigned char command)
{
    LCD_RS=0;
    LCDPORT=command;
    LCD_EN=1;
    lcd_delay(10);
    LCD_EN=0;
    lcd_delay(10);
}

void sendData(unsigned char lcddata)
{
    LCD_RS=1;
    LCDPORT=lcddata;
    LCD_EN=1;
    lcd_delay(10);
    LCD_EN=0;
    lcd_delay(10);
}

void InitLCD(void)
{
    ADCON1=0x0F;
    TRISB=0x00;
    TRISAbits.RA0=0;
    TRISAbits.RA1=0;
    SendInstruction(0x38);
    SendInstruction(0x06);
    SendInstruction(0x0C);
    SendInstruction(0x01);
    SendInstruction(0x80);
}

unsigned char *String1="";
unsigned char *String2="";

void main(void)
{
    ADCON1=0x0F;
    TRISB=0x00;
    TRISAbits.RA0=0;
    TRISAbits.RA1=0;
    SendInstruction(0x38);
    SendInstruction(0x06);
    SendInstruction(0x0C);
    SendInstruction(0x01);
    SendInstruction(0x80);
    
    while(*String1)
    {
        sendData(*String1);
        *String1++;
    }
    
    SendInstruction(0xC0);
    
    while(*String2)
    {
        sendData(*String2);
        *String2++;
    }
    while(1);
}