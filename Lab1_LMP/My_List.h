#pragma once//следит подключена библиотека или нет (чтобы не было повтороного подключения)
#include <iostream>
#include <fstream>

using TInfo = int;//ввод псевдонима

struct NODE //cтруктура узла
{
	TInfo* info;
	NODE* next;//поле, хранящее следующий узел 
	NODE(TInfo value, NODE* ptr = nullptr) :next(ptr) //конструктор
	{
		info = new int;
		*info = value;
	}
	~NODE()//деструктор
	{
		next = nullptr;
		delete info;
		info = nullptr;
	}
};

using ptrNODE = NODE*;//псевдоним узла

struct LIST
{
private:
	ptrNODE head, tail;//создание заглавного и последнего узла
	size_t size;
	void adding_by_pointer(ptrNODE& ptr, TInfo elem)
	{
		ptrNODE p = new NODE(elem, ptr);
		ptr = p;
	}
	void deleting_by_pointer(ptrNODE& ptr)
	{
		ptrNODE p = ptr;
		ptr = p->next;
		delete p;
	}
public:
	LIST()//конструктор
	{
		head = new NODE(0);
		tail = head;
		size = 0;
	}
	//методы
	~LIST();
	ptrNODE get_head()//запрос головы (в таске, чтобы появилось начало списка)
	{
		return head;
	}
	TInfo get_first()
	{
		return *head->next->info;
	}
	size_t get_size()
	{
		return size;
	}
	ptrNODE get_tail()
	{
		return tail;
	}
	void set_tail(ptrNODE ptr)
	{
		tail = ptr;
	}
	bool empty();
	void add_to_head(TInfo elem);
	void add_to_tail(TInfo elem);
	void add_after(ptrNODE ptr, TInfo elem);
	void del_from_head();
	void del_after(ptrNODE ptr);
	void create_by_stack(std::ifstream& file);
	void create_by_queue(std::ifstream& file);
	void create_by_order(std::ifstream& file);
	void print(std::ofstream& file, const char* message = "Искомой последовательности не обружено\n");
	void sorting();//cортировка по возрастанию
};
