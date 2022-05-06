#pragma once

#include <vector>
#include <string>

class Delivery
{
	std::string m_filename;
	std::vector <int> m_id;
	std::vector <std::string> m_category;
	std::vector <std::string> m_destination;
	std::vector <int> m_coord_n_s;
	std::vector <int> m_coord_w_e;
	std::vector <double> m_prizeperkm;

public:
	Delivery(std::string filename, std::vector <int> id, std::vector <std::string> category, std::vector <std::string> destination,
		std::vector <int> coord_n_s, std::vector <int> coord_w_e, std::vector <double> prizeperkm);
	void set_filename(std::string filename) { m_filename = filename; }
	void read_file();
	int show_destinations();
	double distance(int id);
	double delivery_prize(int id, double distance);
};