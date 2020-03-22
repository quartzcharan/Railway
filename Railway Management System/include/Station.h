#include <iostream>
#ifndef STATION_H
#define STATION_H
#include <Train.h>
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
        string location;    //location of train; used in trie
        Train *t[3];
};

#endif // STATION_H
