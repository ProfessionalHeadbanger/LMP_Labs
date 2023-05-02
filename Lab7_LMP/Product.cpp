#include "Product.h"

Product::Product() {}

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

int Product::GetCode()
{
	return code;
}

bool Product::operator==(const Product& object)
{
	return (object.code == code && object.name == name && object.unit == unit && object.cost == cost
		&& object.expiration_date[0] == expiration_date[0] && object.expiration_date[1] == expiration_date[1]
		&& object.shop_name == shop_name);
}

Product& Product::operator=(const Product& object)
{
	if (this != &object)
	{
		code = object.code;
		name = object.name;
		unit = object.unit;
		cost = object.cost;
		expiration_date[0] = object.expiration_date[0];
		expiration_date[1] = object.expiration_date[1];
		shop_name = object.shop_name;
	}
	return *this;
}

std::istream& operator>>(std::istream& stream, Product& object)
{
	std::string separator;
	stream >> object.code;
	stream.ignore();
	std::getline(stream, object.name);
	std::getline(stream, object.unit);
	stream >> object.cost;
	stream >> object.expiration_date[0] >> object.expiration_date[1];
	stream.ignore();
	std::getline(stream, object.shop_name);
	std::getline(stream, separator);
	return stream;
}

std::ostream& operator<<(std::ostream& stream, Product& object)
{
	stream << object.code << std::endl;
	stream << object.name << std::endl;
	stream << object.unit << std::endl;
	stream << object.cost << std::endl;
	stream << object.expiration_date[0] << " " << object.expiration_date[1] << std::endl;
	stream << object.shop_name << std::endl;
	stream << "----------" << std::endl;
	return stream;
}
