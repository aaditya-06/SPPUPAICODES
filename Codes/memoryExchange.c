/*
 * File:   memoryExchange.c
 * Author: shri
 *
 * Created on 09 May 2023, 11:10
 */


#include <xc.h>
void main(void) {

 int temp , i;
 int array1[] = {0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18};
 int array2[] = {0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58};

 for(i=0; i <= 7; i++)
 {
 temp = array1[i];
 array1[i] = array2[i];
 array2[i] = temp;

 }
 return;
}
