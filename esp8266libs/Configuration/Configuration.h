#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Include.h"
#include "ConfigInfo.h"
#include "WiFiAPConfiguredInformation.h"

/*
 * Config the device
 */
class Configuration
{
private:
	Configuration();
	static Configuration *_instance;
	ConfigInfo _ConfigInfo;
	WiFiAPConfiguredInformation _devicesAP;

	public:
		static Configuration *getInstance();
		ConfigInfo getConfigInfo();
		void setConfigInfo(ConfigInfo _configInfo);
		state_t g_state;

		WiFiAPConfiguredInformation getDevicesAP();
		void setDevicesAP(WiFiAPConfiguredInformation _devicesAP);

		~Configuration();
		void wifiSetup();
};

#endif /* CONFIGURATION_H_ */
