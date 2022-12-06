#include <iostream>
#include <algorithm>
#include <ctime>
#include "SDL.h"
#include "Interface.h"
#include "HashMapD.h"
#include "HashMapS.h"
#include "datapoint.h"


using namespace std;

vector<vector<double>> mostFrequentConditions(pair<int, int> coords, array2d& sectors, bool hashFunctionA);
vector<string> weatherMostFrequent(pair<int, int> coords, array2d& sectors, bool hashFunctionA);

bool HASH = true;

int main(int argc, char* args[]) {

    array2d sectors;
    fstream myfile("../src/filtered2.csv");
    if (myfile.is_open()) {
        double lati, longi, distance, temp, humidity, visibility;
        string weather;
        myfile >> weather;

        string s;
        getline(myfile, s);
        int i = 0; // for error catching on inserts
        while (!myfile.eof() && i < 200000) {
            try {
                getline(myfile, s);
                istringstream in(s);
                if (s == "") continue;

                getline(in, s, ',');
                lati = stod(s);
                getline(in, s, ',');
                longi = stod(s);
                getline(in, s, ',');
                distance = stod(s);
                getline(in, s, ',');
                getline(in, s, ',');
                temp = stod(s);
                getline(in, s, ',');
                humidity = stod(s);
                getline(in, s, ',');
                visibility = stod(s);
                getline(in, weather, ',');

                longi = longi * -1.0;
                sectors.insert(dataPoint(lati, longi, distance, temp, humidity, visibility, weather));
            }
            catch (...) { cout << "Data insertion error at: " << i << endl; }
            i++;
        }
    }
    else cout << "file did not open\n";

    Interface display;
    clock_t timer;

    if (!display.isOpen())
        cout << "Failed to create window. Error: " << SDL_GetError() << endl;

    // Window loop
    bool closed = false;
    SDL_Event* e = nullptr;
    pair<int, int> loc = {0,0}, tmp;
    vector<string> stringData;
    vector<vector<double>>  numericData;
    while (!closed) {
        display.updateWindow();

        while (display.pollForEvent()) {

            // Quit Window
            if  (display.getEvent()->type == SDL_QUIT) {
                closed = true;
                break;
            }

            for (auto b : display.getCButtons()){
                tmp = b.handle_event(display.getEvent(), display.getRenderer());

                // Use search function to get vectors of data based on table
                if (display.getEvent()->type == SDL_MOUSEBUTTONDOWN)
                    if (loc.first != tmp.first && loc.second != tmp.second) {
                        loc = tmp;

                        // Start Time
                        timer = clock();

                        // Gather data
                        numericData = mostFrequentConditions(loc, sectors, HASH);
                        stringData = weatherMostFrequent(loc, sectors, HASH);

                        // End Time, Update Timer
                        timer = clock() - timer;
                        display.updateTime(timer);

                        // Update table based on location
                        display.updateTable(numericData, stringData);
                    }

                loc.first = 0;
                loc.second = 0;

            }

            if (display.getEvent()->type == SDL_MOUSEBUTTONDOWN) {
                for (auto b : display.getDSButtons())
                    b.handle_event(display.getEvent(), HASH);
            }
            
        }

    }

    display.close();

    return 0;
}

vector<vector<double>> mostFrequentConditions(pair<int, int> coords, array2d& sectors, bool hashFunctionA) {
    int x = coords.first;
    int y = coords.second;

    HashMapD distance(hashFunctionA);
    HashMapD temperature(hashFunctionA);
    HashMapD humidity(hashFunctionA);
    HashMapD visibility(hashFunctionA);

    for (int i = 0; i < sectors.at(x, y).size(); i++) {
        distance[sectors.at(x, y).at(i)->distance]++;
        temperature[sectors.at(x, y).at(i)->temp]++;
        humidity[sectors.at(x, y).at(i)->humidity]++;
        visibility[sectors.at(x, y).at(i)->visibility]++;
    }

    vector<vector<double>> r;
    vector<double> temp;
    for (auto i : distance.freqeuntKeys()) {
        temp.push_back(i.first);
    }
    reverse(temp.begin(), temp.end());
    r.push_back(temp);
    temp.clear();

    for (auto i : temperature.freqeuntKeys()) {
        temp.push_back(i.first);
    }
    reverse(temp.begin(), temp.end());
    r.push_back(temp);
    temp.clear();

    for (auto i : humidity.freqeuntKeys()) {
        temp.push_back(i.first);
    }
    reverse(temp.begin(), temp.end());
    r.push_back(temp);
    temp.clear();

    for (auto i : visibility.freqeuntKeys()) {
        temp.push_back(i.first);
    }
    reverse(temp.begin(), temp.end());
    r.push_back(temp);
    temp.clear();

    for (auto i : r) {
        while (i.size() < 10) i.push_back(0);
    }

    return r;
}
vector<string> weatherMostFrequent(pair<int, int> coords, array2d& sectors, bool hashFunctionA) {
    int x = coords.first;
    int y = coords.second;
    HashMapS weather(hashFunctionA);

    for (int i = 0; i < sectors.at(x, y).size(); i++) {
        weather[sectors.at(x, y).at(i)->weather]++;
    }

    vector<string> r;
    for (auto i : weather.freqeuntKeys()) {
        r.push_back(i.first);
    }
    reverse(r.begin(), r.end());

    while (r.size() < 10) r.emplace_back("N/A");

    return r;
}