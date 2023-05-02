#include "Product.h"

Product::Product(){}

Product::Product(std::ifstream& input_file)
{
	std::string separator;
	input_file >> code;
	input_file.ignore();
	std::getline(input_file, name);
	std::getline(input_file, unit);
	input_file >> cost;
	input_file >> expiration_date[0] >> expiration_date[1];
	input_file.ignore();
	std::getline(input_file, shop_name);
	std::getline(input_file, separator);
}

void Product::print()
{
	std::cout << code << std::endl;
	std::cout << name << std::endl;
	std::cout << unit << std::endl;
	std::cout << cost << std::endl;
	std::cout << expiration_date[0] << " " << expiration_date[1] << std::endl;
	std::cout << shop_name << std::endl;
	std::cout << "----------" << std::endl;
}

int Product::Compare(const Product& product)
{
	int result = 1;
	if (name < product.name
		|| name == product.name && cost > product.cost
		|| name == product.name && cost == product.cost && code < product.code)
	{
		result = -1;
	}
	else if (name == product.name && cost == product.cost && code == product.code)
	{
		result = 0;
	}
	return result;
}

std::string Product::GetName()
{
	return name;
}

std::string Product::GetShopName()
{
	return shop_name;
}
