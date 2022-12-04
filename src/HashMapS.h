#pragma once
#include <string>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <typeinfo>
#include <iostream>

using namespace std;
typedef pair<string, int> prS;

class HashMapS
{
	// Compare object overload for priority_queue
	struct pairComparison  // Compares pairs based on their second value 
	{
		bool operator()(const prS& pair1, const prS& pair2)
		{
			return pair1.second > pair2.second;  // Check greater than for min heap
		}
	};


	int bucketSize = 8;
	int capacity;
	const double MAX_LOAD_FACTOR = 0.80;
	vector<list<prS*>> hashTable; // seperate chaining
	bool hashFunctionA; // Boolean checking which hashFunction to use

	int keyToInt(const string& key);

	int hashFunction(const int& key); // Combines hash and reduce together
	int hashA(const int& key);
	int hashB(const int& key);
	int reduce(const int& hashCode);

	list<prS*>::iterator search(const string& key, list<prS*>& chain); // Look for key in hash map, return an iterator to the pair

	void rehash(); // When maximum load factor is met, hash table is redone.


public:
	HashMapS(bool hashFunctionA);
	~HashMapS();

	void insertion(const string& key, const int& value);
	void deletion(const string& key);
	prS searchMap(const string& key);
	void printTable() const;
	vector<prS> freqeuntKeys();
	int& operator[](const string& key);
};


