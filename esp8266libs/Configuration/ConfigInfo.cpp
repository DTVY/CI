/*
 * ConfigInfo.cpp
 *
 *  Created on: Sep 19, 2016
 *      Author: trung.q.dinh
 */
#include "Include.h"
#include <ConfigInfo.h>

String ConfigInfo::getServerIP_AddressFromURL(String _url)
{
	return _url.substring(0,_url.indexOf(":")-1);
}
String ConfigInfo::getServerPortFromURL(String _url)
{
	return _url.substring(_url.indexOf(":")+1, _url.indexOf("/")-1);
}
String ConfigInfo::getJenkinsProjectFromUrl(String _url)
{
	return _url.substring(_url.indexOf("/"), _url.length()-1);
}
int ConfigInfo::getNumberOfProjects()
{
	int res=0;
	for(int i=0; i<5; i++)
	{
		if(this->_projectURLs[i]!="")
		{
			res++;
		}
	}
	this->_numberOfProjects = res;
	return this->_numberOfProjects;
}

WiFiAPConfiguredInformation ConfigInfo::getServerAPInfo()
{
	return this->_serverAPInfo;
}
void ConfigInfo::setServerAPInfo(WiFiAPConfiguredInformation _serverAPInfo)
{
	this->_serverAPInfo = _serverAPInfo;
}

void ConfigInfo::setNumberOfProjects(int _numberOfProjects)
{
	this->_numberOfProjects = _numberOfProjects;
}
String ConfigInfo::getServerIP_Address()
{
	return this->_serverIP_Address;
}
void ConfigInfo::setServerIP_Address(String _serverIP_Address)
{
	this->_serverIP_Address = _serverIP_Address;
}
int ConfigInfo::getServerPort()
{
	return this->_serverPort;
}
void ConfigInfo::setServerPort(int _serverPort)
{
	this->_serverPort = _serverPort;
}

String* ConfigInfo::getProjectURLs()
{

	return this->_projectURLs;
}
void ConfigInfo::setProjectURLs(String* _projectURLs)
{
	this->_projectURLs = _projectURLs;
}
void ConfigInfo::setProjectURLs(String _projectURL, int _index)
{
	this->_projectURLs[_index] = _projectURL;
}
ConfigInfo::ConfigInfo()
{
	this->_numberOfProjects = 5;
	this->_projectURLs = new String[this->_numberOfProjects];
	this->_serverPort = 0;
	this->_serverAPInfo.setSSID("serverAPINFO");
}

ConfigInfo::~ConfigInfo()
{
	// TODO Auto-generated destructor stub
}
