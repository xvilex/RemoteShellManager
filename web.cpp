#include "web.h"

string tmp = "";

curlWeb cWeb;

curlWeb::curlWeb() {
	curl = curl_easy_init(); // init curl
	result = "";
}

curlWeb::~curlWeb() {
	curl_easy_cleanup(curl); // clean curl
}

/*
 ptr points to the delivered data, and the size of that data is nmemb; size is always 1.
 https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
*/

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *unused) {
	char *res = new char[nmemb + 1];
	memcpy_s(res, nmemb, ptr, nmemb);
	res[nmemb] = '\0';
	tmp = string(res);
	delete[] res;

	return CURLE_OK;  // This will return CURLE_OK.
}

void curlWeb::SetURL(const string& url){
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
}

void curlWeb::SendRequest()
{
	curl_easy_perform(curl); // Send request
}

string curlWeb::GetResult()
{
	result = tmp;
	return result;
}