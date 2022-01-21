/*
 * File:   SwiGO_16A_EDS001.c
 * Author: SYS1
 *
 * Created on 29 April, 2021, 3:38 PM
 */

//15_30_45_60_Min_With_Delay
#include "mcc_generated_files/mcc.h"
#include<xc.h>
void delay_blink(int , int );
//#define _XTAL_FREQ 16000000  	// change to 16000000
//#pragma config WDTE=OFF         //Watchdog Timer
//#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
//#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
//#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
//#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
//#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void main(void)
 {	TRISB=0xFF; 	// input port
	TRISC=0x00; 	//output port
	ANSELB=0x00;
	PORTC=0x00; 	//initial LED position
	PORTB=0x00; 	//sensing 
   	__delay_ms(100);
    
    int eprom_rem_time=0; //time remaining.
    int eprom_select_buttom=0; //time delay currently selected.
    eprom_rem_time = DATAEE_ReadByte(0);
    eprom_select_buttom = DATAEE_ReadByte(1);
    
   while (1)
   {
        
       if(eprom_rem_time==0)
       {
        if(RB4==0b1){__delay_ms(100);if(RB4==0b0) {RC0=1;RC4=1;DATAEE_WriteByte( 1, 0);delay_blink(1,0);RC0=0;RC4=0;__delay_ms(2000);}}   //sw1 change 1 based no of min
	 
     	if(RB3==0b1){__delay_ms(100);if(RB3==0b0) {RC1=1;RC4=1;DATAEE_WriteByte( 1, 1);delay_blink(2,1);RC1=0;RC4=0;__delay_ms(2000);}}   //sw2 change delay(2) based no of min
	 
     	if(RB2==0b1){__delay_ms(100);if(RB2==0b0){RC2=1;RC4=1;DATAEE_WriteByte( 1, 2);delay_blink(3,2);RC2=0;RC4=0;__delay_ms(2000);}}    //sw3 change delay(3) based no of min
	 
     	if(RB1==0b1){__delay_ms(100);if(RB1==0b0){RC3=1;RC4=1;DATAEE_WriteByte( 1, 3);delay_blink(4,3);RC3=0;RC4=0;__delay_ms(2000);}}    //sw4 change delay(4) based no of min
       }
       
       if(eprom_rem_time!=0)
       {
       __delay_ms(3000); //used for 3 sec delay   
       RC4=1;
       delay_blink(eprom_rem_time,eprom_select_buttom);
       RC0=0;RC1=0;RC2=0;RC3=0;RC4=0;
       }
   }
}
 
 
void delay_blink(int i, int prt)
         {
        uint8_t r_temp = i; 
	    int temp=0;
	    while(temp<i)
	       {
		int min=0;
			while(min<=1)
					{ 
					__delay_ms(500);min++;
					if(prt==0){RC0=~RC0;}
					if(prt==1){RC1=~RC1;}
					if(prt==2){RC2=~RC2;}
					if(prt==3){RC3=~RC3;}
					}
		min=0;
	      	temp++;
            r_temp = i-temp;
            DATAEE_WriteByte( 0, r_temp);
		}
	temp=0;
	i=0;
	}
