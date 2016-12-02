
#ifndef ESP8266LIBS_WEBSERVER_CONFIGUREPAGE_H_
#define ESP8266LIBS_WEBSERVER_CONFIGUREPAGE_H_

#include <WString.h>
#include "string.h"
#include<cstdio>
#include<string>
/*
 * Generate HTML code for configuration page
 */
class ConfigurePage
{
    private:
        ConfigurePage();

        String _header;
        String getBody(String _body);
        String _successPage;
        String _configurePage;
        static ConfigurePage *_instance;
    public:
        static ConfigurePage *getInstance();
        String getHeader();
        String getSuccessPage();
        String getConfigurePage();
        String getNoConnectionPage();
        virtual ~ConfigurePage();
};

#endif
