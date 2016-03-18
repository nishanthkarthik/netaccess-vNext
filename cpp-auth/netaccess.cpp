#include "netaccess.h"

int netaccess::errorcheck(CURLcode result)
{
	if (result != CURLE_OK)
	{
		cerr<<"> "<<curl_easy_strerror(result)<<endl;
		return(0);
	}
	return 1;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string netaccess::params_string(UrlParams const &params)
{
	//http://stackoverflow.com/questions/19978947/libcurl-c-adding-http-get-parameters
	if (params.empty()) 
		return "";
	UrlParams::const_iterator pb = params.cbegin(), pe= params.cend();
	std::string data= pb-> first+ "="+ pb-> second;
	++pb;
	if(pb == pe) 
		return data;
	for(; pb!= pe; ++ pb)
		data+= "&"+ pb-> first+ "="+ pb-> second;
	return data;
}

netaccess::netaccess(string username, string password)
{
	CURL* curl;
	CURLcode result;
	string contentbuffer;
	_LoggedIn = false;
	curl = curl_easy_init();

	if (curl)
	{
		//curl set url, enable redirect
		curl_easy_setopt(curl, CURLOPT_URL, TEST_URL);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		//curl set content buffer
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contentbuffer);

		result = curl_easy_perform(curl);
		cout<<contentbuffer;
		if (!errorcheck(result))
			return;

		char* redirecturl;
		curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &redirecturl);
		if (!string(redirecturl).find("fgtauth"))
			return;
		InitUri = string(redirecturl);
		

	}	

	string auth_body = params_string({
		{"",""},
		{"",""},
		{"",""},
		{"",""}
	});
}

netaccess::~netaccess()
{
	cout<<"to be implemented";
}