#include<iostream>
#include "Station.h"
#include "Train.h"
using namespace std;

Station::Station() : location("")
{
    for (int i=0; i<3; i++)   trainArr[i] = NULL;
}

Station::Station(string str) : location(str)
{
    for (int i=0; i<3; i++)   trainArr[i] = NULL;
}
