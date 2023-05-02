#include "Depot.h"

Depot::Depot(std::string name):name(name) {}

std::string Depot::Get_name()
{
	return name;
}

wg_ptr::iterator Depot::Get_begin()
{
	return List.begin();
}

wg_ptr::iterator Depot::Get_end()
{
	return List.end();
}

void Depot::Set_name(std::string val)
{
	name = val;
}

void Depot::add_by_order(info_t wagon)
{
	auto i = List.begin();
	while (i != List.end() && (*i)->comp(*wagon) == -1)
	{
		i++;
	}
	List.insert(i, std::move(wagon));
}

void Depot::add_to_begin(info_t wagon)
{
	List.insert(List.begin(), std::move(wagon));
}

void Depot::add_to_end(info_t wagon)
{
	List.push_back(std::move(wagon));
}

void Depot::move_to_end(const Wagon& wagon)
{
	for (auto i = List.begin(); i != List.end();)
	{
		if ((*i)->comp(wagon) == 0)
		{
			i = List.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void Depot::sort()
{
	std::sort(List.begin(), List.end(), [](const info_t& Wg1, const info_t& Wg2) {return Wg1->comp(*Wg2) == -1; });
}

std::ostream& operator<<(std::ostream& output, Depot& object)
{
	for (const info_t& Wg : object.List)
	{
		output << Wg->toString() << "\n";
	}
	return output;
}
