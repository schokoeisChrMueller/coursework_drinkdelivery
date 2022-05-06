#pragma once

#include "IOrder.h"

#include <vector>
#include <string>

class FinalOrder : public IOrder
{
	std::string m_filename;
	std::vector <int> m_pos;
	std::vector <std::string> m_product;
	std::vector <int> m_amount;
	std::vector <int> m_duration;
	std::vector <double> m_totalprize;

public:
	FinalOrder(std::string filename, std::vector <int> pos, std::vector <std::string> product, std::vector <int> amount,
		std::vector <int> duration, std::vector <double> totalprize);
	void set_filename(std::string filename) override { m_filename = filename; }
	void read_file() override {};
	int show_products () override { return 0; };
	double prize(int id, int amount, int duration) override { return 0.0; };
	std::string get_product(int id) { return m_product.at(id); };
	double prizeperliter(int id) override { return 0.0; };

	void set_order (std::string product, int amount, int duration, double prize);
	void write_file(double delivery_prize);

	friend std::ostream& operator << (std::ostream& out, const FinalOrder& c);
};

