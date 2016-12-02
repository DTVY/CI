/*
 * FeedbackSystem.cpp
 *
 *  Created on: Oct, 31, 2016
 *      Author: thuan.t.nguyen
 */
/*
 * Read these code lines and understand by yourself =="
 */
#include "FeedbackSystem.h"

/* Common operational variable */
u_long StartFixingTime;
u_long StartedTime;
bool success = true;
static bool flag10min = false;
static bool flagStatus = false;
bool initial = true;
ESP8266WiFiMulti WiFiMulti;
HTTPClient http;

/* ---------------------- */
String getColorFromJenkins(HTTPClient *http, String endpoint) {
	http->begin(Configuration::getInstance()->getConfigInfo().getServerIP_Address(),Configuration::getInstance()->getConfigInfo().getServerPort(),endpoint); //HTTP
	Serial.println("[HTTP] " + Configuration::getInstance()->getConfigInfo().getServerIP_Address() + ":" + Configuration::getInstance()->getConfigInfo().getServerPort()+ endpoint);

	// start connection and send HTTP header
	int httpCode = http->GET();
	if (httpCode) {
		// HTTP header has been send and Server response header has been handled
		Serial.printf("[HTTP] GET... code: %d\n", httpCode);

		// file found at server
		if (httpCode == -2) {
			return "blue";
		}
		if (httpCode == 200) {
			String payload = http->getString();
			Serial.println("[JSON]" + payload);
			JSONClass _json;
			_json = JSONClass::getJSONByKeyFromString(payload, "color");
			payload = _json.getString();
			Serial.println("[JSON]" + payload);

			payload.replace("{\"color\":\"", "");
			payload.replace("\"}", "");
			Serial.println("[HTTP] " + payload + "\n");

			return payload;
		} else {
			return "red";
		}
	} else {
		Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
	}

	http->end();
	delay(200);

	return "";
}

/**
 * Is building
 */
bool isBuilding(String color) {
	return color.endsWith("_anime");
}

/**
 * Alternate the GPIO level
 */
void blink(int delay_ms, int count, const int LED) {
	for (int i = 0; i <= count; i++) {
//		digitalWrite(BUILTIN_LED, LOW);
		digitalWrite(LED, LOW);
		delay(delay_ms);
//		digitalWrite(BUILTIN_LED, HIGH);
		digitalWrite(LED, HIGH);
		delay(delay_ms);
	}
}

void FeedbackSystem::Loop() {

	// wait for WiFi connection
	if ((HeyWiFi.status() == WL_CONNECTED)) {
		http.setReuse(true);
		int colorResult = PIN_LED_GREEN;
		String temp;
		bool isBuild = false;

		for (unsigned int i = 0; i < Configuration::getInstance()->getConfigInfo().getNumberOfProjects(); i++) {
			String _projectURL = Configuration::getInstance()->getConfigInfo().getProjectURLs()[i] + JENKINS_COLOR_SUFFIX;
//			String _projectURL = "/jenkins/job/DCC/api/json?tree=color";
			Serial.println(_projectURL);
			temp = getColorFromJenkins(&http, _projectURL);

			if (isBuilding(temp)) {
				isBuild = true;
				flag10min = false;
			}

			if (temp.startsWith("red")) {
				colorResult = PIN_LED_RED;
			}
		}

		//led will be flash keep the status led before
		if (isBuild) {
			blink(TIME_DELAY, 10, colorResult);
			initial = true;
			flagStatus = true;

		} else {
			if (flagStatus) {
				helper.turnBuzzerOn();
				delay(TIME_DELAY);
				flagStatus = false;
			}

			Serial.println("loop1.1:" + String(colorResult));
			digitalWrite(colorResult, HIGH);

			//ERROR affect to red_led
			if (colorResult == PIN_LED_RED) {
				u_long static getTime = millis(); //get Time system
				Serial.println("loop1.2:" + String(colorResult));
				digitalWrite(PIN_LED_GREEN, LOW);
				//firstly, 10s for buzzer ring + led flashing
				if (initial) {
					for (int i = 0; i < 10; i++) {
						helper.turnBuzzerOn();
						helper.blinkLed(PIN_LED_RED, TIME_DELAY);
						Serial.println(
								String(PIN_BUZZER) + "Count: " + String(i));
					}
					getTime = millis();
					initial = false;
				}

				//20min buzzer ring if error not fixed
				if ((unsigned long) (millis() - getTime) > FIXING_TIME_20MIN) {
					Serial.println("20minutes");

					for (int i = 0; i < 10; i++) {
						helper.turnBuzzerOn();
						delay(TIME_DELAY);
						helper.turnBuzzerOff();
						Serial.println(
								String(PIN_BUZZER) + "Count: " + String(i));
					}
					getTime = millis();
					flag10min = true;

					//every 10min buzzer ring if error not fixed
				} else if (((unsigned long) (millis() - getTime)
						> FIXING_TIME_10MIN) && flag10min) {
					Serial.println("10minutes");
					for (int i = 0; i < 10; i++) {
						helper.turnBuzzerOn();
						delay(TIME_DELAY);
						helper.turnBuzzerOff();

						Serial.println(
								String(PIN_BUZZER) + "Count: " + String(i));
					}
					getTime = millis();
				}
			}
			if (colorResult == PIN_LED_GREEN) {
				digitalWrite(PIN_LED_RED, LOW);
			}
		}
		//-------------------------------------------------------------------------
		delay(1000);
		digitalWrite(PIN_BUZZER, BUZZER_OFF);
	}
}
FeedbackSystem::FeedbackSystem() {
	// TODO Auto-generated constructor stub
}

FeedbackSystem::~FeedbackSystem() {
	// TODO Auto-generated destructor stub
}
