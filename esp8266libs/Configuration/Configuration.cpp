
#include <HeyWiFiSClass.h>
#include "Include.h"
Configuration *Configuration::_instance = NULL;

Configuration* Configuration::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new Configuration();
	}
	return _instance;
}
Configuration::Configuration()
{
	g_state = INIT_CLIENT;

	//Default configuration
	this->_devicesAP.setSSID("HEY_NETWORK");
	this->_devicesAP.setPassword("123456789");
}

Configuration::~Configuration()
{
}

WiFiAPConfiguredInformation Configuration::getDevicesAP()
{
	return this->_devicesAP;
}
void Configuration::setDevicesAP(WiFiAPConfiguredInformation _devicesAP)
{
	this->_devicesAP = _devicesAP;
}

ConfigInfo Configuration::getConfigInfo()
{
	return this->_ConfigInfo;
}
void Configuration::setConfigInfo(ConfigInfo _configInfo)
{
	this->_ConfigInfo = _configInfo;
}
/*
 * Turn on client mode for accessing another AP
 */
void Configuration::wifiSetup()
{
	//Turn off AP mode
	HeyWiFi.disconnect();
	HeyWiFi.softAPdisconnect(true);

	//Setup information
	HeyWiFi.begin( this->_ConfigInfo.getServerAPInfo().getSSID().c_str(), this->_ConfigInfo.getServerAPInfo().getPassword().c_str() );
	Serial.println("wifi Setting up ..................");
	Serial.println("SSID = "+this->_ConfigInfo.getServerAPInfo().getSSID());
	Serial.println("Password = "+this->_ConfigInfo.getServerAPInfo().getPassword());
	HeyWiFi.mode( WIFI_STA );
	delay(2000);

	//Connect to an WiFi AP
	HeyWiFi.waitForConnectResult(PIN_LED_BLUE);


}


