#include "IOrder.h"
#include "Time_.h"
#include "Delivery.h"

#include "OrderBase.h"
#include "RentalOrder.h"
#include "non_alcoholicDrink.h"
#include "alcoholicDrink.h"
#include "FinalOrder.h"

#include <iostream>
#include <vector>


// prototypes
int get_amount();
int get_duration();

void clear_window();
int start_window();
int main_menu();


// global variables
std::string fill_filename;
std::vector <int> fill_int;
std::vector <double> fill_double;
std::vector <std::string> fill_string;

non_alcoholicDrink non_alc_drinks(fill_filename, fill_int, fill_string, fill_string, fill_double, fill_double);
alcoholicDrink alc_drinks(fill_filename, fill_int, fill_string, fill_string, fill_double, fill_double, fill_int);
RentalOrder rentals(fill_filename, fill_int, fill_string, fill_string, fill_double);
FinalOrder final_order(fill_filename, fill_int, fill_string, fill_int, fill_int, fill_double);
Delivery destinations(fill_filename, fill_int, fill_string, fill_string, fill_int, fill_int, fill_double);

int main()
{
	std::string filename = "";

	if (start_window() == 1)
	{
		filename = "all_non_alcoholic_drinks.txt";
		non_alc_drinks.set_filename(filename);
		non_alc_drinks.read_file();

		filename = "all_alcoholic_drinks.txt";
		alc_drinks.set_filename(filename);
		alc_drinks.read_file();

		filename = "all_rentals.txt";
		rentals.set_filename(filename);
		rentals.read_file();

		filename = "all_destinations.txt";
		destinations.set_filename(filename);
		destinations.read_file();

		clear_window();
	}

	int temp = 0;

	while (temp != 2)
	{
		temp = main_menu();
		clear_window();
	}

	int id = 0;
	double distance = 0.0;
	double delivery_prize = 0.0;

	id = destinations.show_destinations();
	distance = destinations.distance(id);
	delivery_prize = destinations.delivery_prize(id, distance);

	Time_ now (0, 0, 0);
	now.current_time();
	Time_ arrival = now.arrival_time (distance);
	Time_ delivery_time = arrival - now;

	clear_window();

	std::cout << "Delivery overview:" << std::endl;

	std::cout << "\nCurrent time: " << now << std::endl;
	std::cout << "Arrival time: " << arrival << std::endl;
	std::cout << "Delivery time: " << delivery_time << std::endl;
	std::cout << "Delivery prize: " << delivery_prize << " [EUR]" << std::endl;

	std::cout << final_order << std::endl;
	
	std::cout << "\n\nThe invoice with all the information is available as a text file 'invoice_template.txt'" << std::endl;

	filename = "invoice_template.txt";

	final_order.set_filename(filename);
	final_order.write_file(delivery_prize);

	return 0;
}


//functions

int get_amount()
{
	int amount = 0;

	std::cout << "\nHow often do you want to add the product to the order?" << std::endl;

	std::cin >> amount;

	return amount;
}

int get_duration()
{
	int duration = 0;

	std::cout << "\nHow many days to you want to rent the product?" << std::endl;

	std::cin >> duration;

	return duration;
}


// menu_functions

void clear_window()
{
	std::cout << "\x1B[2J\x1B[H";
}

int start_window()
{
	int input = 0;

	std::cout << "X X X X X X X X X X X X X X X X X X X X X X X X X X X X X" << std::endl;
	std::cout << "X\t\t\t\t\t\t\tX" << std::endl;
	std::cout << "X   Welcome to 'drink + delivery service Mueller.AG'!   X" << std::endl;
	std::cout << "X\t\t\t\t\t\t\tX" << std::endl;
	std::cout << "X X X X X X X X X X X X X X X X X X X X X X X X X X X X X" << std::endl;
	std::cout << "\n" << std::endl;
	std::cout << "Please press 1 to place a order" << std::endl;
	std::cin >> input;

	while (input != 1)
	{
		std::cout << "Initialization failed. Please press 1 to place a order" << std::endl;
		std::cin >> input;
	}

	return input;
}

int main_menu()
{
	int ending;
	int input = 0;
	int casenumber = 0;
	int id = 0;
	int amount = 0;
	int duration = 0;
	double sumprize = 0.0;
	std::string product;
	int counter = 0;

	IOrder* o = nullptr;

	std::cout << "Please select the desired action" << std::endl;

	std::cout << "1\tBuy non-alcoholic drinks" << std::endl;
	std::cout << "2\tBuy alcoholic drinks" << std::endl;
	std::cout << "3\tRent party equipment" << std::endl;

	std::cin >> input;

	switch (input)
	{
	case 1:
		clear_window();
		o = &non_alc_drinks;
		break;

	case 2:
		clear_window();
		o = &alc_drinks;
		break;

	case 3:
		clear_window();	
		o = &rentals;
		casenumber = 3;
		break;

	default:
		clear_window();
		main_menu();
		break;
	}

	id = o->show_products();
	amount = get_amount();
	if (casenumber == 3) { duration = get_duration(); }
	sumprize = o->prize(id, amount, duration);
	product = o->get_product(id);
	final_order.set_order(product, amount, duration, sumprize);

	std::cout << "\nDo you want to make another order?" << std::endl;
	std::cout << "1\tYes" << "\n" << "2\tNo" << std::endl;

	while (counter == 0)
	{
		std::cin >> ending;

		if (ending == 1 || ending == 2)
		{
			counter++;
		}
	}

	return ending;
}
