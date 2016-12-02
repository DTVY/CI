/*
 * WiFiConfiguredInformation.h
 *
 *  Created on: Oct 5, 2016
 *      Author: trung.q.dinh
 */

#ifndef ESP8266LIBS_CONFIGURATION_WIFIAPCONFIGUREDINFORMATION_H_
#define ESP8266LIBS_CONFIGURATION_WIFIAPCONFIGUREDINFORMATION_H_
#include "WString.h"

class WiFiAPConfiguredInformation
{
	String _SSID;
	String _password;
	String _defaultIP;
public:
	String getSSID();
	void setSSID(String _SSID);

	String getPassword();
	void setPassword(String _password);

	String getDefaultIP();
	void setDefaultIP(String _defaultIP);

	WiFiAPConfiguredInformation();
	virtual ~WiFiAPConfiguredInformation();
};

#endif /* ESP8266LIBS_CONFIGURATION_WIFIAPCONFIGUREDINFORMATION_H_ */
