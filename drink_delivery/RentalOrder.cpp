#include "RentalOrder.h"

#include <iostream>
#include <fstream>

inline std::istream& skipline(std::istream& in)
{
	return in.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}

RentalOrder::RentalOrder (std::string filename, std::vector <int> id, std::vector <std::string> category, 
	std::vector <std::string> product, std::vector <double> prizeperday) 
	: OrderBase(filename, id, category, product)
{
	m_prizeperday = prizeperday;
}

void RentalOrder::read_file ()
{
	int id;
	std::string category;
	std::string product;
	double prizeperday;

	std::ifstream file1_(m_filename);

	if (file1_.is_open())
	{
		while (file1_ >> skipline >> id >> category >> product >> prizeperday)
		{
			m_id.push_back(id);
			m_category.push_back(category);
			m_product.push_back(product);
			m_prizeperday.push_back(prizeperday);
		}

		file1_.close();
	}
	else
		std::cout << "file is not open" << std::endl;
}

int RentalOrder::show_products()
{
	int input = 0;
	std::string category = "";
	int select = 0;
	std::vector <int> temp;
	int counter = 0;

	std::cout << "Please select the desired party equipment to rent." << std::endl;

	std::cout << "1\tbeer bench" << std::endl;
	std::cout << "2\tglass sets" << std::endl;

	while (counter == 0)
	{
		std::cin >> input;

		switch (input)
		{
		case 1:
			category = "beer_bench";
			counter = 1;
			break;

		case 2:
			category = "glass_set";
			counter = 1;
			break;

		default:
			counter = 0;
			break;
		}
	}

	std::cout << "\x1B[2J\x1B[H"; // clear window

	std::cout << "ID" << "\t" << "category" << "\t" << "product" << "\t\t" << "prize per day" << std::endl;

	for (int i = 0; i < m_category.size(); i++)
	{
		if (m_category.at(i) == category)
		{
			temp.push_back(i);
			std::cout << m_id.at(i) << "\t" << m_category.at(i) << "\t" << m_product.at(i) << "\t" << m_prizeperday.at(i) << std::endl;
		}
	}

	std::cout << "\nPlease select the desired product by entering the corresponding ID number" << std::endl;

	counter = 0;

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

double RentalOrder::prize(int id, int amount, int duration)
{
	double sumprize = 0.0;
	double basic_charge = 4.5;

	sumprize = m_prizeperday.at(id) * amount * duration + basic_charge;
	sumprize = (double)((int)(sumprize * 100)) / 100;

	return sumprize;
}
