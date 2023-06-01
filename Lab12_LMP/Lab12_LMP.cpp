//Дана прямоугольная целочисленная матрица. Распараллеливание по элементам. Посчитать количество чисел, в которых цифры упорядочены по убыванию

#include <iostream>
#include <thread>
#include <fstream>
#include <Windows.h>
#include <stack>
#include <mutex>
#include <condition_variable>

const int piece_size = 5;

struct Piece
{
	int arr[piece_size] = {};
	Piece()	{}
	Piece(const Piece& p)
	{
		for (int i = 0; i < piece_size; i++)
		{
			this->arr[i] = p.arr[i];
		}
	}
	Piece& operator=(const Piece& p)
	{
		if (this != &p)
		{
			for (int i = 0; i < piece_size; i++)
			{
				this->arr[i] = p.arr[i];
			}
		}
		return *this;
	}
	friend std::ostream& operator<< (std::ostream& out, const Piece p)
	{
		for (int i = 0; i < piece_size; i++)
		{
			out << p.arr[i] << " ";
		}
		out << '\n';
		return out;
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
		EnterCriticalSection(&cs);
		try
		{
			stack.push(elem);
		}
		catch (...)
		{
			LeaveCriticalSection(&cs);
		}
		LeaveCriticalSection(&cs);
	}
	bool try_pop(TInfo& elem)
	{
		bool result = false;
		EnterCriticalSection(&cs);
		try
		{
			if (!stack.empty())
			{
				result = true;
				elem = stack.top();
				std::cout << elem;
				stack.pop();
			}
		}
		catch (...)
		{
			LeaveCriticalSection(&cs);
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

const size_t NTHREAD = 8;
volatile long res_count = 0;
SafeStack stack;
volatile long volume_work_producer = 10;
volatile long volume_work_consumer = 10;
std::condition_variable cv;
std::mutex mute;

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
	for (int i = 0; i < piece_size; i++)
	{
		if (check(piece.arr[i]))
		{
			local_count++;
		}
	}
	return local_count;
}

void task_producer(int ID)
{
	while (_InterlockedExchangeAdd(&volume_work_producer, -1) > 0)
	{
		Piece tmp;
		for (int i = 0; i < piece_size; i++)
		{
			tmp.arr[i] = rand() % 100 + ID;
		}
		Sleep(2);
		stack.push(tmp);
		cv.notify_all();
	}
}

void task_consumer(int ID)
{
	while (_InterlockedExchangeAdd(&volume_work_consumer, -1) > 0)
	{
		Piece piece;
		std::unique_lock<std::mutex> locker(mute);
		cv.wait_for(locker, std::chrono::seconds(5),[]() {return !stack.is_empty(); });
		if (stack.try_pop(piece))
		{
			Sleep(5);
			_InterlockedExchangeAdd(&res_count, count_num(piece));
		}
		else
		{
			_InterlockedExchangeAdd(&volume_work_consumer, 1);
		}
	}
}

void par_count_num()
{
	std::thread TH[NTHREAD];

	for (size_t i = 0; i < NTHREAD; i++)
	{
		if (i < NTHREAD - 4)
		{
			TH[i] = std::thread(task_producer, i);
		}
		else
		{
			TH[i] = std::thread(task_consumer, i);
		}
	}

	for (int i = 0; i < NTHREAD; i++)
	{
		TH[i].join();
	}
}

int main()
{
	par_count_num();
	std::cout << res_count << std::endl;
}
