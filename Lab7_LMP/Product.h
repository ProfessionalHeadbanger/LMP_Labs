#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Product
{
private:
	int code;
	std::string name;
	std::string unit;
	int cost;
	int expiration_date[2];
	std::string shop_name;
public:
	Product();
	Product(std::ifstream&);
	void print();
	int Compare(const Product&);

	std::string GetName();
	std::string GetShopName();
	int GetCode();

	friend std::istream& operator >> (std::istream& stream, Product& object);
	friend std::ostream& operator << (std::ostream& stream, Product& object);

	bool operator == (const Product& object);
	Product& operator = (const Product& object);
};
