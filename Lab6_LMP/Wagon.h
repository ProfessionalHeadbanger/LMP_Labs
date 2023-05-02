#pragma once
#include <iostream>
#include <string>

class Wagon
{
private:
	unsigned int number;
	unsigned int year;
public:
	Wagon(unsigned int number = 0, unsigned int year = 0);
	virtual ~Wagon();
	unsigned int Get_number();
	unsigned int Get_year();
	void Set_number(unsigned int);
	void Set_year(unsigned int);
	int comp(const Wagon&);
	virtual std::string toString();
};

