#pragma once

#include <iostream>

class Time_
{
protected:
	int m_hour;
	int m_minute;
	int m_second;

public:
	Time_(int hour, int minute, int second);
	void current_time();
	Time_ arrival_time (double distance);
	
	friend std::ostream& operator << (std::ostream& out, const Time_& c);
	friend Time_ operator - (const Time_ &c1, const Time_ &c2);
};
