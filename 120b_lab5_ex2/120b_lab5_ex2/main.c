/*
 * 120b_lab5_ex2.c
 *
 * Created: 10/18/2019 11:52:48 AM
 * Author : Matthew L
 */ 

#include <avr/io.h>

enum States{init, inc, dec, zero, wait, wait2} state;

unsigned char button0;
unsigned char button1;

unsigned char tempC;


void button_Press(){
	button0 = ~PINA & 0x01;
	button1 = ~PINA & 0x02;

	switch(state){ // Transitions
		case init:
			if(!button0 && !button1){
				state = init;
			}
			else if(button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = zero;
			}
			break;
			
		case inc:
			if(button0 && button1){
				state = zero;
			}
			else{
				state = wait2;
			}
			break;
			
		case dec:
			if(button0 && button1){
				state = zero;
			}
			else{
				state = wait2;
			}
			break;
			
		case zero:
			if(!button0 && !button1){
				state = init;
			}
			else if (button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = zero;
			}
				break;
				
		case wait:
			if(button0 && button1){
				state = zero;
			}
			else if(button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else{
				state = wait;
			}
			break;
		case wait2:
			if(!button0 && !button1){
				state = wait;
			}
			else if(button0 && button1){
				state = zero;
			}
			else{
				state = wait2;
			}
			break;
	}
	
	switch(state){ 
		case init:
			break;
			
		case inc:
			if(tempC < 9){
				tempC = tempC + 1;
			}
			break;
			
		case dec:
			if(tempC > 0){
				tempC = tempC - 1;
			}
			break;
			
		case zero:
			tempC = 0;
			break;
		
		case wait:
			break;
			
		case wait2:
			break;
	}
}


int main(void)
{	
	DDRA = 0x00; PORTA = 0xFF; 
	DDRC = 0xFF; PORTC = 0x00; 
	// initialize to 0s

	state = init;
	tempC = 0x07;
    /* Replace with your application code */
    while (1) 
    {
		button_Press();
		PORTC = tempC;
    }
}

