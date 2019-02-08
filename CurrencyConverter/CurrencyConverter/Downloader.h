#pragma once
#include <string>

class Downloader {
private:
	std::string content;

public:
	Downloader();
	~Downloader();

	void DownloadContent();
	std::string& GetContent();
	bool IsContentDownloaded();
};