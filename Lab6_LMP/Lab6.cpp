#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Depot.h"
#include "PassengerWagon.h"
#include "FreightWagon.h"

using namespace std;

void init(Depot& depot, fstream& file)
{
	char t;
	unsigned int tonnage;
	string type;
	while (file >> t)
	{
		unsigned int number, year;
		file >> number >> year;
		if (t == 'P')
		{
			string type, is_shower;
			unsigned int seats;
			bool shower;
			file >> type >> seats >> is_shower;
			if (is_shower == "yes")
			{
				shower = true;
			}
			else
			{
				shower = false;
			}
			PassengerWagon pWg = PassengerWagon(number, year, type, seats, shower);
			depot.add_by_order(move(make_unique<PassengerWagon>(pWg)));
		}
		else
		{
			string type;
			unsigned int tonnage;
			file >> type >> tonnage;
			FreightWagon fWg = FreightWagon(number, year, tonnage, FreightWagon::str_to_type(type));
			depot.add_by_order(move(make_unique<FreightWagon>(fWg)));
		}
	}
	file.close();
}

int task(Depot& depot)
{
	wg_ptr::iterator luxe_bg = depot.Get_begin();
	int max_year;
	int cur_year = 0;
	int count = 0;
	int count_max = 0;
	while (luxe_bg != depot.Get_end())
	{
		PassengerWagon* t = dynamic_cast<PassengerWagon*>(luxe_bg->get());
		if (t && t->Get_type() == "люкс")
		{
			if (cur_year != t->Get_year())
			{
				cur_year = t->Get_year();
				if (count > count_max)
				{
					count_max = count;
					max_year = cur_year;
				}
				count = 1;
			}
			else
			{
				count++;
			}
		}
		luxe_bg++;
	}
	return max_year;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fstream file("input.txt");
	Depot depot("Voronezh 1");
	init(depot, file);
	cout << depot << endl;
	cout << "Год, в который было выпущено больше всего вагонов типа \"люкс\" - " << task(depot);
}
