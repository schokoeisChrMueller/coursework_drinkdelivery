#pragma once

#include "OrderBase.h"

#include <vector>
#include <string>

class RentalOrder : public OrderBase
{
	std::vector <double> m_prizeperday;

public:
	RentalOrder(std::string filename, std::vector <int> id, std::vector <std::string> category, std::vector <std::string> product, 
		std::vector <double> prizeperday);
	void set_filename(std::string filename) override { m_filename = filename; }
	void read_file () override;
	int show_products () override;
	double prize(int id, int amount, int duration) override;
	std::string get_product(int id) { return m_product.at(id); };
	double prizeperliter(int id) override { return 1.0; };
};
