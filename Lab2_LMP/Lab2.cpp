#include "My_List.h"
#include <Windows.h>

void task(DLIST& list)
{
	ptrNODE p = list.get_begin();
	while (p)
	{
		if (p->next && p->info.GetName() != p->next->info.GetName())
		{
			std::cout << p->info.GetName() << " - " << p->info.GetShopName() << std::endl;
		}
		else if (!p->next)
		{
			std::cout << p->info.GetName() << " - " << p->info.GetShopName() << std::endl;
		}
		p = p->next;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool flag = true;
	while (flag)
	{
		std::ifstream file("products.txt");
		if (file)
		{
			DLIST list("products.txt");
			file.close();
			list.print();
			task(list);
		}

		char choice;
		bool label = true;
		while (label)
		{
			std::cout << "Желаете начать заново или выйти? 1 - заново, 2 - выйти ";
			std::cin >> choice;
			switch (choice)
			{
			default:
				std::cout << "Неверный ввод!" << std::endl;
				label = true;
				break;
			case '1':
				flag = true;
				label = false;
				break;
			case '2':
				flag = false;
				label = false;
				break;
			}
		}
	}
	std::cin.get();
}
