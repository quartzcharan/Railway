#include <iostream>
#include "StationTree.h"
using namespace std;

node* node::root = new node();


Station* getStation (string str)    //retrieving a station
{
    node* x = new node();
    x = x->root;      //setting a node to root
    int len = str.length();
    for (int i=0; i<len; i++)   //going down to last alphabet
    {
        int id = str[i] - 'a';
        if (x->next[id] == NULL)    return NULL;    //if required alphabet is unavailable even once, station does not exist
        x = x->next[id];
    }
    return x->s;    //return the station; this returns NULL if given string is prefix of a station name
}

void addStation (string str, Station* newStation)
{
    node* x = new node();
    x = x->root;              //setting a node to the root
    int len = str.length();
    for (int i=0; i<len; i++)       //going down to last alphabet
    {
        int id = str[i] - 'a';
        if (x->next[id] == NULL)    x->next[id] = new node();   // if required alphabet is unavailable, create new node
        x = x->next[id];
    }

    x->s = newStation;   //create new station object
    x->s->setLocation(str); //set the location
}

void clearStations(string stationName, int trainID)  // removes train from station
{
    Station* temp = getStation(stationName);    // retrieve station from trie
    if (temp != NULL)   // if station exists
    {
        for (int i=0; i<MAXTRAINS; i++) // find given train
        {
            Train* tempTrain = temp->getTrain(i);   // retrieve train
            if(tempTrain != NULL && tempTrain->getID() == trainID)   temp->setTrain(NULL, i);
            // if valid train is found, remove it
        }
    }
}

void clearTrains(Station* tempStation)  // deletes all trains associated with a station
{
    for (int i=0; i<MAXTRAINS; i++) // get each of the trains in turn
    {
        Train* temp;
        temp = tempStation->getTrain(i);    // retrieve train
        if (temp != NULL)   // if train exists
        {
            for (int j=0; j<MAXSTATIONS; j++)   clearStations(temp->getStation(j), temp->getID()); // remove this train from all stations associated with it
        }
        delete temp;    // delete train
    }
}

void deleteTree(node* x)    // delete all stations and trains
{
    if (x == NULL)  // for first call
    {
        x = new node(); // start at root
        x = x->root;
    }

    if (x->s != NULL)   // if a station is found at a node
    {
        clearTrains(x->s);  // delete all the trains associated with the station
        delete x->s;    // delete station
    }

    for (int i=0; i<26; i++)    // for each of the child nodes
    {
        if (x->next[i] != NULL) deleteTree(x->next[i]); // call function recursively if node exists
    }

    delete x;   // delete self
}
