//Дана прямоугольная целочисленная матрица. Распараллеливание по элементам. Посчитать количество чисел, в которых цифры упорядочены по убыванию

#include <iostream>
#include <thread>
#include <fstream>
#include <Windows.h>
#include <stack>

struct Piece
{
	int* begin, * end;
	Piece(int* start = nullptr, int *end = nullptr)
	{
		this->begin = start;
		this->end = end;
	}
};

using TInfo = Piece;

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
SafeStack stack;

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
	int local_count = 0;
	for (int* i = piece.begin; i != piece.end; i++)
	{
		if (check(*i))
		{
			local_count++;
		}
	}
	return local_count;
}

void thread_task()
{
	Piece piece;
	while (!stack.is_empty())
	{
		if (stack.try_pop(piece))
		{
			_InterlockedExchangeAdd(&res_count, count_num(piece));
		}
	}
}


void par_count_num(int* arr)
{
	std::thread TH[NTHREAD - 1];
	

	for (int i = 0; i < n * m / piece_size; i++)
	{
		Piece piece(arr + i * piece_size, arr + (i + 1) * piece_size);
		stack.push(piece);
	}

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		TH[i] = std::thread(thread_task);
	}

	Piece piece(arr + n * m - (n * m) % piece_size, arr + n * m - (n * m) % piece_size + (n * m) % piece_size);
	_InterlockedExchangeAdd(&res_count, count_num(piece));
	
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

	Piece piece(arr[0], arr[0] + n * m);
	std::cout << count_num(piece) << std::endl;
}
