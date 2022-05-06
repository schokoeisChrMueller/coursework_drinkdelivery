#include "Time_.h"

#include <iostream>
#include <ctime>
#include <iomanip>

Time_::Time_(int hour = 0, int minute = 0, int second = 0)
{
	m_hour = hour;
	m_minute = minute;
	m_second = second;
}

std::ostream& operator << (std::ostream& out, const Time_& c)
{
	out
		<< std::setfill('0') << std::setw(2) << c.m_hour << ":"
		<< std::setfill('0') << std::setw(2) << c.m_minute << ":"
		<< std::setfill('0') << std::setw(2) << c.m_second << std::endl;

	return out;
}

Time_ operator - (const Time_& c1, const Time_& c2)
{
	Time_ result;

	result.m_hour = c1.m_hour - c2.m_hour;
	result.m_minute = c1.m_minute - c2.m_minute;
	result.m_second = c1.m_second - c2.m_second;

	if (result.m_hour < 0)
	{
		result.m_hour = result.m_hour + 24;
	}

	if (result.m_minute < 0)
	{
		result.m_minute = result.m_minute + 60;
		result.m_hour = result.m_hour - 1;
		if (result.m_hour < 0)
		{
			result.m_hour = result.m_hour + 24;
		}
	}

	if (result.m_second < 0)
	{
		result.m_second = result.m_second + 60;
		result.m_minute = result.m_minute - 1;
		if (result.m_minute < 0)
		{
			result.m_minute = result.m_minute + 60;
			result.m_hour = result.m_hour - 1;
			if (result.m_hour < 0)
			{
				result.m_hour = result.m_hour + 24;
			}
		}
	}

	return result;
}

void Time_::current_time()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	m_hour = newtime.tm_hour;
	m_minute = newtime.tm_min;
	m_second = newtime.tm_sec;
}
	
Time_ Time_::arrival_time (double distance)
{
	int m_hour_arrival = m_hour;
	int m_minute_arrival = m_minute;
	int m_second_arrival = m_second;

	double total_minutes = 0;
	int velocity = 25; // [km/h]
	int preparation_time = 30; // [min]

	total_minutes = (distance / velocity) * 60.0 + preparation_time;
	int total_minutes_ = (int)round(total_minutes);

	m_minute_arrival += total_minutes_;

	if (m_minute_arrival >= 60)
	{
		m_minute_arrival = m_minute_arrival - 60;
		m_hour_arrival++;
		if (m_hour_arrival >= 24)
		{
			m_hour_arrival = m_hour_arrival - 24;
		}
	}

	Time_ arrival_time(m_hour_arrival, m_minute_arrival, m_second_arrival);

	return arrival_time;
}