#include<iostream>
#include "Station.h"
using namespace std;

Station::Station() : location("")
{
    for (int i=0; i<MAXCONN; i++)   this->connection[i] = NULL;
}

Station::Station(string str)
{
    location = str;
    for (int i=0; i<MAXCONN; i++)   this->connection[i] = NULL;
}
