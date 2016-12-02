/*
 * FeedbackSystem.h
 *
 *  Created on: Sep 20, 2016
 *      Author: trung.q.dinh
 */


#include"Include.h"
#include "JSONClass.h"
#include"Configuration.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#ifndef ESP8266LIBS_FEEDBACKSYSTEM_FEEDBACKSYSTEM_H_
#define ESP8266LIBS_FEEDBACKSYSTEM_FEEDBACKSYSTEM_H_

#define FIXING_TIME_10MIN 20000
#define FIXING_TIME_20MIN 40000
#define TIME_DELAY 500
class FeedbackSystem
{
public:
	void Loop();
	FeedbackSystem();
	virtual ~FeedbackSystem();
};

#endif /* ESP8266LIBS_FEEDBACKSYSTEM_FEEDBACKSYSTEM_H_ */
