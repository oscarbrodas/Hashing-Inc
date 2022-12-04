// HashMapPractice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include "HashMapD.h"
#include "HashMapS.h" // HashMap<string, int>
#include <queue>


int main()
{
    //===== Integer HashMap =====
   /*HashMap<int, int> counter;
    int max;
    max = 50; //set the upper bound to generate the random number
    srand(time(0));

    for (int i = 0; i < 1000; i++)
    {
        counter[rand() % 100]++;
    }
    counter.printTable();

    vector<pair<int, int>> keys = counter.freqeuntKeys();
    int i = 1;
    for (auto it = keys.rbegin(); it != keys.rend(); it++)
    {
        cout << i << ": " << (*it).first << ", " << (*it).second << endl;
        i++;
    }
    */

    //===== String HashMap =====
    HashMapS strings(true);
    strings["Mostly Cloudy"]++; // Do this 
    strings.printTable();
    strings.insertion("Mostly Cloudy", 50);
    strings.insertion("Clear", 32);
    strings.insertion("Scattered Clouds", 12);
    strings.insertion("Overcast", 234);
    strings.insertion("Fair", 34);
    strings.insertion("Heavy Rain", 80);
    strings.insertion("Light Thunderstorms and Rain", 324);
    strings.deletion("Hi");

    strings.printTable();

    cout << strings.searchMap("Heavy Rain").second << endl;
    vector<pair<string, int>> pairsS = strings.freqeuntKeys();
    int i = 1;
    for (auto it = pairsS.rbegin(); it != pairsS.rend(); it++)
    {
        cout << i << ": " << (*it).first << ", " << (*it).second << endl;
        i++;
    }
    

    //===== Double HashMap =====
    HashMapD doubles(true);
    doubles.insertion(72.2, 43);
    doubles.insertion(0.2, 34);
    doubles[72.2]++;
    doubles.printTable();
    doubles.insertion(2.4, 54);
    doubles.insertion(2.6, 14);
    doubles.insertion(8.7, 11);
    doubles.printTable();

    cout << doubles.searchMap(8.7).second << endl;
    vector<pair<double, int>> pairsD = doubles.freqeuntKeys();
    i = 1;
    for (auto it = pairsD.rbegin(); it != pairsD.rend(); it++)
    {
        cout << i << ": " << (*it).first << ", " << (*it).second << endl;
        i++;
    }


}


