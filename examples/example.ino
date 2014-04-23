#include "DisplayValueOnLed.h"

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

/********************
 * Which pin to flash
 */
const int outPin = 13; 

DisplayValueOnLed dvol(outPin, 7, 2, 10);

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