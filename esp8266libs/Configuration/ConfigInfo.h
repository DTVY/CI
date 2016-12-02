/*
 * ConfigInfo.h
 *
 *  Created on: Sep 19, 2016
 *      Author: trung.q.dinh
 */

#ifndef ESP8266LIBS_CONFIGURATION_CONFIGINFO_H_
#define ESP8266LIBS_CONFIGURATION_CONFIGINFO_H_
#include <WiFiAPConfiguredInformation.h>
#include "Include.h"
/*
 * Keeping config informations
 */
class ConfigInfo
{
private:
	WiFiAPConfiguredInformation _serverAPInfo;

	String _serverIP_Address;
	int _serverPort;
	String* _projectURLs;
	int _numberOfProjects;
public:
	/*
	 * IP:PORT/_ProjectURL
	 */
	static String getServerIP_AddressFromURL(String _url);
	static String getServerPortFromURL(String _url);
	static String getJenkinsProjectFromUrl(String _url);


	int getNumberOfProjects();
	void setNumberOfProjects(int _numberOfProjects);

	WiFiAPConfiguredInformation getServerAPInfo();
	void setServerAPInfo(WiFiAPConfiguredInformation _serverAPInfo);

	String getServerIP_Address();
	void setServerIP_Address(String _serverIP_Address);

	int getServerPort();
	void setServerPort(int _serverPort);

	String* getProjectURLs();
	void setProjectURLs(String* _projectURLs);
	void setProjectURLs(String _projectURL, int _index);

	ConfigInfo();
	virtual ~ConfigInfo();
};

#endif /* ESP8266LIBS_CONFIGURATION_CONFIGINFO_H_ */
