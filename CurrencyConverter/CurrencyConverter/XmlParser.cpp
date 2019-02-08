#include "stdafx.h"
#include "XmlParser.h"
#include "pugiXML/pugixml.hpp"

#include <string>

XmlParser::XmlParser()
	: currencyMap(), time("")
{

}

XmlParser::~XmlParser()
{
}

void XmlParser::CreateXmlFromString(const std::string& content){
	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_string(content.c_str());

	if (result) {		
		pugi::xml_node cubeNode = document.child("gesmes:Envelope").child("Cube");
		pugi::xml_node childTime = cubeNode.child("Cube");
		this->time = childTime.attribute("time").value();

		for (pugi::xml_node childCurrency = childTime.child("Cube"); childCurrency; childCurrency = childCurrency.next_sibling("Cube"))
		{
			currencyMap.insert(std::pair<CString, float>(childCurrency.attribute("currency").value(), std::stof(childCurrency.attribute("rate").value())));
		}
	}
}

std::map<CString, float> XmlParser::GetParsedData() {
	return this->currencyMap;
}

bool XmlParser::IsDataParsed() {
	return this->currencyMap.empty() ? false : true;
}

CString XmlParser::GetTime() {
	return this->time;
}