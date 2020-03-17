#include<iostream>
#ifndef STATION_H
#define STATION_H
#define MAXCONN 2


class Station
{
    public:
        Station();
        Station(std::string str);

        std::string Getlocation() { return location; }
        void Setlocation(std::string val) { location = val; }

        Station *connection[MAXCONN];   //public for time being while I figure out how to make the connections nicely

    protected:

    private:
        std::string location;
};

#endif // STATION_H
