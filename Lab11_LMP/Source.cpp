//Дана прямоугольная целочисленная матрица. Распараллеливание по элементам. Посчитать количество чисел, в которых цифры упорядочены по убыванию

#include <iostream>
#include <thread>
#include <fstream>
#include <Windows.h>
#include <stack>

struct piece
{
	int* start, * end;
	piece(int* start = nullptr, int *end = nullptr)
	{
		this->start = start;
		this->end = end;
	}
};

using TInfo = piece;

class SafeStack
{
private:
	std::stack<TInfo> stack;
	CRITICAL_SECTION cs;
public:
	SafeStack()
	{
		InitializeCriticalSection(&cs);
	}
	void push(TInfo elem)
	{
		stack.push(elem);
	}
	bool try_pop(TInfo& elem)
	{
		bool result = false;
		EnterCriticalSection(&cs);
		if (!stack.empty())
		{
			result = true;
			elem = stack.top();
			stack.pop();
		}
		LeaveCriticalSection(&cs);
		return result;
	}
	bool is_empty()
	{
		return stack.empty();
	}
	~SafeStack()
	{
		DeleteCriticalSection(&cs);
	}
};

const size_t NTHREAD = 4;
const size_t n = 10;
const size_t m = 10;
const int piece_size = 9;
volatile long res_count = 0;
SafeStack st;

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

int count_num(TInfo piece)
{
	int loc_count = 0;
	for (int* i = piece.start; i != piece.end; i++)
	{
		if (check(*i))
		{
			loc_count++;
		}
	}

	return loc_count;
}

void task_consumer()
{
	piece p;
	while (!st.is_empty())
	{
		if (st.try_pop(p))
		{
			_InterlockedExchangeAdd(&res_count, count_num(p));
		}
	}
}


void par_count_num(int* arr)
{
	std::thread TH[NTHREAD - 1];
	

	for (int i = 0; i < n * m / piece_size; i++)
	{
		piece p(arr + i * piece_size, arr + (i + 1) * piece_size);
		st.push(p);
	}

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		TH[i] = std::thread(task_consumer);
	}

	piece p(arr + n * m - (n * m) % piece_size, arr + n * m - (n * m) % piece_size + (n * m) % piece_size);
	_InterlockedExchangeAdd(&res_count, count_num(p));
	
	for (int i = 0; i < NTHREAD - 1; i++)
	{
		TH[i].join();
	}
}

int main()
{
	int arr[n][m];
	std::fstream file("input.txt");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			file >> arr[i][j];
		}
	}
	par_count_num(arr[0]);
	std::cout << res_count << std::endl;

	piece p(arr[0], arr[0] + n * m);
	std::cout << count_num(p) << std::endl;
	
}