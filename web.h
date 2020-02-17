#pragma once
#include <string>
#include "curl/curl.h"

using namespace std;

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *unused); // Look at cpp file

class curlWeb {
private:
	CURL *curl;
	string url;
	string result;
public:
	curlWeb();
	~curlWeb();

	void SetURL(const string& url);
	void SendRequest();
	string GetResult(); 
};

extern curlWeb cWeb;