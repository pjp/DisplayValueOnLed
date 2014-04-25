#include "DisplayValueOnLed.h"
#include "Arduino.h"
	
/* See header for description */
DisplayValueOnLed::DisplayValueOnLed(
		int ledPin,
		int value,
		int ledOnCountInTicks) {
		
	init(ledPin, value, ledOnCountInTicks, ledOnCountInTicks, DEFAULT_REPEAT_DELAY_MULTIPLIER * ledOnCountInTicks);
}

/* See header for description */
DisplayValueOnLed::DisplayValueOnLed(
        int ledPin,
		int value,
		int ledOnCountInTicks,
		int repeatDelayCountInTicks) {
		
	init(ledPin, value, ledOnCountInTicks, ledOnCountInTicks, repeatDelayCountInTicks);
}

/* See header for description */
DisplayValueOnLed::DisplayValueOnLed(
        int ledPin,
		int value,
		int ledOnCountInTicks,
		int ledOffCountInTicks,
		int repeatDelayCountInTicks) {
		
	init(ledPin, value, ledOnCountInTicks, ledOffCountInTicks, repeatDelayCountInTicks);
}

/* See header for description */
void DisplayValueOnLed::init(
        int	pin,
		int _value,
		int _ledOnCountInTicks,
		int _ledOffCountInTicks,
		int _repeatDelayCountInTicks) {

	ledIsOn				= false;
	ledOnCount           =   0;
	ledOffCount          =   0;
	valueCount           =   0;
	repeatDelayCount    =   0;

	state              	=   START;


	////////////////
	// Sanity checks
	setValue(_value);

	if(pin >= 0) {
		ledPin				   = pin;
	} else {
		ledPin	=	13;
	}
	
	if(_ledOnCountInTicks >= 0) {
		ledOnCountInTicks      =   _ledOnCountInTicks;
	} else {
		ledOnCountInTicks		=	1;		
	}
	
	if(_ledOffCountInTicks >= 0) {
		ledOffCountInTicks     =   _ledOffCountInTicks;
	} else {
		ledOffCountInTicks		= 1;
	}
	
	if(_repeatDelayCountInTicks >= 0) {
		interValueDelayInTicks =   _repeatDelayCountInTicks;
	} else {
		interValueDelayInTicks	= DEFAULT_REPEAT_DELAY_MULTIPLIER * ledOffCountInTicks;
	}
	
	setupLED();
}

 /* See header for description */
 bool DisplayValueOnLed::tick() {
	processTicks();

	return ledIsOn;
}

/* See header for description */
bool DisplayValueOnLed::tick(int newValue) {
	if(newValue != value) {
		setValue(newValue);
	}
	
	processTicks();

	return ledIsOn;
}

/* See header for description */
void DisplayValueOnLed::setValue(int newValue) {
	///////////////
	// Sanity check
	if(newValue >= 0) {
		value  =   newValue;
	} else {
		value	=	1;
	}
}

/* See header for description */
void DisplayValueOnLed::processTicks() {

	switch(state) {
		case START:
			// Reset counters
			ledOnCount          =   0;
			ledOffCount         =   0;
			valueCount          =   0;
			repeatDelayCount    =   0;

			if(value > 0 && ledOnCountInTicks > 0) {
				switchOnLed();
				state = LED_ON;
			}

			break;
		case LED_ON:
			ledOnCount++;
			if(ledOnCount >= ledOnCountInTicks) {
				switchOffLed();
				ledOnCount  =   0;
				state   =   LED_OFF;
			}

			break;
		case LED_OFF:
			ledOffCount++;
			if(ledOffCount >= ledOffCountInTicks) {
				ledOffCount =   0;

				state   =   DISPLAYED_VALUE_CHECK;
			}

			break;
		case DISPLAYED_VALUE_CHECK:
			valueCount++;
			if(valueCount < value) {
				switchOnLed();
				state               =   LED_ON;
			} else {
				valueCount          =   0;
				state               =   INTER_VALUE_DELAY;
			}

			break;
		case INTER_VALUE_DELAY:
			repeatDelayCount++;
			if(repeatDelayCount >= interValueDelayInTicks) {
				repeatDelayCount =   0;
				state   = START;
			}

			break;
	}
}

/* See header for description */
void DisplayValueOnLed::setupLED() {
	pinMode(ledPin, OUTPUT);
}

/* See header for description */
void DisplayValueOnLed::switchOnLed() {
	if(! ledIsOn) {
		digitalWrite(ledPin, HIGH);
		ledIsOn	=	true;
	}
}

/* See header for description */
void DisplayValueOnLed::switchOffLed() {
	if(ledIsOn) {
		digitalWrite(ledPin, LOW);
		ledIsOn	=	false;
	}
}
