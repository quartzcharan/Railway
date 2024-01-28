#ifndef STATIONTREE_H_INCLUDED
#define STATIONTREE_H_INCLUDED
#include "src/Station.h"

struct node             //structure for each node
{
    Station* s;         //last alphabet of station name will store pointer to station object
    static node* root;  //every node keeps track of root, so root does not need to be called in each functions argument
    node* next[26];     //each of the 26 alphabets
    node()  // constructor
    {
        s = NULL;
        for (int i=0; i<26; i++)    next[i] = NULL;
    }
};

Station* getStation (string str);
void addStation (string str, Station* newStation);

void clearStations(string stationName);
void clearTrains(Station* temp);
void deleteTree(node* x = NULL);

#endif // STATIONTREE_H_INCLUDED
