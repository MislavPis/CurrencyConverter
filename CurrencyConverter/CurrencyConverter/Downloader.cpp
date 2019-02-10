#include "stdafx.h"
#include "Downloader.h"

#define CURL_STATICLIB
#include "curl/curl.h"

#if defined _M_IX86
#ifdef _DEBUG
#	pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#	pragma comment(lib, "curl/libcurl_a.lib")
#endif
#endif

#if defined _M_X64
#ifdef _DEBUG
#	pragma comment(lib, "curl64/libcurl_a_debug.lib")
#else
#	pragma comment(lib, "curl64/libcurl_a.lib")
#endif
#endif

size_t AppendDataToStringCurlCallback(void *ptr, size_t size, size_t nmemb, void *vstring)
{
	std::string * pstring = (std::string*)vstring;
	pstring->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

std::string DownloadContent() {
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

	if (!contentFromUrl.empty()) {
		return contentFromUrl;
	}

	return "";
}