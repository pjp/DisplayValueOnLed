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
        int	_pin,
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

	setLedPin(_pin);
	setValue(_value);
	setLedOnCountInTicks(_ledOnCountInTicks);
	setLedOffCountInTicks(_ledOffCountInTicks);
	setRepeatDelayCountInTicks(_repeatDelayCountInTicks);
	
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

///////////////////////////////////////////////////////////////////
// Setters and Getters
///////////////////////////////////////////////////////////////////

/* See header for description */
bool DisplayValueOnLed::setLedPin(int newValue) {
	if(value >= 0) {
		ledPin				   = newValue;
	} else {
		ledPin	=	13;
	}
	
	setupLED();
	
	return ledPin == newValue;
}

/* See header for description */
int DisplayValueOnLed::getLedPin() {
	return ledPin;
}


/* See header for description */
bool DisplayValueOnLed::setValue(int newValue) {
	///////////////
	// Sanity check
	if(newValue >= 0) {
		value  =   newValue;
	} else {
		value	=	1;
	}
	
	return value == newValue;
}

/* See header for description */
int DisplayValueOnLed::getValue() {
	return value;
}


/* See header for description */
bool DisplayValueOnLed::setLedOnCountInTicks(int newValue) {
	if(newValue >= 0) {
		ledOnCountInTicks      =   newValue;
	} else {
		ledOnCountInTicks		=	1;		
	}
	
	return ledOnCountInTicks == newValue;
}

/* See header for description */
int DisplayValueOnLed::getLedOnCountInTicks() {
	return ledOnCountInTicks;
}


/* See header for description */
bool DisplayValueOnLed::setLedOffCountInTicks(int newValue) {
	if(newValue >= 0) {
		ledOffCountInTicks      =   newValue;
	} else {
		ledOffCountInTicks		=	1;		
	}
	
	return ledOffCountInTicks == newValue;
}

/* See header for description */
int DisplayValueOnLed::getLedOffCountInTicks() {
	return ledOffCountInTicks;
}


bool DisplayValueOnLed::setRepeatDelayCountInTicks(int newValue) {
	if(newValue >= 0) {
		interValueDelayInTicks =   newValue;
	} else {
		interValueDelayInTicks	= DEFAULT_REPEAT_DELAY_MULTIPLIER * ledOffCountInTicks;
	}
	
	return interValueDelayInTicks == newValue;
}

/* See header for description */
int DisplayValueOnLed::getRepeatDelayCountInTicks() {
	return interValueDelayInTicks;
}

void DisplayValueOnLed::toString(String &str) {
	str += "LED pin [";
	str += ledPin;
	
	str += "], value [";
	str += value;
	
	str += "], on count [";
	str += ledOnCountInTicks;
	
	str += "], off count [";
	str += ledOffCountInTicks;
	
	str += "], delay count [";
	str += interValueDelayInTicks;
	str += "]";
}

///////////////////////////////////////////////////////////////////
// End of Setters and Getters
///////////////////////////////////////////////////////////////////

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
