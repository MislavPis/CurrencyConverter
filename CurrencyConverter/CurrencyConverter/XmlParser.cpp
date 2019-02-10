#include "stdafx.h"
#include "XmlParser.h"
#include "pugiXML/pugixml.hpp"

std::pair< std::map<CString, float>, CString> CreateXmlFromString(const std::string& content){
	std::map<CString, float> currencyMap;
	CString date;

	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_string(content.c_str());

	if (result) {		
		pugi::xml_node cubeNode = document.child("gesmes:Envelope").child("Cube");
		pugi::xml_node childTime = cubeNode.child("Cube");
		date = childTime.attribute("time").value();

		for (pugi::xml_node childCurrency = childTime.child("Cube"); childCurrency; childCurrency = childCurrency.next_sibling("Cube"))
		{
			currencyMap.insert(std::pair<CString, float>(childCurrency.attribute("currency").value(), std::stof(childCurrency.attribute("rate").value())));
		}
	}
	
	return std::pair< std::map<CString, float>, CString>{ currencyMap, date };
}