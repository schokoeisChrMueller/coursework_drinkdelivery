#include "FinalOrder.h"
#include "Time_.h"

#include <iostream>
#include <fstream>
#include <iomanip>

FinalOrder::FinalOrder(std::string filename, std::vector <int> pos, std::vector <std::string> product, std::vector <int> amount, 
	std::vector <int> duration, std::vector <double> totalprize)
{
	m_filename = filename;
	m_pos = pos;
	m_product = product;
	m_amount = amount;
	m_duration = duration;
	m_totalprize = totalprize;
}

std::ostream& operator << (std::ostream& out, const FinalOrder& c)
{
	out
		<< "\nPos" << "\t" << "product" << "\t\t" << "amount" << "\t" << "duration" << "\t" << "prize" << std::endl;

		for (int i = 0; i < c.m_pos.size(); i++)
		{
			std::cout << c.m_pos.at(i) << "\t" << c.m_product.at(i) << "\t" << c.m_amount.at(i) 
				<< "\t" << c.m_duration.at(i) << " [days]" << "\t" << c.m_totalprize.at(i) << " [EUR]" << std::endl;
		}

		double temp = 0;

		for (int i = 0; i < c.m_totalprize.size(); i++)
		{
			temp = temp + c.m_totalprize.at(i);
		}

		std::cout << "\n\n" << "Summed prize: " << temp << " [EUR]" << std::endl;

	return out;
}

void FinalOrder::write_file(double delivery_prize)
{
	std::fstream file1_;

	file1_.open(m_filename, std::ios::out);

	if (file1_.is_open())
	{
		file1_ << "Invoice for ordering drinks from 'drink + delivery service Mueller.AG'" << "\n" << std::endl;

		Time_ current_time(0, 0, 0);
		current_time.current_time();

		file1_ << "Current time: " << current_time << std::endl;

		file1_ << "\nPos" << "\t" << "product" << "\t\t" << "amount" << "\t" << "duration" << "\t" << "prize" << std::endl;

		for (int i = 0; i < m_pos.size(); i++)
		{
			file1_ << m_pos.at(i) << "\t" << m_product.at(i) << "\t" << m_amount.at(i) << "\t" << m_duration.at(i) << " [days]" 
				<< "\t" << m_totalprize.at(i) << " [EUR]" << std::endl;
		}

		file1_.close();
	}

	double temp = 0;

	for (int i = 0; i < m_totalprize.size(); i++)
	{
		temp = temp + m_totalprize.at(i);
	}

	file1_.open(m_filename, std::ios::app);

	if (file1_.is_open())
	{
		file1_ << "\n\n" << "+ Summed prize: " << temp << " [EUR]" << std::endl;
		file1_ << "+ Delivery prize: " << delivery_prize << " [EUR]" << std::endl;
		file1_ << "\n" << "= Total prize: " << temp + delivery_prize << " [EUR]" << std::endl;
		file1_.close();
	}
}

void FinalOrder::set_order(std::string product, int amount, int duration, double prize)
{
	m_pos.push_back(m_pos.size() + 1);
	m_product.push_back(product);
	m_amount.push_back(amount);
	m_duration.push_back(duration);
	m_totalprize.push_back(prize);
}