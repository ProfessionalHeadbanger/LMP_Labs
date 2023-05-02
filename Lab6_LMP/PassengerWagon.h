#pragma once
#include "Wagon.h"

class PassengerWagon: public Wagon
{
private:
	std::string type;
	unsigned int seats;
	bool shower;
public:
	PassengerWagon(unsigned int number = 0, unsigned int year = 0, std::string type = "", unsigned int seats = 0, bool shower = false);

	std::string Get_type();
	unsigned int Get_Seats();
	bool Get_Shower();
	void Set_type(std::string);
	void Set_seats(unsigned int);
	void Set_shower(bool);
	std::string toString() override;
};

