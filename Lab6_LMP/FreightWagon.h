#pragma once
#include "Wagon.h"

enum Type
{
	tank,
	platform,
	gondola,
	refrigerator
};

class FreightWagon : public Wagon
{
private:
	unsigned int tonnage;
	Type type;
public:
	FreightWagon(unsigned int number = 0, unsigned int year = 0, unsigned int tonnage = 0, Type type = tank);
	unsigned int Get_tonnage();
	Type Get_type();
	void Set_tonnage(unsigned int);
	void Set_type(std::string);
	std::string Get_type_string();
	static Type str_to_type(std::string);
	std::string toString() override;
};

