#include <iostream>
#include <Windows.h>
#include <process.h>
#include <fstream>

const size_t NTHREAD = 3;
size_t n = 0;
size_t m = 0;

using INFORM = struct elem
{
	int** A;
	size_t beg, end;
	int count = 0;
};

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

unsigned __stdcall count_num(void* arr)
{
	INFORM* inf = (INFORM*)arr;
	inf->count = 0;
	for (int i = inf->beg; i < inf->end; i++)
	{
		if (check(inf->A[i / m][i % m]))
		{
			inf->count++;
		}
	}
	_endthreadex(0);
	return 0;
}

int par_count_num(int** arr)
{
	HANDLE TH[NTHREAD];
	unsigned THID[NTHREAD];
	INFORM inf[NTHREAD];
	size_t size = n * m / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		inf[i].A = arr;
		inf[i].beg = i * size;
		inf[i].count = 0;
		if (i == NTHREAD - 1)
		{
			inf[i].end = n * m;
		}
		else
		{
			inf[i].end = (i + 1) * size;
		}
		TH[i] = (HANDLE)_beginthreadex(nullptr, 0, &count_num, &inf[i], 0, nullptr);
	}
	WaitForMultipleObjects(NTHREAD, TH, true, INFINITE);

	int res_count = 0;
	for (size_t i = 0; i < NTHREAD; i++)
	{
		res_count += inf[i].count;
	}

	for (size_t i = 0; i < NTHREAD; i++)
	{
		CloseHandle(TH[i]);
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
