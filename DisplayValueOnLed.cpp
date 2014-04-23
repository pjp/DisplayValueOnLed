#include "DisplayValueOnLed.h"

/**
 * A tick is the time between calling the tick() method. This depends on the caller.
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
 * be in, see the tick() and tick(newValue) methods.
 *
 *      boolean ledOn   =   false;
 *
 *      ledOn           =   dvol.tick();
 *      ledOn           =   dvol.tick();
 *      ledOn           =   dvol.tick();
 *      ledOn           =   dvol.tick();
 *
 * @param value                            // The initial value to display as LED flashes, this can be changed later (see setValue(newValue)  and tick(newValue) )
 * @param ledOnCountInTicks                // How many ticks for the LED to remain on, off time is the same
 * @param repeatDelayCountInTicks          // How many ticks between displaying the value, must be > ledOnCountInTicks
 */
DisplayValueOnLed::DisplayValueOnLed(
		int value,
		int ledOnCountInTicks,
		int repeatDelayCountInTicks) {
		
	init(value, ledOnCountInTicks, ledOnCountInTicks, repeatDelayCountInTicks);
}

 /**
  * See comments above, this allows the off time to be specified as well.
  *
  * @param value                            // The value to display as LED flashes, this can be changed later
  * @param ledOnCountInTicks                // How many ticks for the LED to remain on
  * @param ledOffCountInTicks               // How many ticks for the LED to remain off
  * @param repeatDelayCountInTicks               // How many ticks between displaying the value, must be > ledOffCountInTicks
  */
DisplayValueOnLed::DisplayValueOnLed(
		int value,
		int ledOnCountInTicks,
		int ledOffCountInTicks,
		int repeatDelayCountInTicks) {
		
	init(value, ledOnCountInTicks, ledOffCountInTicks, repeatDelayCountInTicks);
}

void DisplayValueOnLed::init(
		int _value,
		int _ledOnCountInTicks,
		int _ledOffCountInTicks,
		int _repeatDelayCountInTicks) {

	ledOnCount           =   0;
	ledOffCount          =   0;
	valueCount           =   0;
	repeatDelayCount    =   0;

	state                             =   START;
	ledShouldBeOn                   =   false;

	ledSwitchedOnCount                 =   0;


	setValue(_value);

	////////////////
	// Sanity checks
	/*
	if(ledOnCountInTicks < 0) {
		throw new IllegalArgumentException("ledOnCountInTicks cannot be negative");
	}

	if(ledOffCountInTicks < 1) {
		throw new IllegalArgumentException("ledOffCountInTicks cannot be < 1");
	}

	if(repeatDelayCountInTicks <= ledOffCountInTicks) {
		throw new IllegalArgumentException("repeatDelayCountInTicks cannot be <= ledOffCountInTicks");
	}
	*/
	
	ledOnCountInTicks      =   _ledOnCountInTicks;
	ledOffCountInTicks     =   _ledOffCountInTicks;
	interValueDelayInTicks =   _repeatDelayCountInTicks;
}

/**
 * Call this at a regular frequency.
 
 * @return true if the LED should be switch on; else false for it to be switched off
 */
 bool DisplayValueOnLed::tick() {
	processTicks();

	return ledShouldBeOn;
}

/**
 * Call this at a regular frequency.
 
 * @param newValue The new value to display, but ignored if the same as the current value
 * 
 * @return true if the LED should be switch on; else false for it to be switched off
 */
 bool DisplayValueOnLed::tick(int newValue) {
	if(newValue != value) {
		setValue(newValue);
	}
	
	processTicks();

	return ledShouldBeOn;
}

/**
 * Just set a new value to display.
 *
 * @param newValue The new value to display
 */
void DisplayValueOnLed::setValue(int newValue) {
	////////////////
	// Sanity checks
	/*
	if(value < 0) {
		throw new IllegalArgumentException("value cannot be negative");
	}
	*/
	value  =   newValue;
}

/**
 * Simple state machine
 */
void DisplayValueOnLed::processTicks() {

	switch(state) {
		case START:
			// Reset counters
			ledOnCount          =   0;
			ledOffCount         =   0;
			valueCount          =   0;
			repeatDelayCount    =   0;
			ledSwitchedOnCount  =   0;

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

void DisplayValueOnLed::switchOnLed() {
	ledShouldBeOn =   true;
	ledSwitchedOnCount++;
}
void DisplayValueOnLed::switchOffLed() {
	ledShouldBeOn =   false;
}

