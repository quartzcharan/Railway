#include "Administrator.h"
#include "../StationTree.h"


Administrator::Administrator() : adminId(adminCount+1), pass("")
{
    adminCount++;
}

int Administrator::adminCount = 0;


void Administrator::createStation (string str, int mode)     //creating a new station
{
    if (mode == 0)
    {
        cout<<"Enter station name: ";
        cin>>str;
    }
    if (getStation(str) != NULL)           //possible that station already created
    {
        cout<<"Station already exists."<<endl;
        system("PAUSE");
        return;
    }
    else
    {
        Station* newStation = new Station();
        addStation(str, newStation);
    }
    if (mode == 0)
    {
        fstream openFile;
        openFile.open("\Stations.txt", ios_base::app);
        if (!openFile)  //problem reading file; return to main menu
        {
            cout<<"Unable to open file 'Stations.txt'.\n"<<endl;
            system("PAUSE");
            return;
        }
        openFile<<str<<endl;
        openFile.close();
    }
}

void Administrator::createTrain(int n, string stations[],string deptTimes[], string arrTimes[], float distances[], int mode)
{
    if (mode == 0)
    {
        cout<<"Enter number of stations train will pass through: ";
        cin>>n;
        stations = new string[n];
        deptTimes = new string[n];
        arrTimes = new string[n];
        distances = new float[n];
        cout<<"Enter station names: ";
        for (int i=0; i<n; i++) cin>>stations[i];
        cout<<"Enter departure times: ";
        for (int i=0; i<n; i++) cin>>deptTimes[i];
        cout<<"Enter arrival times: ";
        for (int i=0; i<n; i++) cin>>arrTimes[i];
        cout<<"Enter distances: ";
        for (int i=0; i<n; i++) cin>>distances[i];
    }

    int ind[n] = {0};   //will store index at which to put the train at each station
    Station* s[n];      //pointers to the station
    for (int i=0; i<n; i++)
    {
        s[i] = getStation(stations[i]); //retrieving ith station
        if (s[i] == NULL)
        {
            cout<<stations[i]<<" is not a valid station name."<<endl;
            system("PAUSE");
            return;
        }
        Train *t = s[i]->getTrain(ind[i]);
        while (t != NULL && ind[i] < MAXSTATIONS) //finding first non-NULL spot in ith station
        {
            for (int j=0; j<MAXSTATIONS; j++)
            {
                if (t->getStation(j) == s[i]->getLocation())        //when station is found in trains directory, show ID and times
                {
                    if((t->getArrTime(j) == arrTimes[i] && arrTimes[i] != "-1") || (t->getDeptTime(j) == deptTimes[i] && deptTimes[i] != "-1"))
                    {
                        cout<<"Invalid time at station "<<s[i]->getLocation()<<endl;
                        system("PAUSE");
                        return;
                    }
                }
            }
            ind[i]++;
            t = s[i]->getTrain(ind[i]);
        }
        if (ind[i] == MAXSTATIONS)    //station has no space; cannot continue program
        {
            cout<<"Unable to add train to "<<s[i]->getLocation()<<" station."<<endl;
            system("PAUSE");
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

    if (mode == 0)
    {
        fstream openFile;
        openFile.open("\Trains.txt", ios_base::app);
        if (!openFile)  //problem reading file; return to main menu
        {
            cout<<"Unable to open file 'Trains.txt'.\n"<<endl;
            system("PAUSE");
            return;
        }
        openFile<<"Train"<<endl;
        openFile<<n<<endl;
        for (int i=0; i<n; i++) openFile<<stations[i]<<" ";
        openFile<<endl;
        for (int i=0; i<n; i++) openFile<<deptTimes[i]<<" ";
        openFile<<endl;
        for (int i=0; i<n; i++) openFile<<arrTimes[i]<<" ";
        openFile<<endl;
        for (int i=0; i<n; i++) openFile<<distances[i]<<" ";
        openFile<<endl;
        openFile<<endl;
        openFile.close();

        delete stations;
        delete deptTimes;
        delete arrTimes;
        delete distances;
    }
}
