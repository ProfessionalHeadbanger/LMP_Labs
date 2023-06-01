//Дана прямоугольная целочисленная матрица. Распараллеливание по элементам. Посчитать количество чисел, в которых цифры упорядочены по убыванию

#include <iostream>
#include <Windows.h>
#include <omp.h>
#include <fstream>

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
	int res_count = 0;
	omp_lock_t lock;
	omp_init_lock(&lock);
#pragma omp parallel shared(arr)
	{
		int loc_count = 0;
#pragma omp for schedule(static, 10)
		for (int i = 0; i < n * m; i++)
		{
			if (check(arr[i / m][i % m]))
			{
				loc_count++;
			}
		}

		omp_set_lock(&lock);
		res_count += loc_count;
		std::cout << loc_count << std::endl;
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
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

	std::cout << "Result count: " << par_count_num(arr) << std::endl;
}
