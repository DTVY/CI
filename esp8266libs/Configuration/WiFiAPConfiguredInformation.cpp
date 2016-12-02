/*
 * WiFiConfiguredInformation.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: trung.q.dinh
 */

#include <WiFiAPConfiguredInformation.h>

String WiFiAPConfiguredInformation::getSSID()
{
	return this->_SSID;
}
void WiFiAPConfiguredInformation::setSSID(String _SSID)
{
	this->_SSID = _SSID;
}

String WiFiAPConfiguredInformation::getPassword()
{
	return this->_password;
}
void WiFiAPConfiguredInformation::setPassword(String _password)
{
	this->_password = _password;
}

String WiFiAPConfiguredInformation::getDefaultIP()
{
	return this->_defaultIP;
}
void WiFiAPConfiguredInformation::setDefaultIP(String _defaultIP)
{
	this->_defaultIP = _defaultIP;
}

WiFiAPConfiguredInformation::WiFiAPConfiguredInformation()
{
	this->_SSID = "TEMPSSID";
	this->_password = "";
	this->_defaultIP = "";
	
}

WiFiAPConfiguredInformation::~WiFiAPConfiguredInformation()
{
	// TODO Auto-generated destructor stub
}

