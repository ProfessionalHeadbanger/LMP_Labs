#include "FreightWagon.h"

FreightWagon::FreightWagon(unsigned int number, unsigned int year, unsigned int tonnage, Type type) :Wagon(number, year), tonnage(tonnage), type(type) {}

unsigned int FreightWagon::Get_tonnage()
{
	return tonnage;
}

Type FreightWagon::Get_type()
{
	return type;
}

void FreightWagon::Set_tonnage(unsigned int val)
{
	tonnage = val;
}

void FreightWagon::Set_type(std::string str)
{
	type = str_to_type(str);
}

std::string FreightWagon::Get_type_string()
{
	switch (type)
	{
	case tank:
		return "цистерна";
		break;
	case platform:
		return "платформа";
		break;
	case gondola:
		return "полувагон";
		break;
	case refrigerator:
		return "рефрижератор";
		break;
	}
}

Type FreightWagon::str_to_type(std::string str)
{
	if (str == "цистерна")
	{
		return tank;
	}
	else if (str == "платформа")
	{
		return platform;
	}
	else if (str == "полувагон")
	{
		return gondola;
	}
	else if (str == "рефрижератор")
	{
		return refrigerator;
	}
}

std::string FreightWagon::toString()
{
	return "Грузовой вагон " + Wagon::toString() + ", " + Get_type_string() + ", " + std::to_string(tonnage) + " тонн";
}
