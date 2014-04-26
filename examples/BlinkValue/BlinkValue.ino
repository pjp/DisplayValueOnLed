#include "DisplayValueOnLed.h"

//////////////////////////
// Which pin is the LED on

const int LED_PIN  =  13; 	// Digital pin

////////////////////////////////////
// The on/off time for the LED in mS

const int TICK     = 100;	// milliSeconds delay

/***********************************************************************************
 * A tick is the time between calling the tick() method on the class instance. This depends on the caller.
 *
 * Assuming the tick method is to be called called every 100mS, then constructing an object such as :-
 *
 *      DisplayValueOnLed dvol   =   new DisplayValueOnLed(13, 7, 2, 10)
 *
 *
 * means:
 *
 * we want the LED (on digital pin 13) to flash 7 times, each flash will last for 200mS (and off for 200mS) then a delay of 1S
 * before repeating the sequence.
 *
 *
 */

 DisplayValueOnLed dvol(LED_PIN, 7, 2, 10);

/////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
}

void loop() {
	//////////////////////////
	// Do some other work here 
	//////////////////////////
	
	
	/////////////////////////////////////////////////////////
	// All the hard work is done here in the tick() call
	// and the return value is the current state of the LED
	//
	// If the value to be displayed changes at any time, call
	//
	// 		tick(newValue)
	//
	// Make sure you call the delay with the relevant value somewhere
	// in this method.
	/////////////////////////////////////////////////////////
	delay(TICK);

	dvol.tick();	
}