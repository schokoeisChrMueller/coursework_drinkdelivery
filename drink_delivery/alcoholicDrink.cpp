#include "alcoholicDrink.h"

#include <iostream>
#include <fstream>


inline std::istream& skipline(std::istream& in)
{
	return in.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}


alcoholicDrink::alcoholicDrink(std::string filename,  std::vector <int> id, std::vector <std::string> category, 
	std::vector <std::string> product, std::vector <double> prize, std::vector <double> liter, std::vector <int> alcoholcontent)
	: OrderBase(filename, id, category, product)
{
	m_prize = prize;
	m_liter = liter;
	m_alcoholcontent = alcoholcontent;
}

void alcoholicDrink::read_file()
{
	int id;
	std::string category;
	std::string product;
	double prize;
	double liter;
	int alcoholcontent;

	std::ifstream file1_(m_filename);

	if (file1_.is_open())
	{
		while (file1_ >> skipline >> id >> category >> product >> prize >> liter >> alcoholcontent)
		{
			m_id.push_back(id);
			m_category.push_back(category);
			m_product.push_back(product);
			m_prize.push_back(prize);
			m_liter.push_back(liter);
			m_alcoholcontent.push_back(alcoholcontent);
		}

		file1_.close();
	}
	else
		std::cout << "file is not open" << std::endl;
}

int alcoholicDrink::show_products()
{
	int input = 0;
	std::string category = "";
	int select = 0;
	std::vector <int> temp;
	int counter = 0;

	std::cout << "Please select the category of non-alcoholic drinks." << std::endl;

	std::cout << "1\tbeer" << std::endl;
	std::cout << "2\twine" << std::endl;
	std::cout << "3\tliquor" << std::endl;

	while (counter == 0)
	{
		std::cin >> input;

		switch (input)
		{
		case 1:
			category = "beer";
			counter = 1;
			break;

		case 2:
			category = "wine";
			counter = 1;
			break;

		case 3:
			category = "liquor";
			counter = 1;
			break;

		default:
			counter = 0;
			break;
		}
	}

	std::cout << "\x1B[2J\x1B[H"; // clear window

	std::cout << "ID" << "\t" << "category" << "\t" << "product" << "\t\t" << "prize" << "\t" << "liter"
		<< "\t" << "prize per liter" << std::endl;

	for (int i = 0; i < m_category.size(); i++)
	{
		if (m_category.at(i) == category)
		{
			temp.push_back(i);
			std::cout << m_id.at(i) << "\t" << m_category.at(i) << "\t\t" << m_product.at(i) << "\t" << m_prize.at(i)
				<< "\t" << m_liter.at(i) << "\t" << prizeperliter(i) << std::endl;
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

double alcoholicDrink::prize (int id, int amount, int duration)
{
	double sumprize = 0.0;
	double alcohol_tax = 0.0;

	if (m_alcoholcontent.at(id) <= 15)
		alcohol_tax = 1.2;
	if (m_alcoholcontent.at(id) > 15)
		alcohol_tax = 1.45;

	sumprize = m_prize.at(id) * amount * alcohol_tax;
	sumprize = (double)((int)(sumprize * 100)) / 100;

	return sumprize;
}

double alcoholicDrink::prizeperliter(int id)
{
	double prizeperliter = 0.0;

	prizeperliter = m_prize.at(id) / m_liter.at(id);
	prizeperliter = (double)((int)(prizeperliter * 100)) / 100;

	return prizeperliter;
}
