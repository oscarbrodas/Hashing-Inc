#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class dataPoint {
public:
	double lati, longi, distance, temp, humidity, visibility;
	string weather;

	dataPoint(double lati, double longi, double distance, double temp, double humidity, double visibility, string weather) {
		this->lati = lati;
		this->longi = longi;
		this->distance = distance;
		this->temp = temp;
		this->humidity = humidity;
		this->visibility = visibility;
		this->weather = weather;
	}
	dataPoint(const dataPoint& d) {
		this->lati = d.lati;
		this->longi = d.longi;
		this->distance = d.distance;
		this->temp = d.temp;
		this->humidity = d.humidity;
		this->visibility = d.visibility;
		this->weather = d.weather;
	}

	dataPoint() {

	}
};


/*
Don's Note:
array2d is only used to store the initial values of all of the data
*/
class array2d {
private:
	vector<dataPoint*> data[7][8]; // latitude first, longitude second
public:
	void insert(dataPoint d) {
		data[(int)d.lati - 24][(int)d.longi - 80].push_back(new dataPoint(d));
	}

	vector<dataPoint*> at(int latitude, int longitude) { // returns reference of vector of the sector
		latitude = latitude - 24;
		longitude = longitude - 80;

		return data[latitude][longitude];
	}
	~array2d() {
		for (int lati = 0; lati < 7; lati++) {
			for (int longi = 0; longi < 8; longi++) {
				for (auto p : data[lati][longi]) {
					delete p;
				}
				data[lati][longi].clear();
			}
		}
	}
};