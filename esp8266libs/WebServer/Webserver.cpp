#include "Include.h"
#include "WiFiAPConfiguredInformation.h"
#include "Helper.h"

bool Webserver::isConfigured()
{
	char res;
	res = EEPROM.get(0,res);
	Serial.println(res);
	return (res=='1'?true:false);
}

/*
 * First offset values: 0|1
 * Clear Configured information from EEPROM
 * Just need to make first offset off
 */

void Webserver::clearConfiguration()
{
	EEPROM.begin(512);
	EEPROM.write(0,'0');
	delay(10);
	EEPROM.commit();
}

/*
 * Read Configured information from EEPROM
 */
ConfigInfo Webserver::getConfigInfoFromEEPROM()
{

	Helper helper;
	ConfigInfo _configInfo;
	int pos = 1;

	String tmp = "";

	Serial.println("Getting configInfo ---->");
	delay(1000);
	tmp = helper.getStringFromEEPROM(pos,341);
	tmp = "";


	tmp = helper.getStringFromEEPROM(pos,35);
	tmp.replace("`","");

	WiFiAPConfiguredInformation _ServerAPInfo; // Have to use this for avoiding lvalue case

	_ServerAPInfo.setSSID(tmp);

	pos+=35;
//	Serial.println("SSID: " + _configInfo.getServerAPInfo().getSSID());

	tmp = helper.getStringFromEEPROM(pos,35);
	tmp.replace("`","");
	_ServerAPInfo.setPassword(tmp);
	pos+=35;
//	Serial.println("Password: " + _configInfo.getServerAPInfo().getPassword());

	_configInfo.setServerAPInfo(_ServerAPInfo);
	Serial.println("SSID: " + _configInfo.getServerAPInfo().getSSID());
	Serial.println("Password: " + _configInfo.getServerAPInfo().getPassword());
	tmp = helper.getStringFromEEPROM(pos,15);
	tmp.replace("`","");
	_configInfo.setServerIP_Address(tmp);
	pos+=15;
	Serial.println("Server: " + tmp);

	tmp = helper.getStringFromEEPROM(pos,5);
	tmp.replace("`","");
	_configInfo.setServerPort(tmp.toInt());
	pos+=5;
	Serial.println("Port: " + tmp);

	for (int j = 0; j < 5; j++)
	{
		tmp = helper.getStringFromEEPROM(pos,50);
		tmp.replace("`","");
		Serial.println(tmp);
		_configInfo.setProjectURLs(tmp,j);
		pos+=50;
	}
	Serial.println("\n----------------Imported configuration ----------------\n");

	return _configInfo;
}

/*
 * Write Configured information into EEPROM
 */
int Webserver::saveConfigInfo(ConfigInfo _configInfo)
{
	Helper helper;
	/*
	 * use Flag 0|1 to check configInfo avaible
	 */

	/*maximum length of
	 * ssid: 35
	 * password: 35
	 * serverIP: 15
	 * serverPORT: 5
	 * jenkinsURL: 50 x 5 = 250
	 *
	 */

	EEPROM.begin(512);

	String _value  = "1";
	String tmp = "";
	tmp = _configInfo.getServerAPInfo().getSSID();
	Serial.println("Saving configInfo ----<");
	while(tmp.length()<35)
	{
		tmp = "`"+tmp;
	}
	_value += tmp;
	Serial.println("SSID: " + tmp);


	tmp = _configInfo.getServerAPInfo().getPassword();
	while(tmp.length()<35)
	{
		tmp = "`" + tmp;
	}
	_value += tmp;
	Serial.println("Password: " + tmp);

	tmp = _configInfo.getServerIP_Address();
	while (tmp.length() < 15)
	{
		tmp = "`" + tmp;
	}
	_value += tmp;
	Serial.println("Server: " + tmp);

	tmp = String(_configInfo.getServerPort());
	while (tmp.length() < 5)
	{
		tmp = "`" + tmp;
	}
	_value += tmp;
	Serial.println("Port: " + tmp);

	for(int j=0; j<5; j++)
	{

		tmp = _configInfo.getProjectURLs()[j];
		Serial.println(_configInfo.getProjectURLs()[j]);
		while (tmp.length() < 50)
		{
			tmp = "`" + tmp;
		}
		Serial.println(tmp);
		_value += tmp;
	}

	helper.writeIntoEEPROM(0,_value);
	EEPROM.commit();

	return _value.length();
}
bool Webserver::isValidInfo()
{
	return this->_validInfo;
}

/*
 * Get configured information from request from configuration page
 */
ConfigInfo Webserver::getConfiguration(String _stringRequest)
{
	//Decode symbols from HTML request
	_stringRequest.replace("%2F","/");
	_stringRequest.replace("%3F","?");
	_stringRequest.replace("%3D","=");
	_stringRequest.replace("%3A",":");

	ConfigInfo _config;

	WiFiAPConfiguredInformation _APConfig;

	if (-1 != _stringRequest.indexOf( "SSID=" ))
	{
		_APConfig.setSSID(
				_stringRequest.substring(
				_stringRequest.indexOf( "SSID=" ) + 5,
				_stringRequest.indexOf( "&password" ) ));

		_APConfig.setPassword(
				_stringRequest.substring(
				_stringRequest.indexOf( "password=" ) + 9,
				_stringRequest.indexOf( "&txt_JenkinsURL=" ) ));
		_config.setServerAPInfo(_APConfig);

		String _jenkinsURL =
				_stringRequest.substring(
				_stringRequest.indexOf( "txt_JenkinsURL=" ) + 15,
				_stringRequest.indexOf( "&txt_Project1" ) );



		/*
		 * type 1: http://
		 * type 2: 192.168...
		 * type 3: httls://
		 * type 4: has www.
		 */
		_jenkinsURL.replace("www.","");
		if(_jenkinsURL.indexOf("//") > 0)
		{
			_jenkinsURL = _jenkinsURL.substring(_jenkinsURL.indexOf("//")+2, _jenkinsURL.length());
		}

		_config.setServerIP_Address(_jenkinsURL.substring(0,_jenkinsURL.indexOf(":")));
		_config.setServerPort(_jenkinsURL.substring(_jenkinsURL.indexOf(":")+1,_jenkinsURL.indexOf("/")).toInt());
//		Serial.println(_jenkinsURL);
		String _prefix = _jenkinsURL.substring(_jenkinsURL.indexOf("/"), _jenkinsURL.length());
//		Serial.println(_prefix);

		//Get project's URL
/*		String _projectStringRequest =
					_stringRequest.substring(
					_stringRequest.indexOf( "txt_Project1="),
					_stringRequest.indexOf( "HTTP/1.1" ) - 1 );
*/
		String _projectStringRequest =_stringRequest.substring(_stringRequest.indexOf( "txt_Project1="));
		Serial.println("--------"+_projectStringRequest+"-----"); //print out list project request to view
		String _projectURL;
		int _numberOfProject = 0;

		for(int i=0; i<5; ++i)
		{
			_projectURL =
					_projectStringRequest.substring(
					_projectStringRequest.indexOf( "txt_Project"+ String(i+1) +"=" ) + 13,
					_projectStringRequest.indexOf( "&txt_Project"+ String(i+2)));

			if(_projectURL != "")
			{
				_config.setProjectURLs(_prefix + JENKINS_PROJECT_PREFIX + _projectURL, _numberOfProject++);
				Serial.println("project name "+_projectURL);
			}

		}

		_config.setNumberOfProjects(_numberOfProject);
	}
	if ((_config.getServerAPInfo().getSSID() != "") && (_config.getServerAPInfo().getPassword() != ""))
	{

		Helper helper;
		this->saveConfigInfo(_config);
		helper.getStringFromEEPROM(0,341);
		this->_validInfo = true;
	}
	return _config;
}
Webserver::Webserver()
{
	this->_validInfo = false;
}
Webserver::~Webserver()
{

}
