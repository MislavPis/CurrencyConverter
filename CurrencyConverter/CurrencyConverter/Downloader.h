#pragma once
#include <string>

class Downloader {
private:
	std::string content;

public:
	Downloader();
	std::string& DownloadContent();
	std::string GetContent();
	bool IsContentDownloaded();
};