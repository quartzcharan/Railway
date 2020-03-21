#include <iostream>
#ifndef STATION_H
#define STATION_H
#include <Train.h>
using namespace std;


class Station
{
    public:
        Station();
        //removed single argument constructor since object creation being handled by function
        void setLocation (string str) { location = str; }
        string getLocation() { return location; }
        void setTrain (Train *tr, int i) { t[i] = tr; }
        Train* getTrain (int i) { return t[i]; }
        //total number of trains are not required
        //we can just loop through the array until we reach a null value


    protected:

    private:
        string location;    //location of train; used in trie
        Train *t[3];
};

#endif // STATION_H
