#pragma once

#include <string>

class  IOrder
{

public:
	virtual void set_filename(std::string filename) = 0;
	virtual void read_file() = 0;
	virtual int show_products() = 0;
	virtual double prize (int id, int amount, int duration) = 0;
	virtual std::string get_product(int id) = 0;
	virtual double prizeperliter(int id) = 0;
};
