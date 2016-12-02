/*
 * HEY Device
 */
#include "Include.h"
#include "FeedbackSystem.h"
#include<cstdio>

Configuration *deviceConfig = Configuration::getInstance();
Webserver configWebServer;
WiFiServer webserver(80);
Helper helper;
FeedbackSystem feedBackSystem;

volatile long Helper::countWhenConfigTimer1 = 0;
volatile bool Helper::flagcleanEeprom = false;
/*
 * Global variable for notifying beep
 */
int StartedBeepTime = millis();
int beeptimes = 0;
int deltaBeep = 60001;

//-------------------
void printConfiguration(void);
void reconfigDevice(void);
state_t initServer(void);
state_t serverLoop(void);
state_t initClient(void);
state_t noConnect(void);

//-------------------
int main() {
	helper.checkEepromButton();
	if (helper.flagcleanEeprom == 1) {
		Configuration::getInstance()->g_state = RECONFIG;
	}
	switch (Configuration::getInstance()->g_state) {
	case WEB_SERVER_INIT:
		Configuration::getInstance()->g_state = initServer();
		break;
	case WEB_SERVER:
		Configuration::getInstance()->g_state = serverLoop();
		break;
	case INIT_CLIENT:
		Configuration::getInstance()->g_state = initClient();
		break;
	case CONNECTED:
		feedBackSystem.Loop();
		break;
	case NO_CONNECT:
		noConnect();
		break;
	case RECONFIG:
		reconfigDevice();
		break;
	default:
		noConnect();
		break;
	}
	return 0;
}

void setup() {
	Serial.begin(115200);
	EEPROM.begin(512);

	pinMode(PIN_RESET_BUTTON, INPUT_PULLUP);
	deltaBeep = 60001;
	pinMode(PIN_BUZZER, OUTPUT);
	helper.turnBuzzerOff();

	Serial.println("\n\n\n\n\n----------------Setting up ----------------\n");
	delay(1000);

	Configuration::getInstance()->g_state = WEB_SERVER_INIT;

	helper.turnOnOnlyLed(PIN_LED_BLUE);
}

void reconfigDevice(void) {
	configWebServer.clearConfiguration();
	ESP.restart();
	Serial.println("Please Reconfig HEY! again ");
}
/*
 * Print configure information through Serial Monitor View
 */
void printConfiguration(void) {
	Serial.println(deviceConfig->getConfigInfo().getServerAPInfo().getSSID());
	Serial.println(
			deviceConfig->getConfigInfo().getServerAPInfo().getPassword());
	Serial.println(deviceConfig->getConfigInfo().getServerIP_Address());
	Serial.println(deviceConfig->getConfigInfo().getServerPort());
	Serial.println(deviceConfig->getConfigInfo().getNumberOfProjects());

	for (int i = 0; i < 5; i++) {
		Serial.println(deviceConfig->getConfigInfo().getProjectURLs()[i]);
	}
}
/*
 * Make Device become an AP for configuration
 */
state_t initServer(void) {
	if (!configWebServer.isConfigured()) {
		deviceConfig->getDevicesAP().setSSID("HEY_NETWORK");
		deviceConfig->getDevicesAP().setPassword("123456789");
		HeyWiFi.softAP(deviceConfig->getDevicesAP().getSSID().c_str(),
				deviceConfig->getDevicesAP().getPassword().c_str());

		IPAddress myIP = HeyWiFi.softAPIP();

		Serial.println("\n");
		Serial.println("AP IP address: ");
		Serial.println(myIP);

		webserver.begin();

		Serial.println("HTTP server started");

		return WEB_SERVER;
	} else {
		//if had configuration in EEPROM, use it
		deviceConfig->setConfigInfo(configWebServer.getConfigInfoFromEEPROM());

		printConfiguration();

		return INIT_CLIENT;
	}
}
/*
 * Receive configured information from request
 */
state_t serverLoop(void) {
	WiFiClient client_ser = webserver.available();
//	String request = client_ser.readStringUntil('\r');
	String OGrequest = client_ser.readString(); // Original request from browser even GET or POST
	String request = OGrequest.substring(OGrequest.indexOf("SSID")); // request after edit
	if (request != 0)
		Serial.println("Request was received       " + request);
	Serial.println("OGRequest was received       " + OGrequest); // print out to view for debug
	client_ser.flush(); // flush request
	if (OGrequest != 0) {
		deviceConfig->setConfigInfo(configWebServer.getConfiguration(request));

		if (configWebServer.isValidInfo()) //check valid information from Request
		{
			client_ser.println(ConfigurePage::getInstance()->getSuccessPage());
//			Export config info into web page
//			client_ser.println("SSID = " + deviceConfig->getConfigInfo().getServerAPInfo().getSSID());
//			client_ser.println("\nIP Address = " + deviceConfig->getConfigInfo().getServerIP_Address());
//			client_ser.println("\nPort = " + String(deviceConfig->getConfigInfo().getServerPort()));
//			for (int i = 0; i < deviceConfig->getConfigInfo().getNumberOfProjects(); ++i)
//			{
//				client_ser.println("project" + String(i + 1) + ":" + deviceConfig->getConfigInfo().getProjectURLs()[i]);
//			}

			return INIT_CLIENT;
		} else {
			client_ser.println(ConfigurePage::getInstance()->getHeader());
			client_ser.println(
					ConfigurePage::getInstance()->getConfigurePage());
		}
	}
	return WEB_SERVER;
}

/*
 * Access to another WiFiAP for receiving results from Jenkins
 */
state_t initClient(void) {
	Configuration::getInstance()->wifiSetup();

	Serial.println(HeyWiFi.localIP());

	if (HeyWiFi.status() != WL_CONNECTED) {
		helper.turnOnOnlyLed(PIN_LED_RED);

		return NO_CONNECT;
	}

	helper.turnOnOnlyLed(PIN_LED_GREEN);
	return CONNECTED;
}

/*
 * Let device notify when have troubles with connection
 */
state_t noConnect(void) {
	// make 10 beep sounds and repeat after 1 minute
	if (deltaBeep > 10000) {
		if (beeptimes <= 10) {
			helper.turnBuzzerOn();
			delay(50);
			helper.turnOnOnlyLed(PIN_LED_BLUE);
			delay(50);
//				digitalWrite(PIN_BUZZER, BUZZER_OFF);
			helper.turnBuzzerOff();
			helper.turnOffLed(PIN_LED_BLUE);
			delay(500);
			helper.turnOnOnlyLed(PIN_LED_BLUE);

			beeptimes++;

		} else {
			StartedBeepTime = millis();
			deltaBeep = millis() - StartedBeepTime;
			beeptimes = 0;
		}
	} else {
		deltaBeep = millis() - StartedBeepTime;
	}
	return NO_CONNECT;
}

void loop() {
	main();
}
