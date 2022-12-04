#pragma once
#include <string>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <typeinfo>
#include <iostream>

using namespace std;
typedef pair<double, int> prD;

class HashMapD
{
	// Compare object overload for priority_queue
	struct pairComparison  // Compares pairs based on their second value 
	{
		bool operator()(const prD& pair1, const prD& pair2)
		{
			return pair1.second > pair2.second;  // Check greater than for min heap
		}
	};


	int bucketSize = 8;
	int capacity;
	const double MAX_LOAD_FACTOR = 0.80;
	vector<list<prD*>> hashTable; // seperate chaining
	bool hashFunctionA; // Boolean checking which hashFunction to use

	int keyToInt(const double& key);

	int hashFunction(const int& key); // Combines hash and reduce together
	int hashA(const int& key);
	int hashB(const int& key);
	int reduce(const int& hashCode);

	typename list<prD*>::iterator search(const double& key, list<prD*>& chain); // Look for key in hash map, return an iterator to the pair

	void rehash(); // When maximum load factor is met, hash table is redone.



public:
	HashMapD(bool hashFunctionA);
	~HashMapD();

	void insertion(const double& key, const int& value);
	void deletion(const double& key);
	prD searchMap(const double& key);
	void printTable() const;
	vector<prD> freqeuntKeys();
	int& operator[](const double& key);
};