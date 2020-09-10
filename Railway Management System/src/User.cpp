#include "User.h"
#include "../StationTree.h"

User::User(): name("")  // constructor
{

}

void User::viewTimeTable () //shows schedule for a particular station
{
    string str;
    system("CLS");  // clear screen
    cout<<endl; // leave a line gap at top

    cout<<"  Enter Station Name: "; // get station name as input
    cin>>str;
    Station *s = getStation(str);   //retrieve station
    if (s == NULL)                  //invalid input
    {
        cout<<"  No such station exists."<<endl;
        cout<<"  ";
        system("PAUSE");    // wait for user to read message
        return; // return to main menu
    }
    int i = 0;
    Train *t = s->getTrain(i);  // retrieve each train in turn
    if (t == NULL)  // if there are no trains
    {
        cout<<"  Schedule empty.\n  ";
        system("Pause");    // wait for use to read message
        return; // return to main menu
    }
    cout<<"      ID"<<"  Arrival"<<"  Departure"<<endl;   //headers for output
    while (t != NULL)   // while trains are available
    {
        for (int j=0; j<MAXSTATIONS; j++)   // loop over each station in train's list to find index of valid one
        {
            if (t->getStation(j) == str)        //when station is found in trains directory, show ID and times
            {
                cout<<"  "<<i+1<<". ";  // numbered list
                cout<<setfill('0')<<setw(3)<<t->getID()<<"  ";  // using manipulator to display as three digit numbers

                if (t->getArrTime(j) == "-1")   cout<<setfill(' ')<<setw(7)<<"Start"<<"  "; // starting station with no arrival time
                else    cout<<setfill(' ')<<setw(7)<<t->getArrTime(j)<<"  ";

                if (t->getDeptTime(j) == "-1")  cout<<setw(9)<<"End"<<endl; // ending station with no departure time
                else    cout<<setw(9)<<t->getDeptTime(j)<<endl;
            }
        }
        i++;    // go to next train
        if (i < MAXTRAINS)  t = s->getTrain(i); // while in range
        else    break;
    }
    cout<<"  ";
    system("PAUSE");    // wait for user to read messages
}


