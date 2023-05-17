//Дана прямоугольная целочисленная матрица. Распараллеливание по элементам. Посчитать количество чисел, в которых цифры упорядочены по убыванию

#include <iostream>
#include <future>
#include <fstream>

const size_t NTHREAD = 4;
size_t n = 0;
size_t m = 0;

bool check(int num)
{
	num = abs(num);
	int prevDigit = -1;
	while (num > 0) {
		int currentDigit = num % 10;
		if (currentDigit <= prevDigit) {
			return false;
		}
		prevDigit = currentDigit;
		num /= 10;
	}
	return true;
}

int count_num(int** arr, int beg, int end)
{
	int count = 0;
	for (int i = beg; i < end; i++)
	{
		if (check(arr[i / m][i % m]))
		{
			count++;
		}
	}
	return count;
}

int par_count_num(int** arr)
{
	std::future<int> TH[NTHREAD];
	size_t size = n * m / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		if (i == NTHREAD - 1)
		{
			TH[i] = std::async(std::launch::async, count_num, arr, i * size, n * m);
		}
		else
		{
			TH[i] = std::async(std::launch::async, count_num, arr, i * size, (i + 1) * size);
		}
	}

	int res_count = 0;
	for (size_t i = 0; i < NTHREAD; i++)
	{
		res_count += TH[i].get();
	}
	return res_count;
}

int main()
{
	int** arr;
	std::fstream file("input.txt");
	file >> n >> m;
	arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			file >> arr[i][j];
		}
	}

	std::cout << par_count_num(arr) << std::endl;
}
