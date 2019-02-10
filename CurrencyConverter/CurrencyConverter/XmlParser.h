#pragma once

class XmlParser {
private:
	std::map<CString, float> currencyMap;
	CString time;

public:
	XmlParser();
	~XmlParser();

	void CreateXmlFromString(const std::string&);
	std::map<CString, float> GetParsedData();
	bool IsDataParsed();
	CString GetTime();
};