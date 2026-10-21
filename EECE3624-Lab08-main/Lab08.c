/*****************************************************************************
 *	    File: Lab08.c
 *  Lab Name: RS232 Communication Server
 *    Author: Dr. Greg Nordstrom
 *   Created: 12/30/17
 *  Mod Date: 3/28/19, 1/17/21
 *  Modified:Allyanna Westcott
 *   ModDate: 10/20/2026
 * 
 * Processor: ATmega128A (on the ReadyAVR board)
 *
 * This program implements a communication server. Normally the server
 * simply echoes what was sent. However, there are two cases where
 * different behavior occurs:
 *    1. Pressing the ESC causes a soft reset (redisplays the title text)
 *    2. Typing the letters 'end' contiguously displays 'Bye' and halts
 *
 *****************************************************************************/

// define CPU speed (7.3728 MHz for the ATmega128A)
#define F_CPU   7372800UL

#define CR          0x0D
#define LF          0x0A
#define ESC         0x1B

#include <avr/io.h>
#include <util/delay.h>
#include "UARTLibrary.h"  // Double quotes for local library.

#define BAUDRATE 9600 // standard values from 1200 to 115200
#define DATABITS    8 // 5-8
#define STOPBITS    1 // 1,2
#define PARITY      0 // 0=none, 1=odd, 2=even

/* Your code here.  */

int main(void)
{
	/* Your code here.  */

    /* See the UARTLibrary.h for available calls.
	 *     	  // initialize the UART
	 *    	  uart_init(BAUDRATE, DATABITS, STOPBITS, PARITY);
	 *
	 *        // transmit a value (0x41) to the comm port
	 *        c = 0x41;
	 *        uart_tx(c);
	 *
	 *        // receive a byte from the comm port
	 *        c = uart_rx();
	 */
	DDRA = 0xFF;  // Set the Direction for all PORTA pints to be outputs
	PORTA = 0xFF; //turn all LEDS off
	
	uart_init(BAUDRATE, DATABITS, STOPBITS, PARITY);
	
	uart_print("\r\n\r\nRS232 Communications Server\r\nStatus: Active\r\nAllyanna Westcott\r\nEECE3624\r\nFall 2026\r\n\r\n");
	
	unsigned int count = 0; //says "BYE" when countdown reaches three
	
	while(1)
	{ 
		/* your loop code here */
		unsigned char typed = uart_rx();
		
		PORTA = 0x00;
		_delay_ms(75);
		PORTA = 0xFF;
		
		if(typed== 'e'){
			count = 1;
		}
		else if((count==1) & (typed=='n')){
			count++;
		}
		else if((count ==2 ) & (typed == 'd')){
			uart_print("d \r\nBye");
			break;
		}
		
		if(typed == 0x0D){
			uart_print("\r\n");
		}
		else if(typed == 0x1B){ //esc
			uart_print("\r\n\r\nRS232 Communications Server\r\nStatus: Active\r\nAllyanna Westcott\r\nEECE3624\r\nFall 2026\r\n\r\n");
		}
		
		
		uart_tx(typed);
		
		
		

		
		
	}
	return 0;
}
