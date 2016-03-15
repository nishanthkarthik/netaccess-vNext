#ifndef NETACCESS_AUTH
#define NETACCESS_AUTH

#include "curl/curl.h"
#include "cstring"

using namespace std;

class netaccess
{
	public string Magic;
	public string InitUri;
	public string KeepaliveUrl;
	public string LogoutUrl;
	private bool _LoggedIn;
public:
	netaccess(string username, string password);
	~netaccess();
	bool LogOut();
};

#endif