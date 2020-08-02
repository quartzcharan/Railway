#include "Administrator.h"
#include "../StationTree.h"


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
