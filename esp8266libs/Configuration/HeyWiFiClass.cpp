/*
 * HeyWiFiSTAClass.cpp
 *
 *  Created on: Oct 6, 2016
 *      Author: trung.q.dinh
 */

#include <HeyWiFiSClass.h>
#include "ESP8266WiFi.h"
#include "ESP8266WiFiGeneric.h"
#include "ESP8266WiFiSTA.h"

/*
 * Have to have these statements
 * Dont know why it work ./.
 */
extern "C" {
#include "c_types.h"
#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "mem.h"
#include "user_interface.h"
#include "smartconfig.h"
#include "lwip/err.h"
#include "lwip/dns.h"
}

#include "debug.h"
//#include "user_interface.h"
#include "Include.h"

HeyWiFiClass HeyWiFi;
/*
 * Notify when in connecting mode
 */
uint8_t HeyWiFiClass::waitForConnectResult(int _pin)
{
	Helper Helper;

	//1 and 3 have STA enabled
	if ((wifi_get_opmode() & 1) == 0)
	{
		return WL_DISCONNECTED;
	}
	int i = 0;
	Serial.println("Hey WiFi SSID: -- "+HeyWiFi.SSID());
	while (HeyWiFi.status() == WL_DISCONNECTED)
	{
		if (i > 100)
		{
			i = 0;
			Serial.println(".");
		}
		Serial.print(".");
		i++;

		digitalWrite(_pin, LOW);
		delay(100);
		digitalWrite(_pin, HIGH);
		delay(100);
	}
	return HeyWiFi.status();
}
int HeyWiFiClass::option()
{
	return 123;
}
HeyWiFiClass::HeyWiFiClass()
{
	// TODO Auto-generated constructor stub
	
}

HeyWiFiClass::~HeyWiFiClass()
{
	// TODO Auto-generated destructor stub
}

