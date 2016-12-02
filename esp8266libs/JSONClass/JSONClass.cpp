/*
 * JSONClass.cpp
 *
 *  Created on: Oct 13, 2016
 *      Author: trung.q.dinh
 */

#include "JSONClass.h"
#include "Include.h"
String JSONClass::getString()
{
	return "{\"" + this->_key + "\":\"" + this->_value + "\"}";
}

String JSONClass::getKey()
{
	return this->_key;
}
void JSONClass::setKey(String _key)
{
	this->_key = _key;
}


String JSONClass::getValue()
{
	return this->_value;
}
void JSONClass::setValue(String _value)
{
	this->_value = _value;
}

JSONClass JSONClass::getJSONByKeyFromString(String _scr , String _key)
{
	String tmp = "";

	int idx = _scr.indexOf("\"" + _key + "\"");
//	Serial.println("scr = " + _scr);
	int count = 0;
	int i = idx;
	do
	{
		tmp += _scr[i];
//		Serial.println("tmp = " + tmp);
		if(_scr[i] == '\"')
		{
			count++;
		}
		i++;
	}while(count<4);
//	Serial.println("tmp = " + tmp);
	JSONClass res;
	res.Parse(tmp);

	return res;
}

void JSONClass::Parse(String _json)
{
	JSONClass res;

	_json.replace("\"","");
	String tmp  = "";
	int _length = _json.length();
	int i = 0;
	for(; i< _length; i++)
	{
		if(_json[i] == ':')
		{
			break;
		}
		else
		{
			tmp += _json[i];
		}
	}
	this->_key = tmp;
//	Serial.println("tmp = " + tmp);
	tmp = "";
	i++;
	for (; i < _length; i++)
	{
		if (_json[i] == ':')
		{
			break;
		}
		else
		{
			tmp += _json[i];
		}
	}
	this->_value = tmp;
//	Serial.println("tmp = " + tmp);
}

JSONClass::JSONClass()
{
	this->_key = "";
	this->_value = "";
}

JSONClass::~JSONClass()
{
	// TODO Auto-generated destructor stub
}
