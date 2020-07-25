#include "Administrator.h"
#include "../StationTree.h"
#include <fstream>


Administrator::Administrator() : adminId(adminCount+1), pass("")
{
    adminCount++;
}

int Administrator::adminCount = 0;


void Administrator::createStation (string str)     //creating a new station
{
    if (getStation(str) != NULL)           //possible that station already created
    {
        cout<<"Station already exists."<<endl;
        return;
    }
    else
    {
        Station* newStation = new Station();
        addStation(str, newStation);
    }
}

void Administrator::createTrain(int n, string stations[], string deptTimes[], string arrTimes[], float distances[])
{
    int ind[n] = {0};   //will store index at which to put the train at each station
    Station* s[n];      //pointers to the station
    for (int i=0; i<n; i++)
    {
        s[i] = getStation(stations[i]); //retrieving ith station
        if (s[i] == NULL)
        {
            cout<<stations[i]<<" is not a valid station name."<<endl;
            return;
        }
        Train *t = s[i]->getTrain(ind[i]);
        while (t != NULL && ind[i] < 3) //finding first non-NULL spot in ith station
        {
            for (int j=0; j<3; j++)
            {
                if (t->getStation(j) == s[i]->getLocation())        //when station is found in trains directory, show ID and times
                {
                    if(t->getArrTime(j) == arrTimes[i] || t->getDeptTime(j) == deptTimes[i])
                    {
                        cout<<"Invalid time at station "<<s[i]->getLocation()<<endl;
                        return;
                    }
                }
            }
            ind[i]++;
            t = s[i]->getTrain(ind[i]);
        }
        if (ind[i] == 3)    //station has no space; cannot continue program
        {
            cout<<"Unable to add train to "<<s[i]->getLocation()<<" station."<<endl;
            return;
        }
    }

    Train *t = new Train();
    for (int i=0; i<n; i++)
    {
        t->setStation(stations[i], i);      //set station names, departure and arrival times and distances for the train
        t->setDeptTime(deptTimes[i], i);
        t->setArrTime(arrTimes[i], i);
        t->setDistanceToNext(distances[i], i);
        s[i]->setTrain(t, ind[i]);          //train t stops at each station s at the first index at which there is space
    }
}

void Administrator::setup()    //sets up all the stations and trains for the program to use
{
    fstream openFile;   //will store station and train files
    string str;         //store lines being read from files
    int num;            //stores integer numbers

    openFile.open("\Stations.txt"); //working with stations
    if (!openFile)                  //problem reading file; must stop program
    {
        cout<<"Unable to open file 'Stations.txt'.\nSetup failed.\nExiting Program.\n"<<endl;
        exit(1);
    }
    while (getline(openFile, str))
        createStation(str); //creating each of the stations

    openFile.close();   //done with stations

    openFile.open("\Trains.txt");   //working with trains
    if (!openFile)  //problem reading file; must stop program
    {
        cout<<"Unable to open file 'Trains.txt'.\nSetup failed.\nExiting Program.\n"<<endl;
        exit(1);
    }
    while (getline(openFile, str))  //creating each of the trains
    {
        openFile>>num;              //number of stations associated with train
        getline(openFile, str);     //go to next line
        string stations[num];       //storing everything to pass to createTrain function
        string deptTimes[num];
        string arrTimes[num];
        float dist[num];
        for (int i=0; i<num; i++)   //storing station names
        {
            getline(openFile, stations[i]);
        }
        for (int i=0; i<num; i++)   //storing departure times
        {
            openFile>>deptTimes[i];
            getline(openFile, str);
        }
        for (int i=0; i<num; i++)   //storing arrival times
        {
            openFile>>arrTimes[i];
            getline(openFile, str);
        }
        for (int i=0; i<num; i++)   //storing distance
        {
            openFile>>dist[i];
            getline(openFile, str);
        }
        createTrain(num, stations, deptTimes, arrTimes, dist);  //creating train
    }
}
