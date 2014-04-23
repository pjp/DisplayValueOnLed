#include "DisplayValueOnLed.h"

/***********************************************************************************
 * A tick is the time between calling the tick() method on the class instance. This depends on the caller.
 *
 * Assuming the tick method is to be called called every 100mS, then constructing an object such as :-
 *
 *      DisplayValueOnLed dvol   =   new DisplayValueOnLed(7, 2, 10)
 *
 *
 * means:
 *
 * we want the LED to flash 7 times, each flash will last for 200mS (and off for 200mS) then a delay of 1S
 * before repeating the sequence.
 *
 * Note that this class DOES NOT actually manipulate the LED, it simply indicates the state that the LED should
 * be in, see loop method below.
 *
 */

/********************
 * Which pin to flash
 */
const int outPin = 13; 

DisplayValueOnLed dvol(outPin, 7, 2, 10);

/**************************
 * Initial state of the led
 */
boolean ledIsOn	= false;

/////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
	Serial.begin(9600);

	Serial.println("Finished setup");
}

void loop() {
	delay(100);

	bool ledShouldBeOn  =  dvol.tick();	// All the hard work is done here

	Serial.println(ledShouldBeOn);
  
}