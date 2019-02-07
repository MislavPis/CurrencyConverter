#pragma once

#include <string>
#include <map>

class XmlParser {
private:
	std::map<CString, float> currencyMap;
	CString time;

public:
	XmlParser();
	void CreateXmlFromString(const std::string&);
	std::map<CString, float> GetParsedData();
	bool IsDataParsed();
	CString GetTime();
};