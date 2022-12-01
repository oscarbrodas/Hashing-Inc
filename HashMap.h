#pragma once
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <typeinfo>

using namespace std;

template<typename K, typename V>
class HashMap {


	int bucketSize = 8;
	int capacity; 
	const double MAX_LOAD_FACTOR = 0.80;
	vector<list<pair<K, V>*>> hashTable; // seperate chaining

	int hashFunction(const K& key); // Combines hash and reduce together
	int hash(const K& key);
	int reduce(const int& hashCode);

	typename list<pair<K, V>*>::iterator search(const K& key, list<pair<K, V>*>& chain); // Look for key in hash map, return an iterator to the pair
	
	void rehash(); // When maximum load factor is met, hash table is redone.
	

public:
	HashMap();

	void insertion(const K& key,const V& value);
	void deletion(const K& key);
	const V& searchMap(const K& key);
	void printTable() const;
	V& operator[](const K& key);



};

/*===== Constructor =====*/
template<typename K, typename V>
HashMap<K, V>::HashMap()
{
	hashTable.resize(bucketSize);
	capacity = 0;
}

/*===== Behaviors =====*/
template<typename K, typename V>
void HashMap<K,V>::insertion(const K& key, const V& value)
{
	int index = hashFunction(key);

	list<pair<K, V>*>& chain = hashTable.at(index);
	auto foundPair = search(key, chain);

	if (foundPair != chain.end()) // Checking if key was found
		(*foundPair)->second = value; // Update value if found
	else
	{
		capacity++; // Increment number of elements stored
		double loadFactor = double(capacity) / bucketSize;
		if (loadFactor >= MAX_LOAD_FACTOR) // If table is crowded
		{
			rehash();
			index = hashFunction(key);    // Rehash the table, recalculate index and list
			list<pair<K,V>*>& rehashChain = hashTable.at(index); // Need new chain, old one points to deleted memory

			pair<K, V>* pairPtr = new pair<K, V>(key, value); // Create a new pair and insert
			rehashChain.push_back(pairPtr);
			return;
		}

		pair<K, V>* pairPtr = new pair<K, V>(key, value); // Create a new pair and insert
		chain.push_back(pairPtr);
	}
}
template<typename K, typename V>
void HashMap<K,V>::deletion(const K& key)
{

	int index = hashFunction(key);

	list<pair<K, V>*>& chain = hashTable.at(index);
	auto foundPair = search(key, chain);

	if (foundPair != chain.end())
	{
		chain.erase(foundPair);
		capacity--;
	}
		
}
template<typename K, typename V>
const V& HashMap<K,V>::searchMap(const K& key)
{
	int index = hashFunction(key);

	list<pair<K, V>*>& chain = hashTable.at(index);
	auto foundPair = search(key, chain);

	if (foundPair != chain.end())
		return (*foundPair)->second;
	else
		return -1; // Usually a map would create a new pair, placeholder maybe
}
template<typename K, typename V>
void HashMap<K,V>::printTable() const
{
	for (unsigned int i = 0; i < hashTable.size(); i++)
	{
		auto it = hashTable.at(i).begin();
		cout << i << ": ";
		while (it != hashTable.at(i).end())
		{
			cout << (*it)->second << " -> ";
			it++;
		}
		cout << endl;
	}
}


/*===== Operators =====*/
template<typename K, typename V>
V& HashMap<K,V>::operator[](const K& key)
{
	int index = hashFunction(key);

	list<pair<K, V>*>& chain = hashTable.at(index);
	auto foundPair = search(key, chain);

	if (foundPair != chain.end()) // If duplicate, return value
		return (*foundPair)->second;

	// Else create a new pair, value-intialized

	capacity++; // Increment number of elements stored
	double loadFactor = double(capacity) / bucketSize;
	if (loadFactor >= MAX_LOAD_FACTOR) // If table is crowded
	{
		rehash();
		index = hashFunction(key);    // Rehash the table, recalculate index and list
		list<pair<K, V>*>& rehashChain = hashTable.at(index); // Need new chain, old one points to deleted memory

		pair<K, V>* pairPtr = new pair<K, V>(); // Create a new pair and insert
		rehashChain.push_back(pairPtr);
		pairPtr->first = key;
		return pairPtr->second;
	}

	pair<K, V>* pairPtr = new pair<K, V>();
	chain.push_back(pairPtr);

	pairPtr->first = key;
	return pairPtr->second;
}


/*===== Helpers =====*/
template<typename K, typename V>
int HashMap<K, V>::hashFunction(const K& key)
{
	int hashCode = hash(key);
	int index = reduce(key);
	return index;
}
template<typename K, typename V>
int HashMap<K,V>::hash(const K& key)
{
	return key; // PlaceHolder
}
template<typename K, typename V>
int HashMap<K,V>::reduce(const int& hashCode)
{
	return hashCode % bucketSize;
}
template<typename K, typename V>
typename list<pair<K, V>*>::iterator HashMap<K,V>::search(const K& key, list<pair<K, V>*>& chain)
{
	typename list<pair<K, V>*>::iterator it;
	for (it = chain.begin(); it != chain.end(); it++)
	{
		if ((*it)->first == key) // If their is a key match, return it
		{
			return it;
		}
	}
	return it; // Else return chain.end()
}
template<typename K, typename V>
void HashMap<K, V>::rehash()
{
	bucketSize *= 2;
	vector<list<pair<K, V>*>> newHashTable; // Create a new table, of double the size
	newHashTable.resize(bucketSize);
	
	for (unsigned int i = 0; i < hashTable.size(); i++) // For each list,
	{
		list<pair<K, V>*>& chain = hashTable.at(i);
		for (auto it = chain.begin(); it != chain.end(); it++) // For each pair,
		{
			int key = (*it)->first;
			int value = (*it)->second;

			int index = hashFunction(key);
			
			list<pair<K, V>*>& newChain = newHashTable.at(index);

			pair<K, V>* pairPtr = new pair<K, V>(key, value); // Create a new pair and insert into placeholder table
			newChain.push_back(pairPtr);

			delete *it;  // Free allocated memory
		}
		chain.clear();
	}

	hashTable = newHashTable;
}

