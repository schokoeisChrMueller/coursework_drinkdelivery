#include "Delivery.h"

#include <iostream>
#include <fstream>
#include <cmath>

inline std::istream& skipline(std::istream& in)
{
	return in.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}

Delivery::Delivery(std::string filename, std::vector <int> id, std::vector <std::string> category, 
	std::vector <std::string> destination, std::vector <int> coord_n_s, std::vector <int> coord_w_e, std::vector <double> prizeperkm)
{
	m_filename = filename;
	m_id = id;
	m_category = category;
	m_destination = destination;
	m_coord_n_s = coord_n_s;
	m_coord_w_e = coord_w_e;
	m_prizeperkm = prizeperkm;
}

void Delivery::read_file()
{
	int id;
	std::string category;
	std::string destination;
	int coord_n_s;
	int coord_w_e;
	double prizeperkm;

	std::ifstream file1_(m_filename);

	if (file1_.is_open())
	{
		while (file1_ >> skipline >> id >> category >> destination >> coord_n_s >> coord_w_e >> prizeperkm)
		{
			m_id.push_back(id);
			m_category.push_back(category);
			m_destination.push_back(destination);
			m_coord_n_s.push_back(coord_n_s);
			m_coord_w_e.push_back(coord_w_e);
			m_prizeperkm.push_back(prizeperkm);
		}

		file1_.close();
	}
	else
		std::cout << "file is not open" << std::endl;
}

int Delivery::show_destinations()
{
	int select;
	std::vector <int> temp;
	int counter = 0;

	std::cout << "ID" << "\t" << "location" << "\t\t" << "prize per kilometer" << std::endl;

	for (int i = 0; i < m_category.size(); i++)
	{
		if (m_category.at(i) == "destination")
		{
			temp.push_back(i);
			std::cout << m_id.at(i) << "\t" << m_destination.at(i) << "\t\t" << m_prizeperkm.at(i) << std::endl;
		}
	}

	std::cout << "\nPlease select the desired destination by entering the corresponding ID number" << std::endl;
	std::cout << "Then the fastest route will be calculated from all possible stocks" << std::endl;

	while (counter == 0)
	{
		std::cin >> select;

		for (int i = 0; i < temp.size(); i++)
		{
			if (temp.at(i) == select)
			{
				counter++;
			}
		}
	}

	return select;
}

double Delivery::distance(int id)
{
	double distance = 0;
	double temp = 0;
	int counter = 0;

	for (int i = 0; i < m_id.size(); i++)
	{
		if (m_category.at(i) == "stock")
		{
			int dx = m_coord_n_s.at(i) - m_coord_n_s.at(id);
			int dy = m_coord_w_e.at(i) - m_coord_w_e.at(id);

			temp = (1.0 / 1000) * sqrt(dx * dx + dy * dy);
		}

		if (counter == 0)
			distance = temp;

		if (temp < distance)
			distance = temp;

		counter++;
	}
	
	return distance;
}

double Delivery::delivery_prize(int id, double distance)
{
	double prize = 0;
	
	prize = distance * m_prizeperkm.at(id);
	prize = (double)((int)(prize * 100)) / 100;

	return prize;
}



