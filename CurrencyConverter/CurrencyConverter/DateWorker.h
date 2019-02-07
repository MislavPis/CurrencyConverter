#pragma once

#include <string>

class DateWorker {
private:
	int day, month, year;
	CString dateString;
	const char& separator;
	bool yearFirst;

public:
	enum DateFormat{yyyyMMdd, ddMMyyyy};

public:
	DateWorker(const CString&, const char&, bool = true);

	int GetDay();
	int GetMonth();
	int GetYear();

	void Split();
	
	CString GetFullDate(DateFormat);
};