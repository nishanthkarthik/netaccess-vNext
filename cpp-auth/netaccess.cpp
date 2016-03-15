#include "netaccess.h"

string params_string(UrlParams const &params)
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

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, TEST_URL);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
			
	}	

	auth_body = params_string({
		{"",},
		{"",},
		{"",},
		{"",}
	});
}

netaccess::~netaccess()
{
	cout<<"to be implemented";
}