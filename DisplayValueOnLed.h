#ifndef DisplayValueOnLed_h
#define DisplayValueOnLed_h

class DisplayValueOnLed {
	public:
	
	enum State {START, LED_ON, LED_OFF, DISPLAYED_VALUE_CHECK, INTER_VALUE_DELAY};

	private:
	
	int ledOnCountInTicks;
	int ledOffCountInTicks;
	int interValueDelayInTicks;

	int ledOnCount;
	int ledOffCount;
	int valueCount;
	int repeatDelayCount;

	bool ledShouldBeOn;

	enum State state;
	
	long ledSwitchedOnCount;

	int value;
	
	void init(
			int value,
			int ledOnCountInTicks,
			int ledOffCountInTicks,
			int repeatDelayCountInTicks);
	
	void processTicks();

	void switchOnLed();
	
	void switchOffLed();
	
	public:

	DisplayValueOnLed(
			int value,
			int ledOnCountInTicks,
			int repeatDelayCountInTicks);

	 /**
	  * See comments above, this allows the off time to be specified as well.
	  *
	  * @param value                            // The value to display as LED flashes, this can be changed later
	  * @param ledOnCountInTicks                // How many ticks for the LED to remain on
	  * @param ledOffCountInTicks               // How many ticks for the LED to remain off
	  * @param repeatDelayCountInTicks               // How many ticks between displaying the value, must be > ledOffCountInTicks
	  */
	DisplayValueOnLed(
			int value,
			int ledOnCountInTicks,
			int ledOffCountInTicks,
			int repeatDelayCountInTicks);
			
	
	/**
	 * Call this at a regular frequency. Also see tick(newValue)
	 *
 	 * @return true if the LED should be switch on; else false for it to be switched off
	 */
	bool tick();

	/**
	 * Call this at a regular frequency. This is logically the same as calling :-
	 *
	 * setValue(newValue); tick();
	 *
	 * @param newValue The new value to display, but ignored if the same as the current value
	 
 	 * @return true if the LED should be switch on; else false for it to be switched off
	 */
	bool tick(int newValue);

	/**
	 * Set a value to display - will reset the state.
	 *
	 * @param value The new value to display
	 */
	void setValue(int newValue);
};

#endif
