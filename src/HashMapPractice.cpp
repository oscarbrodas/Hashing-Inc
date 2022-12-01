// HashMapPractice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include "HashMap.h"

int main()
{
    HashMap<int, int> counter;
    /*counter.insertion(4, 4);
    counter.insertion(12, 3);
    counter.insertion(3, 34);
    counter[5]++;
    counter[5]++;
    counter.printTable();
    counter.insertion(7,1);
    counter.printTable();
    counter.insertion(90, 6);
    counter.printTable();
    counter.insertion(57, 57);
    counter.printTable();

    cout << counter.searchMap(4) << endl;
    cout << counter.searchMap(5) << "-1 signifies missing/not found" << endl;
    cout << counter.searchMap(3) << endl;*/

    int max;
    max = 100; //set the upper bound to generate the random number
    srand(time(0));

    for (int i = 0; i < 10000; i++)
    {
        counter[rand() % 100]++;
    }
    counter.printTable();
}


