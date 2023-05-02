#include"HashTable.h"
#include<Windows.h>

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream file("products.txt");
	HashTable Table(file, 3);
	Table.print();
	
	int check = 4;
	Table.remove(check);
	Table.print();

	int key = 5;
	Product tmp;
	if (Table.find(key, tmp))
	{
		std::cout << tmp << std::endl;
	}
	else
	{
		std::cout << "Не найдено" << std::endl;
	}
}
