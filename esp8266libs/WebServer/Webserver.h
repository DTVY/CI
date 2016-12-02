#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include "Include.h"
#include "Helper.h"
class Webserver
{
private:
	bool _validInfo;
public:

	ConfigInfo getConfigInfoFromEEPROM();
	int saveConfigInfo(ConfigInfo _configInfo);

	bool isConfigured();
	void clearConfiguration();


	bool isValidInfo();
	ConfigInfo getConfiguration(String _stringRequest);
	Webserver();
	virtual ~Webserver();
};
#endif /* 00_HAW_WEBSERVER_H_ */
