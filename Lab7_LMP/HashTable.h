#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include "Product.h"

using TInfo = Product;
using THashTable = std::vector<std::list<TInfo>>;
using Iterator = std::list<TInfo>::iterator;

class HashTable
{
private:
	THashTable hashTable;
	size_t maxSize;
public:
	HashTable(size_t maxSize)
	{
		hashTable.resize(maxSize);
	};
	HashTable(std::ifstream& file, size_t MaxSize);
	size_t hash(int key);
	Iterator find(int key);
	bool find(int key, TInfo& current);
	bool remove(int key);
	bool add(TInfo pair);
	void print();
	~HashTable() {};
};

