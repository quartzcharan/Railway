#include "User.h"
#include "../StationTree.h"

User::User(): name("")
{

}

void User::viewTimeTable () //shows schedule for a particular station
{
    string str;
    system("CLS");
    cout<<endl;
    cout<<"  Enter Station Name: ";
    cin>>str;
    Station *s = getStation(str);   //retrieve station
    if (s == NULL)                  //station not found
    {
        cout<<"  No such station exists."<<endl;
        cout<<"  ";
        system("PAUSE");
        return;
    }
    int i = 0;
    Train *t = s->getTrain(i);
    if (t == NULL)
    {
        cout<<"  Schedule empty.\n  ";
        system("Pause");
        return;
    }
    cout<<"  Train ID\tArrival\tDeparture"<<endl;   //showing each train until NULL
    while (t != NULL)
    {
        for (int j=0; j<MAXSTATIONS; j++)
        {
            if (t->getStation(j) == str)        //when station is found in trains directory, show ID and times
            {
                cout<<"  "<<i+1<<". ";
                cout<<t->getID()<<"\t\t";
                cout<<t->getArrTime(j)<<"\t";
                cout<<t->getDeptTime(j)<<endl;
            }
        }
        i++;
        if (i < MAXTRAINS)  t = s->getTrain(i); // while in range
        else    break;
    }
    cout<<"  ";
    system("PAUSE");
}
