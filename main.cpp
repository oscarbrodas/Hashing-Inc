#include <iostream>
#include <SDL.h>
#include "Interface.h"
#include "dataPoint.h"

using namespace std;



int main(int argc, char* args[]) {

	array2d sectors;
	fstream myfile("filtered2.csv");
	if (myfile.is_open()) {
		double lati, longi, distance, temp, humidity, visibility;
		string weather;
		myfile >> weather;

		string s;
		getline(myfile, s);
		int i = 0; // for error catching on inserts
		while (!myfile.eof()) {
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

    if (!display.isOpen())
        cout << "Failed to create window. Error: " << SDL_GetError() << endl;

    bool closed = false;
    SDL_Event* e = nullptr;
    while (!closed) {
        display.updateSurface();

        while (display.pollForEvent()) {

                if  (display.getEvent()->type == SDL_QUIT) {
                    closed = true;
                    break;
                }

                for (auto b : display.getCB())
                    b.handle_event(display.getEvent(), display.getRenderer());

                for (auto b : display.getDSB())
                    b.handle_event(display.getEvent());





        }

    }

    display.close();

    return 0;
}


