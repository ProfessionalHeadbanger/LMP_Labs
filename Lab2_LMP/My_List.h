#pragma once
#include <iostream>
#include <fstream>
#include "Product.h"

using TInfo = Product;

struct NODE
{
	TInfo info; // глобально относительно констр.
	NODE* next,* prev;
	NODE(TInfo info, NODE* next = nullptr, NODE* prev = nullptr) :info(info), next(next), prev(prev) {}
	~NODE() // деструктор
	{
		next = nullptr;
		prev = nullptr;
	}
};

using  ptrNODE = NODE*;

struct DLIST
{
private:
	ptrNODE begin, end;
	size_t size;
public:
	DLIST() { begin = nullptr, end = nullptr; };
	DLIST(const char* file_name);
	void first_node(const TInfo& product);
	bool empty();
	void add_after(ptrNODE ptr, const TInfo& product);
	void add_before(ptrNODE ptr, const TInfo& product);
	void del_before(ptrNODE& ptr);
	void del_after(ptrNODE& ptr);
	void print();
	~DLIST();
	TInfo& Delete(ptrNODE& ptr);
	ptrNODE get_begin()
	{
		return begin;
	}
};
