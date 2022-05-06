#pragma once

#include "IOrder.h"

#include <vector>
#include <string>

class OrderBase : public IOrder
{
protected:
	std::string m_filename;
	std::vector <int> m_id;
	std::vector <std::string> m_category;
	std::vector <std::string> m_product;

public:
	OrderBase(std::string filename, std::vector <int> id, std::vector <std::string> category, std::vector <std::string> product);
};