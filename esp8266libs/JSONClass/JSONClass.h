/*
 * JSONClass.h
 *
 *  Created on: Oct 13, 2016
 *      Author: trung.q.dinh
 */

#ifndef ESP8266LIBS_JSONCLASS_JSONCLASS_H_
#define ESP8266LIBS_JSONCLASS_JSONCLASS_H_
#include "Include.h"
class JSONClass
{
	String _key;
	String _value;
public:
	String getString();

	String getKey();
	void setKey(String _key);

	String getValue();
	void setValue(String _value);

	static JSONClass getJSONByKeyFromString(String _scr, String _key);

	void Parse(String _json);
	JSONClass();
	virtual ~JSONClass();
};

#endif /* ESP8266LIBS_JSONCLASS_JSONCLASS_H_ */
