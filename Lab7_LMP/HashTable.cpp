#include "HashTable.h"

HashTable::HashTable(std::ifstream& file, size_t MaxSize)
{
	Product current;
	maxSize = MaxSize;
	hashTable.resize(maxSize);
	while (file >> current)
	{
		add(current);
	}
	file.close();
}

size_t HashTable::hash(int key)
{
	size_t res = key;
	return res % maxSize;
}

Iterator HashTable::find(int key)
{
	int index = hash(key);
	return std::find_if(hashTable[index].begin(), hashTable[index].end(), [&key](Product elem)->bool {return elem.GetCode() == key; });
}

bool HashTable::find(int key, TInfo& current)
{
	bool result = false;
	int index = hash(key);
	Iterator it = std::find_if(hashTable[index].begin(), hashTable[index].end(), [&key](TInfo elem)->bool {return elem.GetCode() == key; });
	if (it != hashTable[index].end()) {
		current = *it;
		result = true;
	}
	return result;
}

bool HashTable::remove(int key)
{
	bool result = false;
	Iterator it = find(key);
	size_t index = hash(key);
	if (it != hashTable[index].end()) {
		result = true;
		hashTable[index].erase(it);
	}
	return result;
}

bool HashTable::add(TInfo current)
{
	bool res = false;
	int index = hash(current.GetCode());
	if (std::find_if(hashTable[index].begin(), hashTable[index].end(), [&current](TInfo elem)->bool 
		{return elem.GetCode() == current.GetCode(); }) == hashTable[index].end())
	{
		hashTable[index].push_back(current);
		res = true;
	}

	return res;
}

void HashTable::print()
{
	for (int i = 0; i < maxSize; i++)
	{
		for (auto current : hashTable[i])
		{
			std::cout << i + 1 << ": " << current << '\n';
		}	
	}
}
