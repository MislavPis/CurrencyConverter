#include "stdafx.h"
#include "DateWorker.h"

CString Format(const CString& dateString) {
	int day = 0;
	int month = 0;
	int year = 0;

	const wchar_t separator = L'-';

	std::wstring buff = _T("");
	std::vector<std::wstring> splittedComponents;
	
	for (int i = 0; i < dateString.GetLength(); ++i)
	{
		if (dateString.GetAt(i) != separator) 
			buff += dateString.GetAt(i); 
		else if (dateString.GetAt(i) == separator && buff != _T(""))
		{ 
			splittedComponents.push_back(buff); buff = _T("");
		}
	}
	if (buff != _T("")) splittedComponents.push_back(buff);

	if (splittedComponents.size() == 3) {
		day = std::stoi(splittedComponents.at(2));
		month = std::stoi(splittedComponents.at(1));
		year = std::stoi(splittedComponents.at(0));
	}

	CString str((std::to_wstring(day) + _T(".") + std::to_wstring(month) + _T(".") + std::to_wstring(year) + _T(".")).c_str());
	return str;
}



