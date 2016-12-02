#include "ConfigurePage.h"


ConfigurePage *ConfigurePage::_instance = NULL;
ConfigurePage *ConfigurePage::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ConfigurePage();
    }
    return _instance;
}
String ConfigurePage::getHeader()
{
	return this->_header;
}
String ConfigurePage::getBody(String _body)
{
    return "<html>\n\ " + _body + "<html/>";
}

String ConfigurePage::getSuccessPage()
{
    return this->_header + this->getBody(this->_successPage);
}
String ConfigurePage::getConfigurePage()
{
    return this->getBody(this->_configurePage);
}
ConfigurePage::ConfigurePage()
{
    this->_header =
    "<title>\n\
    Extreme Feedback System\n\
    </title>\n\
    <head>\n\
        <style>\n\
            * {\n\
                box-sizing: border-box;\n\
            }\n\
            *:focus {\n\
                outline: none;\n\
            }\n\
            body {\n\
                font-family: Arial;\n\
                background-color: #3498DB;\n\
                padding: 10px;\n\
            }\n\
            .login {\n\
                margin: 20px auto;\n\
                width: 600px;\n\
            }\n\
            .login-screen {\n\
                background-color: #FFF;\n\
                padding: 20px;\n\
                border-radius: 5px;\n\
            }\n\
            .app-title {\n\
                text-align: center;\n\
                color: #777;\n\
            }\n\
            .login-form {\n\
                text-align: center;\n\
    			border: 2px solid white;\n\
				margin-top:30px;\n\
				margin-bottom:-10px;\n\
            }\n\
            .control-group {\n\
                margin-bottom: 10px;\n\
            }\n\
    		.div-title\n\
			{\n\
			 padding:0px;\n\
			 margin-left:-7.35cm;\n\
			 margin-bottom: 0.4cm;\n\
			 color :#999;\n\
			 font-weight:bold;\n\
			 align:center;\n\
			}\n\
            .login-field {\n\
                text-align: left;\n\
                background-color: #ECF0FA;\n\
                border: 2px solid #3498DB;\n\
                border-radius: 3px;\n\
                font-size: 16px;\n\
                font-weight: 200;\n\
                padding: 10px 30px;\n\
                width: 450px;\n\
                transition: border .5s;\n\
            }\n\
            .login-link {\n\
                font-size: 12px;\n\
                color: #3498DB;\n\
                margin-left: 4cm;\n\
            }\n\
            .alert {\n\
				font-size: 15px; \n\
				color: rgb(90,90,90);\n\
				text-align:left;\n\
				width: 450px;\n\
    		}\n\
			.button {\n\
			  font-size: 20px;\n\
			  text-align: auto;\n\
			  cursor: pointer;\n\
			  color: #ffffff;\n\
    		  background-color: #3498DB;\n\
			  border: none;\n\
			  border-radius: 3px;\n\
			  height:40px;\n\
			  width:120px;\n\
			  margin-top:10px;\n\
			  margin-left:3px;\n\
			}\n\
             .button:hover {background-color: #2f93d6}\n\
             .button:active {\n\
			  background-color: #2f93d6;\n\
			  transform: translateY(1px);\n\
			}\n\
            .button-group {\n\
				margin-left:250px;\n\
				margin-bottom:30px;\n\
				text-align: center;\n\
			}\n\
        </style>\n\
    </head> ";
    this->_configurePage =
	"<body>\n\
	<form action='action_page.php' method='post'>\n\
	<div  class='login'>\n\
	<div class='login-screen'>\n\
    	  <div class='app-title'>\n\
			<h2>HEY! Configuration</h2>\n\
				<center>\n\
				<div class='alert' >This page is for System Administrators only. If you are not, please leave and contact your System Administrators. Thank you.</div>\n\
	            </center>\n\
	        </div>\n\
	      <div>\n\
				<div class='login-form'>\n\
	            <div class='div-title'>Network configuration</div>\n\
					<div class='control-group'>\n\
	                    <input type='text' class='login-field' name='SSID' placeholder='WiFi SSID *' required>\n\
	                    <label class='login-field-icon fui-user' for='login-name'></label>\n\
	                </div>\n\
		            <div class='control-group'>\n\
	                    <input type='password' class='login-field' name='password' placeholder='WiFi Sercurity Key *' id='login-pass' required>\n\
	                    <label class='login-field-icon fui-lock' for='login-pass'></label>\n\
	            </div>\n\
	      </div>\n\
				<div class='login-form'>\n\
	                <div class='div-title' s> Jenkins configuration</div >\n\
    				<div class='control-group'>\n\
	                    <input type='text' name='txt_JenkinsURL' class='login-field' placeholder='Jenkins URL *' required>\n\
	            </div>\n\
	            <div class='control-group'>\n\
	                    <input type='text' name='txt_Project1' class='login-field' placeholder='Jenkins&rsquo;s JobName'>\n\
	            </div>\n\
				<div class='control-group'>\n\
	                    <input type='text' name='txt_Project2' class='login-field' placeholder='Jenkins&rsquo;s JobName'>\n\
				</div>\n\
	            <div class='control-group'>\n\
	                    <input type='text' name='txt_Project3' class='login-field' placeholder='Jenkins&rsquo;s JobName'>\n\
	            </div>\n\
				<div class='control-group'>\n\
						<input type='text' name='txt_Project4' class='login-field' placeholder='Jenkins&rsquo;s JobName'>\n\
			     </div>\n\
				 <div class='control-group'>\n\
	             <input type='text' name='txt_Project5' class='login-field' placeholder='Jenkins&rsquo;s JobName'>\n\
				 </div>\n\
            	 </div>\n\
	   </div>\n\
			<table class='button-group'>\n\
				<th>\n\
					<tr> \n\
						<th>	<button class='button' type='button'  onclick='self.close()'>Leave</button> </th>\n\
						<th>	<button class='button btn-primary btn-large btn-block' method='post'>Save</button> </th>\n\
					</tr>\n\
				</th>\n\
				</table>\n\
					<br></br>\n\
					<a class='login-link'  ><center>Copyright &copy; DEKLab</center></a>\n\
		</div>\n\
		</div>\n\
	</form>\n\
</body>";

	this->_successPage =
	"<body>\n\
	        <div class='login'>\n\
	            <div class='login-screen'>\n\
	                <div class='app-title'>\n\
	                   <h2 style='font-weight:bold'> Your HEY! is READY</h2>\n\
	                   <h3 align='center' > Be Happy Developers  &#128515;</h3>\n\
					</div>\n\
	                <div class='login-form'>\n\
						<br></br>\n\
	                    <br></br>\n\
	                    <br></br>\n\
                        <br></br>\n\
	                    <a class='login-link' ><center>Copyright &copy; DEKLab</center></a>\n\
	                </div>\n\
	            </div>\n\
	        </div>\n\
	    </body>";
}

ConfigurePage::~ConfigurePage()
{

}
