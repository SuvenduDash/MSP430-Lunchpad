/*
 * 16/01/18
 * MSP430 Moore Finite State Machine
 *
 * The purpose of this program is to build a simple
 * finite state machine with 4 states.  The input value
 * is updated from the user button isr and takes on a
 * value from 0 to 3.  Each state has a different flash
 * routine.  See fsm.c/.h for state defintions / functions.
 *
 *
 */

//includes
#include <msp430g2553.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "main.h"
#include "fsm.h"

//prototypes

void TimeDelay_Decrement(void);
void GPIO_init(void);
void TimerA_init(void);
void Interrupt_init(void);

void WasteCPU(void);


//global variables
static volatile int TimeDelay;


//main program
void main(void)
{
	//disable the watchdog timer
	WDTCTL = WDTPW + WDTHOLD;
	
	TimerA_init();
	GPIO_init();
	Interrupt_init();

	LedRed_Clear();
	LedGreen_Clear();

	//should never return
	FSM_Run();

}


////////////////////////////////////////
void delay_ms(volatile int ticks)
{
	TimeDelay = ticks;

	//TimeDelay is static and gets decremented
	//in the TimerA ISR
	while (TimeDelay !=0){};
}


/////////////////////////////////////////
//Function called from the TimerA ISR
void TimeDelay_Decrement(void)
{
	if (TimeDelay != 0x00)
	{
		TimeDelay--;
	}

}

//////////////////////////////////////
//Note: SPIB conflicts with P1.6, so the green led does not work
void GPIO_init(void)
{
	//setup bit 0 and 6 as output
	P1DIR |= BIT0;
	P1DIR |= BIT6;

	P1OUT &=~ BIT0;		//turn off
	P1OUT &=~ BIT6;		//turn off

	//set up the user button bit 3
	//as input with pull up enabled
	P1DIR &=~ BIT3;		//input
	P1REN |= BIT3;		//enable pullup/down
	P1OUT |= BIT3;		//resistor set to pull up

}

/////////////////////////////////////////
//Sets up the timer And the frequency
//of the clock, since the rate of overflow
//is connected to this

void TimerA_init(void)
{
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;

	//Set up Timer A register TACTL
	TACTL = 0x0000;		//start from all all clear
	TACTL |= BIT9;		//use SMCLK as the source
	TACTL |= BIT7;		//use prescaler 8
	TACTL |= BIT6;
	TACTL |= BIT4;		//count up to TACCR0(set below)
	TACTL |= BIT1;		//enable the interrupt
	TACTL &=~ BIT0;		//clear all pending interrupts

	//set the countup value.  for 1ms delay,
	//the countup value depends on the clock freq.

	//1 mhz or 16
	TACCR0 = 2000;		//use 2000 for 16 mhz
	//TACCR0 = 125;		//use 125 for  1 mhz
	//	TACCR0 = 1000;		//use 1000 for 8 mhz

	//TACCTL0 - compare capture control register.
	//this has to be set up along with the timer interrupt
	//bit 4 enables the interrupts for this register
	//also called CCIE

	TACCTL0 = CCIE;		//compare, capture interrupt enable

}

///////////////////////////////////////////
void Interrupt_init(void)
{
	//enable all the interrupts
	__bis_SR_register(GIE);

	P1IE |= BIT3;		//enable button interrupt
	P1IFG &=~ BIT3;		//clear the flag

}


void LedRed_Toggle(void)
{
	P1OUT ^= BIT0;
}

void LedRed_Set(void)
{
	P1OUT |= BIT0;
}

void LedRed_Clear(void)
{
	P1OUT &=~ BIT0;
}

void LedGreen_Toggle(void)
{
	P1OUT ^= BIT6;
}

void LedGreen_Set(void)
{
	P1OUT |= BIT6;
}

void LedGreen_Clear(void)
{
	P1OUT &=~ BIT6;
}






//////////////////////////////////////
//TimerA ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	//clear the timer interrupt
	TACTL &=~ BIT0;

	TimeDelay_Decrement();
}


/////////////////////////////////////
//P1 ISR for the user button
//Update input value to the fsm
//and send to the fsm, takes on
//values from 0 to 3
//
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
	static uint8_t fsmValue = 0;
	WasteCPU();

	//still pressed...
	if(!(P1IN & BIT3))
	{
		if (fsmValue < 3)
			fsmValue++;
		else
			fsmValue = 0;

		FSM_SetInputValue(fsmValue);
	}

	//clear the interrupt flag - button
	P1IFG &=~ BIT3;
}


void WasteCPU(void)
{
	volatile int t = 10000;
	while(t >0)
		t--;
}




