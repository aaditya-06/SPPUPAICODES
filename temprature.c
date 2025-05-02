
#include <xc.h>
#include<pic18f4550.h>
#include<stdio.h>

#define LCD_EN LATAbits.LA1
#define LCD_RS LATAbits.LA0
#define LCDPORT LATB

unsigned char str[16];

void delay(unsigned int time)
{
    unsigned int i,j;
    for(i=0;i<time;i++)
        for(j=0;j<100;j++);
}

void SendInstruction(unsigned char command)
{
    LCD_RS=0;
    LCDPORT=command;
    LCD_EN=1;
    delay(10);
    LCD_EN=0;
    delay(10);
}

void sendData(unsigned char lcddata)
{
    LCD_RS=1;
    LCDPORT=lcddata;
    LCD_EN=1;
    delay(10);
    LCD_EN=0;
    delay(10);
    
}

void display(unsigned int row,unsigned int pos,unsigned char *ch)
{
    if(row==1)
        SendInstruction((0x80) | (pos-1));
    else
        SendInstruction((0xC0) | (pos-1));
    while(*ch)
    {
        sendData(*ch);
        *ch++;
    }
}

void InitLCD(void)
{
    ADCON1=0x0F;
    TRISAbits.RA0=0;
    TRISAbits.RA1=0;
    LATAbits.LA0=0x00;
    
    SendInstruction(0x38);
    SendInstruction(0x06);
    SendInstruction(0x0C);
    SendInstruction(0x01);
    SendInstruction(0x80);
}

void ADCInit(void)
{
    TRISEbits.RE2=1;
    
    ADCON1=0b00000111;
    ADCON2=0b10101110;
}

unsigned short read_temp(void)
{
    ADCON1=0b00011101;
    GODONE=1;
    
    while(GO_DONE==1)
    return ADRES;
}

void main(void) 
{
    unsigned int temp;
    InitLCD();
    ADCInit();
    display(1,1,"Temperature");
    while(1)
    {
        temp=read_temp();
        temp=((temp*500)/1023);
        sprintf(str,"%d 'C",temp);
        display(2,1,str);
        delay(9000);
    }
            
    
    return;
}
