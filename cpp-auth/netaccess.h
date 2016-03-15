#ifndef NETACCESS_AUTH
#define NETACCESS_AUTH

#define TEST_URL "http://www.bing.com"
#define NETACCESS_URL "http://netaccess1.iitm.ac.in:1000"
#define REGEX_MAGIC "\"magic\" value=\"(?<cap>.+?)\""
#define REGEX_KEEPALIVE "location.href=\"(?<cap>.+keepalive.+?)\""
#define REGEX_LOGOUT "location.href=\"(?<cap>.+logout.+?)\""

#include "curl/curl.h"
#include "cstring"
#include "iostream"
#include "vector"
#include "map"

typedef std::map<std::string, std::string> UrlParams;
using namespace std;

class netaccess
{
	bool _LoggedIn;
public:
	string Magic;
	string InitUri;
	string KeepaliveUrl;
	string LogoutUrl;
	netaccess(string username, string password);
	~netaccess();
	bool LogOut();
};

#endif