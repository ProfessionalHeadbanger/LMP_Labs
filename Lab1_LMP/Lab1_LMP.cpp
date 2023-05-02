//Дан текстовый файл input.txt, в котором хранятся целые числа.
//Создать список по принципу очереди. 
//Найти вторую подпоследовательность, состоящую из простых чисел. 
//Переставить эту подпоследовательность после первого элемента, кратного 4. 
//Полученную последовательность записать в текстовый файл output.txt. 
//Если искомой подпоследовательности нет, то помимо последовательности в файл записать соответствующее сообщение.

#include "My_List.h"
#include <Windows.h>

bool task(LIST& list)
{
	auto is_prime_pair = [](int first, int second)
	{
		auto is_prime_alone = [](int number)
		{
			bool result = number != 0 && number != 1;
			for (int i = 2; i <= number / 2 && result; ++i)
			{
				if (number % i == 0)
				{
					result = false;
				}
			}
			return result;
		};
		bool prime = is_prime_alone(first) && is_prime_alone(second);
		return prime;
	};

	bool check = false;
	ptrNODE beg = nullptr, end = nullptr, head = list.get_head();
	ptrNODE p = head;
	ptrNODE kr4 = nullptr;
	ptrNODE tail = list.get_tail();
	int counter = 0;

	while (p->next && p->next->next && counter != 2)
	{
		if (is_prime_pair(*p->next->info, *p->next->next->info) && (p == head || !is_prime_pair(*p->info, *p->next->info)))
		{
			beg = p;
			end = nullptr;
		}
		else
		{
			if (is_prime_pair(*p->info, *p->next->info) && !is_prime_pair(*p->next->info, *p->next->next->info))
			{
				end = p->next;
				counter++;
			}
		}
		if (*p->next->info % 4 == 0 && kr4 == nullptr)
		{
			kr4 = p->next;
		}
		p = p->next;
	}
	if (counter == 2)
	{
		while (p->next && !kr4)
		{
			if (*p->next->info % 4 == 0)
			{
				kr4 = p->next;
			}
		}
		if (beg && !end)
		{
			end = p->next;
		}
		if (kr4)
		{
			if (end != kr4)
			{
				if (kr4 == tail)
				{
					list.set_tail(end);
				}
				if (end == tail)
				{
					list.set_tail(beg);
				}
				ptrNODE tmp = beg->next;
				beg->next = end->next;
				end->next = kr4->next;
				kr4->next = tmp;
			}
			check = true;
		}
	}
	
	return check;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool flag = true;
	while (flag)
	{
		LIST list;
		std::ifstream file_in("input.txt");
		std::ofstream file_out("output.txt");
		if (file_in)
		{
			bool input = true;
			while (input)
			{
				char choice;
				std::cout << "Выберите, как будет создаваться список (1 - стек, 2 - очередь, 3 - упорядоченно): "; std::cin >> choice;
				switch (choice)
				{
				case '1':
					list.create_by_stack(file_in);
					input = false;
					break;
				case '2':
					list.create_by_queue(file_in);
					input = false;
					break;
				case '3':
					list.create_by_order(file_in);
					input = false;
					break;
				default:
					std::cout << "Неверный ввод" << std::endl;
					input = true;
					break;
				}
			}
			if (task(list))
			{
				list.print(file_out, "Преобразованная последовательность: \n");
			}
			else
			{
				list.print(file_out);
			}
		}

		file_in.close();
		file_out.close();

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
	std::cin.ignore();
	std::cin.get();
}
