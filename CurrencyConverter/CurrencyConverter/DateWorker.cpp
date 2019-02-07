#include "stdafx.h"
#include <vector>
#include "DateWorker.h"

DateWorker::DateWorker(const CString& date, const char& separator, bool yearFirst) 
	: dateString(date), separator(separator), day(0), month(0), year(0), yearFirst(yearFirst)
{
	
}

int DateWorker::GetDay() {
	return this->day;
}

int DateWorker::GetMonth() {
	return this->month;
}

int DateWorker::GetYear() {
	return this->year;
}

void DateWorker::Split() {
	std::string buff{ "" };
	std::vector<std::string> v;
	
	for (int i = 0; i < dateString.GetLength(); ++i)
	{
		if (dateString.GetAt(i) != separator) buff += dateString.GetAt(i); else
		if (dateString.GetAt(i) == separator && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	if (v.size() == 3) {
		if (yearFirst) {
			this->day = std::stoi(v.at(2));
			this->month = std::stoi(v.at(1));
			this->year = std::stoi(v.at(0));
		}
		else {
			this->day = std::stoi(v.at(0));
			this->month = std::stoi(v.at(1));
			this->year = std::stoi(v.at(2));
		}
	}
}

CString DateWorker::GetFullDate(DateFormat format) {

	if (format == DateFormat::ddMMyyyy) {
		CString str((std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year) + ".").c_str());
		return str;
	}
	else if (format == DateFormat::yyyyMMdd) {
		CString str((std::to_string(year) + "." + std::to_string(month) + "." + std::to_string(day) + ".").c_str());
		return str;
	}

	return _T("");
}

