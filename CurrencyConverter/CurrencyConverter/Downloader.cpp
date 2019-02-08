#include "stdafx.h"
#include "Downloader.h"

#define CURL_STATICLIB
#include "curl/curl.h"

#ifdef _DEBUG
#	pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#	pragma comment(lib, "curl/libcurl_a.lib")
#endif

size_t AppendDataToStringCurlCallback(void *ptr, size_t size, size_t nmemb, void *vstring)
{
	std::string * pstring = (std::string*)vstring;
	pstring->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

Downloader::Downloader() 
	: content("")
{

}

Downloader::~Downloader()
{
}

void Downloader::DownloadContent() {
	std::string contentFromUrl;

	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = nullptr;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contentFromUrl);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AppendDataToStringCurlCallback);
		CURLcode code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	this->content = contentFromUrl;
}

bool Downloader::IsContentDownloaded() {
	return this->content.empty() ? false : true;
}

std::string& Downloader::GetContent() {
	return this->content;
}