#ifndef DisplayValueOnLed_h
#define DisplayValueOnLed_h

#include "Arduino.h"

#define DEFAULT_REPEAT_DELAY_MULTIPLIER	4

/**
 * An Arduino library class that allows a LED to display an integer value by flashing a LED a proportional number of times.
 *
 * The on, off and repeat counts/time are configurable.
 *
 * I needed a way to indicate the current input battery voltage on a tracked vehicle project, couldn't find anything that used
 * a single pin so I wrote this library class (my first, I'm a Java man).
 *
 * Written by Paul Pearce - April 2014
 
 */
class DisplayValueOnLed {
	public:

	/***************************************
	 * Current internal state of the object.
	 */
	enum State {START, LED_ON, LED_OFF, DISPLAYED_VALUE_CHECK, INTER_VALUE_DELAY};
	
	/************************************************************************************
	 * A tick is the time between calling the tick() method. This depends on the caller.
	 *
	 * Assuming the tick method is to be called called every 100mS, then constructing an object such as :-
	 *
	 *      DisplayValueOnLed dvol   =   new DisplayValueOnLed(13, 7, 2)
	 *
	 *
	 * means:
	 *
	 * we want the LED (on digital pin 13) to flash 7 times, each flash will last for 200mS (and off for 200mS, then a delay of 800mS
	 * before repeating the sequence).
	 
	  * Use defaults for the off count (same as on count) and repeat delay ( 4 * on count) .
	  *
	  * @param ledPin							// THe digital pin the LED is on
	  * @param value                            // The value to display as LED flashes, this can be changed later
	  * @param ledOnCountInTicks                // How many ticks for the LED to remain on (and off)
	  */
	DisplayValueOnLed(
			int ledPin,
			int value,
			int ledOnCountInTicks);

	/************************************************************************************
	 * A tick is the time between calling the tick() method. This depends on the caller.
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
	 * Use defaults for the off count (same as on count)
	 *
	 * @param ledPin							// The digital pin the led is on
	 * @param value                            // The initial value to display as LED flashes, this can be changed later (see setValue(newValue)  and tick(newValue) )
	 * @param ledOnCountInTicks                // How many ticks for the LED to remain on, off time is the same
	 * @param repeatDelayCountInTicks          // How many ticks between displaying the value, must be > ledOnCountInTicks
	 */
	DisplayValueOnLed(
			int ledPin,
			int value,
			int ledOnCountInTicks,
			int repeatDelayCountInTicks);

	/************************************************************************************
	 * A tick is the time between calling the tick() method. This depends on the caller.
	 *
	 * Assuming the tick method is to be called called every 100mS, then constructing an object such as :-
	 *
	 *      DisplayValueOnLed dvol   =   new DisplayValueOnLed(13, 7, 2, 3, 10)
	 *
	 *
	 * means:
	 *
	 * we want the LED (on digital pin 13) to flash 7 times, each flash will last for 200mS, off for 300mS then a delay of 1S
	 * before repeating the sequence.
	 *
	 *
	 * @param ledPin							// The digital pin the led is on 
	 * @param value                            // The value to display as LED flashes, this can be changed later
	 * @param ledOnCountInTicks                // How many ticks for the LED to remain on
	 * @param ledOffCountInTicks               // How many ticks for the LED to remain off
	 * @param repeatDelayCountInTicks          // How many ticks between displaying the value, must be > ledOffCountInTicks
	 */
	DisplayValueOnLed(
			int	ledPin,
			int value,
			int ledOnCountInTicks,
			int ledOffCountInTicks,
			int repeatDelayCountInTicks);
			
	
	/***********************************************************
	 * Call this at a regular frequency. Also see tick(newValue)
	 *
 	 * @return true if the LED should be switch on; else false for it to be switched off
	 */
	bool tick();

	/****************************************************************************
	 * Call this at a regular frequency. This is logically the same as calling :-
	 *
	 * setValue(newValue); tick();
	 *
	 * @param newValue The new value to display, but ignored if the same as the current value
	 
 	 * @return true if the LED should be switch on; else false for it to be switched off
	 */
	bool tick(int newValue);

	/************************************************
	 * Set a value to display.
	 *
	 * @param newValue The new value to display
	 *
	 * @return true if the new value was accepted; false if a default was applied
	 */
	bool setValue(int newValue);
	
	/*************
	 * Get the current value being displayed on the LED
	 */
	int  getValue();
	
	/************************************************
	 * Set the digital pin the LED is connected to
	 *
	 * @param newValue The new digital pin
	 *
	 * @return true if the new value was accepted; false if a default was applied
	 */
	bool setLedPin(int newValue);

	/*************
	 * Get the current value for the LED pin
	 */
	int  getLedPin();
	
	/************************************************
	 * Set the LED ON count in ticks
	 *
	 * @param newValue The new LED ON count
	 *
	 * @return true if the new value was accepted; false if a default was applied
	 */
	bool setLedOnCountInTicks(int newValue);

	/*************
	 * Get the current value for the LED ON count in ticks
	 */
	int  getLedOnCountInTicks();
	
	/************************************************
	 * Set the LED OFF count in ticks
	 *
	 * @param newValue The new LED OFF count
	 *
	 * @return true if the new value was accepted; false if a default was applied
	 */
	bool setLedOffCountInTicks(int newValue);

	/*************
	 * Get the current value for the LED OF count in ticks
	 */
	int  getLedOffCountInTicks();
	
	/************************************************
	 * Set the delay repeat count in ticks
	 *
	 * @param newValue The new delay repeat count
	 *
	 * @return true if the new value was accepted; false if a default was applied
	 */
	bool setRepeatDelayCountInTicks(int newValue);

	/*************
	 * Get the current value for the delay repeat count in ticks
	 */
	int  getRepeatDelayCountInTicks();
	
	/********************************************
	 * Get a String representation of this object
	 */
	void toString(String &value);
	
	/****************************************************************************************************************************************
	* PRIVATE definitions follow, for use by the class itself, not exposed to the users of the created object.
	**********************************************************************************************************/
	private:

	/*************************
	 * Set by the constructors
	 */
	int	ledPin;					// The pin the LED is on
	int ledOnCountInTicks;		// How may ticks the LED must stay on for
	int ledOffCountInTicks;		// How may ticks the LED must stay off for
	int interValueDelayInTicks;	// How may ticks the LED must stay off for before the value is repeated

	/******************
	 * For internal use
	 */
	int 	ledOnCount;
	int 	ledOffCount;
	int 	valueCount;
	int 	repeatDelayCount;
	enum 	State state;
	bool	ledIsOn;
	int 	value;
	
	/********************************
	 * Actually initialize the class
	 *
	 * @param ledPin							// The digital pin the led is on 
	 * @param value                            // The value to display as LED flashes, this can be changed later
	 * @param ledOnCountInTicks                // How many ticks for the LED to remain on
	 * @param ledOffCountInTicks               // How many ticks for the LED to remain off
	 * @param repeatDelayCountInTicks          // How many ticks between displaying the value, must be > ledOffCountInTicks
	 */
	void init(
			int pin,
			int value,
			int ledOnCountInTicks,
			int ledOffCountInTicks,
			int repeatDelayCountInTicks);

	/*********************
	 * Simple state machine
	 */
	void processTicks();
	
	/***************
	 * Set up the LED
	 */
	void setupLED();
	
	/*******************
	 * Switch on the LED
	 */
	void switchOnLed();
	
	/********************
	 * Switch off the LED
	 */
	void switchOffLed();
};

#endif
