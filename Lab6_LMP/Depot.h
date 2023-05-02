//3.4 - uniquepointer и vector

#pragma once
#include "Wagon.h"
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

using info_t = std::unique_ptr<Wagon>;
using wg_ptr = std::vector<info_t>;

class Depot
{
private:
	wg_ptr List;
	std::string name;
public:
	Depot(std::string name = "");
	std::string Get_name();
	wg_ptr::iterator Get_begin();
	wg_ptr::iterator Get_end();
	void Set_name(std::string);
	void add_by_order(info_t wagon);
	void add_to_begin(info_t wagon);
	void add_to_end(info_t wagon);
	void move_to_end(const Wagon& wagon);
	void sort();
	friend std::ostream& operator << (std::ostream& output, Depot& object);
};

