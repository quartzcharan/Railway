#include <Train.h>
#include <Station.h>
void createTrain(int n, string stations[], int deptTimes[], int arrTimes[])
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
        t->setStation(stations[i], i);      //set station names, departure and arrival times for the train
        t->setDeptTime(deptTimes[i], i);
        t->setArrTime(arrTimes[i], i);
        s[i]->setTrain(t, ind[i]);          //train t stops at each station s at the first index at which there is space
    }
}

void bookTicket(string dept, string arr, int passengers)    //search for available trains for routes selected by passengers
{
    Train* validtrains[10];     //to store trains that are valid for this journey
    int validDeptIndexes[10];   //indexes inside each train at which the departure station lies; used to display departure times
    int validArrIndexes[10];    //same as above for arrival stations and arrival times
    Station *s = getStation(dept);  //retrieving departure station
    if (s == NULL)
    {
        cout<<"Departure point invalid."<<endl;
        return;
    }
    int i = 0, k = 0;
    Train *t = s->getTrain(i);  //each train from departure station being retrieved in turn
    while (t != NULL && i<3)    //while trains are available and i<3 (max number of trains in each station)
    {
        if (k == 10)    break;  //maximum number of options given to user
        int deptInd = -1, arrInd = -1;  //index for departure and arrival stations for ith train
        for (int j=0; j<3; j++) //for each station in the trains list
        {
            if (t->getStation(j) == dept) deptInd = j;  //departure station found
            if (t->getStation(j) == arr)  arrInd = j;   //arrival station found
        }
        int flag = -1;
        if (deptInd != -1 && arrInd != -1 && deptInd < arrInd)  //check if required number of seats are available from departure to arrival station
        {
            flag = 0;
            for (int j=deptInd; j<arrInd; j++)  if (t->getSeatsRemaining(j) < passengers)   flag = 1;
        }
        if (flag == 0)  //if everything is good, store train and the departure and arrival indexes so it can be displayed
        {
            validtrains[k] = t;
            validDeptIndexes[k] = deptInd;
            validArrIndexes[k] = arrInd;
            k++;
        }
        i++;
        t = s->getTrain(i);
    }
    if (k == 0) //k will be 0 if no trains are found
    {
        cout<<"There are no available trains."<<endl;
        return;
    }
    cout<<"  Train ID\tDeparture\tArrival"<<endl;   //displaying valid trains
    for (int j=0; j<k; j++)
    {
        cout<<j+1<<". ";
        cout<<validtrains[j]->getID()<<"\t\t";
        cout<<validtrains[j]->getDeptTime(validDeptIndexes[j])<<"\t\t";
        cout<<validtrains[j]->getArrTime(validArrIndexes[j])<<endl;
    }
    cout<<"Please chose a train: "; //getting chosen train
    int choice;
    cin>>choice;

    for (int j=validDeptIndexes[choice-1]; j<validArrIndexes[choice-1]; j++)    //changing available seats for chosen train
    {
        int seats = validtrains[choice-1]->getSeatsRemaining(j);
        validtrains[choice-1]->setSeatsRemaining(seats - passengers, j);
    }
    cout<<"Seats booked."<<endl;
}

void viewTimeTable (string str) //shows schedule for a particular station
{
    Station *s = getStation(str);   //retrieve station
    if (s == NULL)                  //station not found
    {
        cout<<"No such station exists."<<endl;
        return;
    }
    int i = 0;
    Train *t = s->getTrain(i);
    cout<<"  Train ID\tArrival\tDeparture"<<endl;   //showing each train until NULL
    while (t != NULL)
    {
        for (int j=0; j<3; j++)
        {
            if (t->getStation(j) == str)        //when station is found in trains directory, show ID and times
            {
                cout<<i+1<<". ";
                cout<<t->getID()<<"\t\t";
                cout<<t->getArrTime(j)<<"\t";
                cout<<t->getDeptTime(j)<<endl;
            }
        }
        i++;
        t = s->getTrain(i);
    }
}
