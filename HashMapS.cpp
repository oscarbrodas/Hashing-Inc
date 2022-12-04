#include "HashMapS.h"


/*===== Constructor/Deconstructor =====*/
HashMapS::HashMapS(bool hashFunctionA)
{
	hashTable.resize(bucketSize);
	capacity = 0;
	this->hashFunctionA = hashFunctionA;
}
HashMapS::~HashMapS()
{
	for (auto vectorIt = hashTable.begin(); vectorIt != hashTable.end(); vectorIt++)
	{
		for (auto listIt = (*vectorIt).begin(); listIt != (*vectorIt).end(); listIt++)
		{
			prS* ptrToBeDeleted = *listIt;
			delete ptrToBeDeleted;
		}
	}
}

/*===== Behaviors =====*/
void HashMapS::insertion(const string& key, const int& value)
{
	int integerKey;

	// Need to transform key into an integer, 
	integerKey = keyToInt(key);


	int index = hashFunction(integerKey);

	list<prS*>& chain = hashTable.at(index);
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
			index = hashFunction(integerKey);    // Rehash the table, recalculate index and list
			list<prS*>& rehashChain = hashTable.at(index); // Need new chain, old one points to deleted memory

			prS* pairPtr = new prS(key, value); // Create a new pair and insert
			rehashChain.push_back(pairPtr);
			return;
		}

		prS* pairPtr = new prS(key, value); // Create a new pair and insert
		chain.push_back(pairPtr);
	}
}
void HashMapS::deletion(const string& key)
{
	int integerKey;

	// Need to transform key into an integer, 
	integerKey = keyToInt(key);

	int index = hashFunction(integerKey);

	list<prS*>& chain = hashTable.at(index);
	auto foundPair = search(key, chain);

	if (foundPair != chain.end())
	{
		prS* ptrToBeDeleted = *foundPair;
		chain.erase(foundPair);
		capacity--;
		delete ptrToBeDeleted;
	}

}
prS HashMapS::searchMap(const string& key)
{
	int integerKey;

	// Need to transform key into an integer, 
	integerKey = keyToInt(key);

	int index = hashFunction(integerKey);

	list<prS*>& chain = hashTable.at(index);
	auto foundPair = search(key, chain);

	if (foundPair != chain.end())
		return *(*foundPair);
	else
		return prS(); // usually a map would return map.end(), here just return empty pair
}
void HashMapS::printTable() const
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
vector<prS> HashMapS::freqeuntKeys()
{
	priority_queue<prS, vector<prS>, pairComparison> minHeap; // 10th Biggest Elements

	for (auto vectorIt = hashTable.begin(); vectorIt != hashTable.end(); vectorIt++)
	{
		for (auto listIt = (*vectorIt).begin(); listIt != (*vectorIt).end(); listIt++)
		{
			if (minHeap.size() < 10)
				minHeap.push(make_pair((*listIt)->first, (*listIt)->second)); // While the heap has less than ten elements, insert
			else if (minHeap.top().second < (*listIt)->second) // if the smallest element is smaller than the current, 
			{
				minHeap.pop();
				minHeap.push(make_pair((*listIt)->first, (*listIt)->second));   // Remove the top and insert the current function, keeping the size as 10
			}
		}
	}

	vector<prS> frequentKeys;
	while (!minHeap.empty())
	{
		frequentKeys.push_back(minHeap.top());
		minHeap.pop();
	}
	return frequentKeys;
}



/*===== Operators =====*/
int& HashMapS::operator[](const string& key)
{
	int integerKey;

	// Need to transform key into an integer, 
	integerKey = keyToInt(key);

	int index = hashFunction(integerKey);

	list<prS*>& chain = hashTable.at(index);
	auto foundPair = search(key, chain);

	if (foundPair != chain.end()) // If duplicate, return value
		return (*foundPair)->second;

	// Else create a new pair, value-intialized

	capacity++; // Increment number of elements stored
	double loadFactor = double(capacity) / bucketSize;
	if (loadFactor >= MAX_LOAD_FACTOR) // If table is crowded
	{
		rehash();
		index = hashFunction(integerKey);    // Rehash the table, recalculate index and list
		list<prS*>& rehashChain = hashTable.at(index); // Need new chain, old one points to deleted memory

		prS* pairPtr = new prS(); // Create a new pair and insert
		rehashChain.push_back(pairPtr);
		pairPtr->first = key;
		return pairPtr->second;
	}

	prS* pairPtr = new prS();
	chain.push_back(pairPtr);

	pairPtr->first = key;
	return pairPtr->second;
}


/*===== Helpers =====*/
int HashMapS::hashFunction(const int& key)
{
	int hashCode;
	if (hashFunctionA)
		hashCode = hashA(key);
	else
		hashCode = hashB(key);

	int index = reduce(hashCode);
	return index;
}
int HashMapS::hashA(const int& key) // Mid Square Method Implmentation
{
	int k = key * key;
	string product = to_string(k);
	string stringHash;
	if (product.size() <= 2)
		stringHash = product;
	else
		stringHash = product.substr(product.length() / 2 - 1, 2);

	int hash = stoi(stringHash);
	return hash;
}
int HashMapS::hashB(const int& key)
{
	string keyS = to_string(key);
	int sum = 0;
	while(keyS.size()>0){
		if(keyS.size()>=2) {
			sum += stoi(keyS.substr(0,2));
			keyS = keyS.substr(2,keyS.size()-2);
		}
		else{
			sum += stoi(keyS.substr(0,1));
			keyS = "";
		}
	}

	return sum;
}
int HashMapS::reduce(const int& hashCode)
{
	return hashCode % bucketSize;
}
int HashMapS::keyToInt(const string& key)
{
	return key.length(); // Length of string to be used
}
list<prS*>::iterator HashMapS::search(const string& key, list<prS*>& chain)
{
	list<prS*>::iterator it;
	for (it = chain.begin(); it != chain.end(); it++)
	{
		if ((*it)->first == key) // If their is a key match, return it
		{
			return it;
		}
	}
	return it; // Else return chain.end()
}
void HashMapS::rehash()
{
	bucketSize *= 2;
	vector<list<prS*>> newHashTable; // Create a new table, of double the size
	newHashTable.resize(bucketSize);

	for (unsigned int i = 0; i < hashTable.size(); i++) // For each list,
	{
		list<prS*>& chain = hashTable.at(i);
		for (auto it = chain.begin(); it != chain.end(); it++) // For each pair,
		{
			string key = (*it)->first;
			int value = (*it)->second;

			int integerKey = keyToInt(key);

			int index = hashFunction(integerKey);

			list<prS*>& newChain = newHashTable.at(index);

			prS* pairPtr = new prS(key, value); // Create a new pair and insert into placeholder table
			newChain.push_back(pairPtr);

			delete* it;  // Free allocated memory
		}
		chain.clear();
	}

	hashTable = newHashTable;
}