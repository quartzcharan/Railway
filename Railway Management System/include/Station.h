#ifndef STATION_H
#define STATION_H
#define MAXTRAINS 3  // maximum number of trains a station can hold at once
#include "Train.h"
#include <iostream>
using namespace std;


class Station
{
public:
    Station();
    void setLocation (string str) { location = str; }
    string getLocation() { return location; }
    void setTrain (Train *tr, int i) { t[i] = tr; }
    Train* getTrain (int i) { return t[i]; }

protected:

private:
    string location;    //location of station; used in trie
    Train *t[MAXTRAINS];
};

#endif // STATION_H
