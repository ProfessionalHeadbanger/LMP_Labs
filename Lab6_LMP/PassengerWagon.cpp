#include "PassengerWagon.h"

PassengerWagon::PassengerWagon(unsigned int number, unsigned int year, std::string type, unsigned int seats, bool shower):Wagon(number, year), type(type), seats(seats), shower(shower) {}

std::string PassengerWagon::Get_type()
{
	return type;
}

unsigned int PassengerWagon::Get_Seats()
{
	return seats;
}

bool PassengerWagon::Get_Shower()
{
	return shower;
}

void PassengerWagon::Set_type(std::string val)
{
	type = val;
}

void PassengerWagon::Set_seats(unsigned int val)
{
	seats = val;
}

void PassengerWagon::Set_shower(bool val)
{
	shower = val;
}

std::string PassengerWagon::toString()
{
	std::string str = "Пассажирский вагон " + Wagon::toString() + ", " + type + ", кол-во мест - " + std::to_string(seats);
	if (shower)
	{
		str += ", душ - есть";
	}
	else
	{
		str += ", душ - нет";
	}
	return str;
}
