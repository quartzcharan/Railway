#include "Administrator.h"
#include "../StationTree.h"


Administrator::Administrator() : adminId(adminCount+1), pass("")    // constructor
{
    adminCount++;   // increase count for administrator accounts
}

int Administrator::adminCount = 0;  // initializing static variable


void Administrator::createStation (string str, int mode)     //creating a new station
{
    system("CLS");  // clear screen
    cout<<endl; // leave a line gap at top

    if (mode == 0)  // mode 0 for manual entry; otherwise used by setup function so no entry required
    {
        cout<<"  Enter station name: ";
        cin>>str;
    }
    if (getStation(str) != NULL)           //possible that station already created
    {
        cout<<"  Station already exists."<<endl;
        cout<<"  ";
        system("PAUSE");    // wait to allow user to see message
        return;
    }
    if (mode == 0)  // manual entry means new station (not in file)
    {
        fstream openFile;
        openFile.open("\Stations.txt", ios_base::app);  // opening file in append mode
        if (!openFile)  //problem reading file; return to main menu
        {
            cout<<"  Unable to open file 'Stations.txt'.\n"<<endl;
            cout<<"  ";
            system("PAUSE");    // pause to allow user to read
            return; // unable to add to file so must leave; will cause inconsistencies if we continue
        }
        openFile<<str<<endl;    // add station name to file
        openFile.close();
    }

    Station* newStation = new Station();    // allocate memory for new station object
    addStation(str, newStation);    // add station to trie
}

void Administrator::createTrain(int n, string stations[],string deptTimes[], string arrTimes[], float distances[], int mode)    // creating a new train
{
    system("CLS");  // clear the screen
    cout<<endl; // leave one line gap at top
    if (mode == 0)  // mode 0 for manual entry; otherwise used by setup function so does not need entries
    {
        cout<<"  Enter number of stations train will pass through: ";
        cin>>n;
        stations = new string[n];   // allocating memory to arrays as needed
        deptTimes = new string[n];
        arrTimes = new string[n];
        distances = new float[n];
        cout<<"  Enter station names: ";    // storing entries in arrays
        for (int i=0; i<n; i++) cin>>stations[i];
        cout<<"  Enter departure times: ";
        for (int i=0; i<n; i++) cin>>deptTimes[i];
        cout<<"  Enter arrival times: ";
        for (int i=0; i<n; i++) cin>>arrTimes[i];
        cout<<"  Enter distances: ";
        for (int i=0; i<n; i++) cin>>distances[i];
    }

    int ind[n] = {0};   //will store index at which to put the train at each station
    Station* s[n];      //pointers to the stations
    for (int i=0; i<n; i++) // for each station
    {
        s[i] = getStation(stations[i]); //retrieving ith station
        if (s[i] == NULL)   // if ith statin name was invalid
        {
            cout<<"  "<<stations[i]<<" is not a valid station name."<<endl;
            cout<<"  ";
            system("PAUSE");    // wait for user to read
            return; // incorrect input so leave
        }

        Train *t = s[i]->getTrain(ind[i]);  // retrieve the first train in the station
        while (t != NULL && ind[i] < MAXTRAINS) //looping over trains already present in station's list
        {
            for (int j=0; j<MAXSTATIONS; j++)   //find this station in train's list and check information
            {
                if (t->getStation(j) == s[i]->getLocation())        //found the station
                {
                    string arrNew, deptNew, arrOld, deptOld;
                    if (arrTimes[i] == "-1")    arrNew = to_string(0);  // very low value for train that starts from this station
                    else    arrNew = arrTimes[i];
                    if (deptTimes[i] == "-1")   deptNew = to_string(999);   // very high value for train that never leaves
                    else    deptNew = deptTimes[i];
                    if (t->getArrTime(j) == "-1")   arrOld = to_string(0);
                    else    arrOld = t->getArrTime(j);
                    if (t->getDeptTime(j) == "-1")  deptOld = to_string(999);
                    else    deptOld = t->getDeptTime(j);

                    /*
                        Errors occur if the given departure time is before the given arrival time,
                        or if there is some overlap with another train already in the station.
                        Checking errors such as the same time being given for one train at different stations,
                        or geographical inconsistencies is beyond the scope of this program.
                    */

                    if ((deptNew <= arrNew) || (arrNew < deptOld && arrOld < deptNew))
                    {
                        cout<<"  Invalid time at station "<<s[i]->getLocation()<<endl;
                        cout<<"  ";
                        system("PAUSE");    // wait for user to view message
                        return; //incorrect input so leave
                    }
                }
            }
            ind[i]++;   // move onto next train
            t = s[i]->getTrain(ind[i]); // retrieve next train in station
        }
        if (ind[i] == MAXTRAINS)    //station has no space; cannot continue program
        {
            cout<<"  Unable to add train to "<<s[i]->getLocation()<<" station."<<endl;
            cout<<"  ";
            system("PAUSE");    // wait for user to see message
            return; //incorrect input so leave
        }
    }

    if (mode == 0)  // for manual entry, add details of train to file
    {
        fstream openFile;
        openFile.open("\Trains.txt", ios_base::app);    //append mode
        if (!openFile)  //problem reading file; return to main menu
        {
            cout<<"  Unable to open file 'Trains.txt'.\n"<<endl;
            cout<<"  ";
            system("PAUSE");    // wait for user to see message
            return; // unable to add to file so must leave; will cause inconsistencies if we continue
        }
        openFile<<"Train"<<endl;    // adding data to file
        openFile<<n<<endl;  // number stations
        for (int i=0; i<n; i++) openFile<<stations[i]<<" "; // names of stations
        openFile<<endl;
        for (int i=0; i<n; i++) openFile<<deptTimes[i]<<" ";
        openFile<<endl;
        for (int i=0; i<n; i++) openFile<<arrTimes[i]<<" ";
        openFile<<endl;
        for (int i=0; i<n; i++) openFile<<fixed<<setprecision(1)<<distances[i]<<" ";
        openFile<<endl;
        openFile<<endl;
        openFile.close();
    }

    Train *t = new Train(); // allocate memory to new train object
    for (int i=0; i<n; i++)
    {
        t->setStation(stations[i], i);      //set station names, departure and arrival times and distances for the train
        t->setDeptTime(deptTimes[i], i);
        t->setArrTime(arrTimes[i], i);
        t->setDistanceToNext(distances[i], i);
        s[i]->setTrain(t, ind[i]);          //train t stops at each station s at the first index at which there is space
    }

    if (mode == 0)  // for manual entry; delete allocated memory
    {
        delete[] stations;    // deleting all the allocated memory in this function
        delete[] deptTimes;
        delete[] arrTimes;
        delete[] distances;
    }
}

void Administrator::viewBooking()   // function to view bookings for a particular train; overloaded from parent
{
    system("CLS");  // clear screen
    cout<<endl; // leave a line gap at the top

    int tid;
    cout<<"  Please enter Train ID: ";  // get train id as input
    cin>>tid;

    User::viewBooking("", "", tid, 2);  // pass to parent function; passing blanks for information not needed
}
