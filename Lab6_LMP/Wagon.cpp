#include "Wagon.h"

Wagon::Wagon(unsigned int number, unsigned int year):number(number), year(year) {}

Wagon::~Wagon(){}

unsigned int Wagon::Get_number()
{
	return number;
}

unsigned int Wagon::Get_year()
{
	return year;
}

void Wagon::Set_number(unsigned int val)
{
	number = val;
}

void Wagon::Set_year(unsigned int val)
{
	year = val;
}

int Wagon::comp(const Wagon& object)
{
	int result = 1;
	if (year < object.year)
	{
		result = -1;
	}
	else if (number == object.number)
	{
		result = 0;
	}
	return result;
}

std::string Wagon::toString()
{
	return "№" + std::to_string(number) + ": год выпуска - " + std::to_string(year);
}
