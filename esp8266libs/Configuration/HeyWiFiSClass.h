/*
 * HeyWiFiSTAClass.h
 *
 *  Created on: Oct 6, 2016
 *      Author: trung.q.dinh
 */

#ifndef ESP8266LIBS_WEBSERVER_HEYWIFISTACLASS_H_
#define ESP8266LIBS_WEBSERVER_HEYWIFISTACLASS_H_
#pragma once
#include <stdint.h>
#include "Include.h"
#include "ESP8266WiFi.h"
/*
 * Use strategy desin pattern for open up ESP8266WiFi class
 */
class HeyWiFiClass: public ESP8266WiFiClass
{
private:
	ESP8266WiFiClass _wiFi;
public:
	uint8_t waitForConnectResult(int _pin);
	int option();
	HeyWiFiClass();
	virtual ~HeyWiFiClass();
};
extern HeyWiFiClass HeyWiFi;
#endif /* ESP8266LIBS_WEBSERVER_HEYWIFISTACLASS_H_ */
