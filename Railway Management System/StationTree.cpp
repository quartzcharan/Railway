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
