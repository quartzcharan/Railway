#include<iostream>
#ifndef STATION_H
#define STATION_H
#include<Train.h>


class Station
{
    public:
        Station();
        Station(std::string str);

        std::string Getlocation() { return location; }
        void Setlocation(std::string val) { location = val; }

        void setTrain(Train *t, int ind) { trainArr[ind] = t; }
        Train getTrain(int i) { return *trainArr[i]; }



    protected:

    private:
        std::string location;   //location of train; used in trie
        Train *trainArr[3];
};

#endif // STATION_H
