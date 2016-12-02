/*
 * Helper.cpp
 *
 *  Created on: Sep 19, 2016
 *      Author: trung.q.dinh
 */
#include"Include.h"
String Helper::getStringFromEEPROM(int pos, char _stopChar) {
	String res;
	Serial.println("Reading ->");
	char s_char;
	while (s_char != _stopChar) {
		s_char = EEPROM.get(pos, s_char);
		Serial.print(s_char);
		pos++;
	}
	Serial.println("\n -> Done");
	return res;
}

String Helper::getStringFromEEPROM(int pos, int numberOfChar) {
	String res;
	Serial.print("Reading ->");
	char s_char;
	for (int i = pos; i < pos + numberOfChar; i++) {
		s_char = EEPROM.get(i, s_char);
		delay(10);
		Serial.print(s_char);
		if (s_char != 0) {
			res += s_char;
		}
	}
	Serial.println("\n -> Done");
	return res;
}

void Helper::writeIntoEEPROM(int pos, int value, int numberOfValue) {
	Serial.println("Writing ->");
	for (int i = 0; i < numberOfValue; ++i) {
		EEPROM.write(pos + i, value);
		delay(10);
	}
	Serial.println("\n -> Done");
}
void Helper::writeIntoEEPROM(int pos, String str) {
	Serial.println("Writing ->");
	for (uint i = 0; i < str.length(); ++i) {
		EEPROM.write(pos + i, str[i]);
		delay(10);
		Serial.print(str[i]);
	}
	Serial.println("\n -> Done " + String(str.length()));
}

void Helper::checkEepromButton(void) {
	helper._clearingRequest = digitalRead(PIN_RESET_BUTTON);
	Serial.println("Reset Request:  " + String(helper._clearingRequest));
	if (helper._clearingRequest == 0) {
		helper.InitInterruptTimer1(CPU_FREQ); // CPU_FREQ*(1/80MHz) = 1s
		if (helper._clearingRequest == 0) {
			if (helper.Timer1CountSecond() == 6) {
				flagcleanEeprom = true;
			}
		}
	} else
		helper.ResetTimer1Count();
}

void Helper::InitInterruptTimer1(int Timer1Counter) {
	timer1_disable();
	countWhenConfigTimer1++;
	Serial.println(
			"TIME hold down clear EEPROM button:  "
					+ String(countWhenConfigTimer1));
	timer1_write(Timer1Counter);
	timer1_enable(TIM_DIV1, TIM_EDGE, TIM_SINGLE);

}

void Helper::turnOnLed(int _ledPin) {
	digitalWrite(_ledPin, HIGH);
}
void Helper::turnOffLed(int _ledPin) {
	digitalWrite(_ledPin, LOW);
}
void Helper::turnAllLedOff() {
	turnOffLed(PIN_LED_RED | PIN_LED_GREEN | PIN_LED_BLUE);
}
void Helper::turnOnOnlyLed(int _ledPin) {
	turnAllLedOff();
	turnOnLed(_ledPin);
}
void Helper::blinkLed(int _pinLed, int _time) {
	delay(_time);
	turnOffLed(_pinLed);
	delay(_time);
	turnOnLed(_pinLed);
}

void Helper::turnBuzzerOn() {
	for (int i = 0; i < 1000; i++) {
		digitalWrite(PIN_BUZZER, BUZZER_ON);
		delayMicroseconds(500);
		digitalWrite(PIN_BUZZER, BUZZER_OFF);
		delayMicroseconds(500);
	}
}
void Helper::turnBuzzerOff() {
	digitalWrite(PIN_BUZZER, BUZZER_OFF);
}
Helper::Helper() {
	pinMode(PIN_LED_RED | PIN_LED_GREEN | PIN_LED_BLUE, OUTPUT);
}

Helper::~Helper() {
	// TODO Auto-generated destructor stub
}

