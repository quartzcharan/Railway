#include <Station.h>

struct node             //structure for each node
{
    Station* s;         //last alphabet of station name will store pointer to station object
    static node* root;  //every node keeps track of root, so root does not need to be called in each functions argument
    node* next[26];     //each of the 26 alphabets
    node()
    {
        s = NULL;
        for (int i=0; i<26; i++)    next[i] = NULL;
    }
};

node* node::root = new node();

void createStation (string str)     //creating a new station
{
    node* x = x->root;              //setting a node to the root
    int len = str.length();
    for (int i=0; i<len; i++)       //going down to last alphabet
    {
        int id = str[i] - 'a';
        if (x->next[id] == NULL)    x->next[id] = new node();
        x = x->next[id];
    }
    if (x->s != NULL)           //possible that station already created
    {
        cout<<"Station already exists."<<endl;
        return;
    }
    x->s = new Station();   //create new station object
    x->s->setLocation(str); //set the location
}

Station* getStation (string str)    //retrieving a station
{
    node* x = x->root;      //setting a node to root
    int len = str.length();
    for (int i=0; i<len; i++)   //going down to last alphabet
    {
        int id = str[i] - 'a';
        if (x->next[id] == NULL)    return NULL;    //if required alphabet is unavailable even once, station does not exist
        x = x->next[id];
    }
    return x->s;    //return the station; this returns NULL if given string is prefix of a station name
}
