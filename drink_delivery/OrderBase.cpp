#include "OrderBase.h"

OrderBase::OrderBase(std::string filename, std::vector <int> id, std::vector <std::string> category, 
	std::vector <std::string> product)
{
	m_filename = filename;
	m_id = id;
	m_category = category;
	m_product = product;
}