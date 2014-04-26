#include "DisplayValueOnLed.h"

//////////////////////////
// Which pin is the LED on

const int LED_PIN  =  13; 	// Digital pin

////////////////////////////////////
// The on/off time for the LED in mS

const int TICK     = 100;	// milliSeconds delay

int value			= 2;
int newValue		= 0;

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
 * we want the LED (on digital pin 13) to flash twice, each flash will last for 200mS (and off for 200mS) then a delay of 1S
 * before repeating the sequence.
 *
 *
 */

 DisplayValueOnLed dvol(LED_PIN, value, 2, 10);

/////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
	Serial.begin(9600);

	Serial.println("Setup complete");

	displayValues();
	
	showHelp();
}

void loop() {
	bool setOk	=	false;
	
	//////////////////////////
	// Check for commands 
	//////////////////////////
	if ( Serial.available()) {
		char ch = Serial.read();

		if(ch >= '0' && ch <= '9'){             		// is ch a number?
			newValue = (newValue * 10) + (ch - '0');    // yes, accumulate the value
		} else if(ch == 'v'){
			setOk	=	dvol.setValue(newValue);
			checkParamWasSet(setOk);
			newValue	= 0;
			displayValues();
		} else if(ch == 'o') {
			setOk	=	dvol.setLedOnCountInTicks(newValue);
			checkParamWasSet(setOk);
			newValue	= 0;
			displayValues();
		} else if(ch == 'O') {
			setOk	=	dvol.setLedOffCountInTicks(newValue);
			checkParamWasSet(setOk);
			newValue	= 0;
			displayValues();
		} else if(ch == 'd') {
			setOk	=	dvol.setRepeatDelayCountInTicks(newValue);
			checkParamWasSet(setOk);
			newValue	= 0;
			displayValues();
		} else if(ch == '?') {
			newValue	= 0;
			showHelp();
			displayValues();
		}
    }
	
	////////////////////////////////////////////////////////////////////
	// All the hard work is done here in the tick() call
	// and the return value is the current state of the LED
	//
	// If the value to be displayed changes at any time, call
	//
	// 		tick(newValue) or dvol.setValue(newValue)
	//
	// There is no overhead if the same value is passed in continuously
	//
	// Make sure you call the delay with the relevant value somewhere
	// in this method.
	///////////////////////////////////////////////////////////////////
	delay(TICK);

	dvol.tick();	
}

void checkParamWasSet(bool setOk) {
	if(! setOk) {
		Serial.println("Invalid parameter value entered - ignored");
	}
}

void showHelp() {
	Serial.println("Enter a number then a command letter:-");
	Serial.println("v - change the value displayed on the LED");
	Serial.println("o - change the ON tick count for the LED");
	Serial.println("O - change the OFF tick count for the LED");
	Serial.println("d - change the delay tick count between displaying the value on the LED");
	Serial.println("? - show this help and display the current state of the LED object");
}

void displayValues() {
	String me;
	dvol.toString(me);
	Serial.println(me);
}
