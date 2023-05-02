#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

struct NODE
{
	NODE* ptrs[26];
	bool eow = false;
	NODE()
	{
		for (int i = 0; i < 26; ++i)
			ptrs[i] = nullptr;
	}
};

using TrieTree = NODE*;

void init(TrieTree& root)
{
	root = nullptr;
}

bool empty(TrieTree root)
{
	return root == nullptr;
}

void add(TrieTree& t, const std::string word, size_t i)
{
	if (!t)
	{
		t = new NODE;

	}
	if ((word.length()) - 1 < i)
		t->eow = true;
	else
		add(t->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptr_empty(TrieTree t)
{
	bool res = true;
	size_t i = 0;
	while (i < 26 && res)
		if (!t->ptrs[i])
			++i;
		else
			res = false;
	return res;
}

void del(TrieTree& t, const std::string word, size_t i)
{
	if (t)
		if (i <= word.length() - 1)
			del(t->ptrs[word[i] - 'a'], word, i + 1);
		else
		{
			t->eow = false;
			if (all_ptr_empty(t))
			{
				delete t;
				t = nullptr;
			}
		}
}

void print(TrieTree t, std::string word)
{
	if (t->eow)
	{
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			print(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

void clear(TrieTree& t)
{
	for (size_t i = 0; i < 26; ++i)

		if (t->ptrs[i])
			clear(t->ptrs[i]);
	delete t;
	t = nullptr;
}

void printall(TrieTree t, std::string word)
{
	bool flag = 1;
	for (int i = 0; i < 26; i++)
		if (t->ptrs[i])
			flag = 0;
	if (flag)
	{
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			printall(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

//Дано Trie-дерево. Посчитать количество слов нечетной длины

int task(TrieTree& tree, int len = 0)
{
	int count = 0;
	if (tree->eow)
	{
		count += len % 2;
	}
	for (int i = 0; i < 26; i++)
	{
		if (tree->ptrs[i])
		{
			count += task(tree->ptrs[i], len + 1);
		}
	}
	return count;
}

int main()
{
	std::ifstream file("input.txt");
	TrieTree tree;
	init(tree);
	std::string word;
	while (std::getline(file, word))
	{
		if (word.length())
		{
			add(tree, word, 0);
		}
	}
	file.close();
	print(tree, "");

	std::cout << task(tree);
}
