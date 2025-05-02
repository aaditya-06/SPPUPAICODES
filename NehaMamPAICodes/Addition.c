#include <stdio.h>
#include <stdio.h>
#include <pl8f4550.h>

void main(void)
    {
	    int sum;
	    sum=0;       //initialze sum as zero
	    
	    sum=0X0A + 0X02;
	     
	     TRISD =0;       //initialize Fort D as output
	     PORTD= sum;     //from sum to PORT_D
	     
	 }