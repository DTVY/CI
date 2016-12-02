/*
 * Helper.h
 *
 *  Created on: Sep 19, 2016
 *      Author: trung.q.dinh
 */

#ifndef ESP8266LIBS_HELPER_HELPER_H_
#define ESP8266LIBS_HELPER_HELPER_H_
#include"WString.h"
#include "Webserver.h"
#include"Configuration.h"

class Helper {
private:
	static volatile long countWhenConfigTimer1;
	volatile int _clearingRequest;

public:
	static volatile bool flagcleanEeprom;
	String getStringFromEEPROM(int pos, int numberOfChar);
	String getStringFromEEPROM(int pos, char _stopChar);

	void writeIntoEEPROM(int pos, String str);
	void writeIntoEEPROM(int pos, int value, int numberOfValue);

	static long Timer1CountSecond() {
		return countWhenConfigTimer1;
	}
	void ResetTimer1Count() {
		countWhenConfigTimer1 = 0;
	}

	void checkEepromButton();

	void turnAllLedOff();
	void turnOnLed(int _ledPin);
	void turnOffLed(int _ledPin);
	void turnOnOnlyLed(int _ledPin);
	void blinkLed(int _ledPin, int _time);

	void InitInterruptTimer1(int);

	void turnBuzzerOn();
	void turnBuzzerOff();
	Helper();
	virtual ~Helper();
};
extern Helper helper;


#endif /* ESP8266LIBS_HELPER_HELPER_H_ */
