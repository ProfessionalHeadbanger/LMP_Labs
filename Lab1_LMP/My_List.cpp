#define _CRTDBG_MAP_ALLOC//ïðîâåðêà êîððåêòíîñòè äàííûõ
#include <crtdbg.h>
#define DBG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define newDBG_NEW

#include "My_list.h"
#include <functional>

LIST::~LIST()
{
	std::cout << "***";
	while (!empty())
		del_from_head();
	delete head;
	std::cout << "*** \n";
	_CrtDumpMemoryLeaks();
}

bool LIST::empty()
{
	return head->next == nullptr;
}

void LIST::add_to_head(TInfo elem)
{
	adding_by_pointer(head->next, elem);
	if (head == tail)//cïèñîê ïóñò
		tail = tail->next;
	++size;
}

void LIST::add_to_tail(TInfo elem)
{
	adding_by_pointer(tail->next, elem);
	tail = tail->next;
	++size;
}

void LIST::add_after(ptrNODE ptr, TInfo elem)
{
	if (ptr)//åñòü àäðåñ, ïî êîòîðîìó äåëàòü âñòàâêó
	{
		adding_by_pointer(ptr->next, elem);
		if (ptr == tail)
			tail = tail->next;
		++size;
	}
}

void LIST::del_from_head()
{
	if (head->next)
	{
		deleting_by_pointer(head->next);
		if (!head->next) //îäèí ýëåìåíò
			tail = head;
		--size;
	}
}

void LIST::del_after(ptrNODE ptr)
{
	if (ptr && ptr->next)
	{
		if (ptr->next == tail)
			tail = ptr;
		deleting_by_pointer(ptr->next);
		if (empty())
			tail = head;//íàäî èëè âåðõíÿÿ ñïðàâèòñÿ
		--size;
	}
}

void LIST::create_by_stack(std::ifstream& file)
{
	TInfo elem;
	while (file >> elem)
		add_to_head(elem);
}

void LIST::create_by_queue(std::ifstream& file)
{
	TInfo elem;
	while (file >> elem)
		add_to_tail(elem);
}

void LIST::create_by_order(std::ifstream& file)
{
	TInfo elem;
	ptrNODE p = nullptr;
	auto find_place = [this](TInfo elem)->ptrNODE//èùåì, êóäà âñòàâèòü ýëåìåíò (ïîèñê ìåñòà äëÿ âñòàâêè)
	{
		ptrNODE result = head;
		while (result->next && *result->next->info < elem)
			result = result->next;
		return result;
	};
	while (file >> elem)
	{
		p = find_place(elem);
		add_after(p, elem);
	}
}

void LIST::print(std::ofstream& file, const char* message)
{
	file << message;
	ptrNODE p = head->next;
	while (p)
	{
		file << *p->info << ' ';
		p = p->next;
	}
	file << '\n';
}

void LIST::sorting()
{
	auto switch_pointers = [](ptrNODE q, ptrNODE p)
	{
		ptrNODE tmp = p->next;
		p->next = tmp->next;
		tmp->next = q->next;
		q->next = tmp;
	};
	//h -      ýëåìåíò, äëÿ êîòðîãî èùåòñÿ ìåñòî äëÿ âñòàâêè â óïîðÿäî÷åíííîé îáëàñòè
	//h_prev - êóäà âñòàâëÿòü
	ptrNODE h = head->next->next, h_prev = head->next;
	while (h)
	{
		if (*h_prev->info > *h->info)//îçíà÷àåò, ÷òî íàøëè ìåñòî äëÿ âñòàâêè
		{
			ptrNODE p = head;
			while (p->next != h && *p->next->info < *h->info)//èìååò ìåñòî âñòàâêè (äëÿ ïåðåêëþ÷åíèÿ óêàçàòåëåé)
				p = p->next;
			switch_pointers(p, h_prev);
			h = h_prev->next;
		}
		else //åñëè ýëåìåíòû óïîðÿäî÷åíû (ìåñòî èñêàòü íå íàäî)
		{
			h_prev = h;
			h = h->next;
		}
	}
	tail = h_prev;
}
