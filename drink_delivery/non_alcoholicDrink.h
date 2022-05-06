#pragma once

#include "OrderBase.h"

#include <vector>
#include <string>

class non_alcoholicDrink : public OrderBase
{
	std::vector <double> m_prize;
	std::vector <double> m_liter;

public:
	non_alcoholicDrink (std::string filename, std::vector <int> id, std::vector <std::string> category, 
		std::vector <std::string> product, std::vector <double> prize, std::vector <double> liter);
	void set_filename(std::string filename) override { m_filename = filename; }
	void read_file () override;
	int show_products() override;
	double prize(int id, int amount, int duration) override;
	std::string get_product(int id) { return m_product.at(id); };
	double prizeperliter(int id) override;
};