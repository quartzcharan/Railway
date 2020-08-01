#include "Customer.h"
#include "../StationTree.h"
#include "Train.h"
#include "Station.h"

Customer::Customer() : phoneNum("")
{

}

void Customer::bookTicket()    //search for available trains for routes selected by passengers
{
    string dept, arr;
    int passengers;
    //getting user input
    system("CLS");
    cout<<"\n  Enter departure station name: ";
    cin>>dept;
    cout<<"  Enter arrival station name: ";
    cin>>arr;
    cout<<"  Enter number of passengers: ";
    cin>>passengers;

    Train* validtrains[10];     //to store trains that are valid for this journey
    int validDeptIndexes[10];   //indexes inside each train at which the departure station lies; used to display departure times
    int validArrIndexes[10];    //same as above for arrival stations and arrival times
    bool business[10];          //confirms that business class seats are available
    bool economy[10];           //same as above for economy class seats
    Station *s = getStation(dept);  //retrieving departure station
    if (s == NULL)
    {
        cout<<"  Departure point invalid."<<endl;
        cout<<"  ";
        system("PAUSE");
        return;
    }
    int i = 0, k = 0;
    Train *t = s->getTrain(i);  //each train from departure station being retrieved in turn
    while (t != NULL && i<3)    //while trains are available and i<3 (max number of trains in each station)
    {
        if (k == 10)
            break;  //maximum number of options given to user
        int deptInd = -1, arrInd = -1;  //index for departure and arrival stations for ith train
        for (int j=0; j<3; j++) //for each station in the trains list
        {
            if (t->getStation(j) == dept)
                deptInd = j;  //departure station found
            if (t->getStation(j) == arr)
                arrInd = j;   //arrival station found
        }
        int flag = -1;
        if (deptInd != -1 && arrInd != -1 && deptInd < arrInd)  //check if required number of seats are available from departure to arrival station
        {
            flag = 0;
            for (int j=deptInd; j<arrInd; j++)
                if (t->getSeatsRemainingEconomy(j) < passengers && t->getSeatsRemainingBusiness(j) < passengers)
                    flag = 1;
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
        cout<<"  There are no available trains."<<endl;
        cout<<"  ";
        system("PAUSE");
        return;
    }
    system("CLS");
    cout<<"  Departure: "<<dept<<"\n  Arrival: "<<arr<<"\n\n"<<endl;   //displaying valid trains
    for (int j=0; j<k; j++)
    {
        cout<<"  "<<j+1<<". ";
        cout<<"\n  Train ID: "<<validtrains[j]->getID();
        cout<<"\n  Departure Time: "<<validtrains[j]->getDeptTime(validDeptIndexes[j]);
        cout<<"\n  Arrival Time: "<<validtrains[j]->getArrTime(validArrIndexes[j]);
        if (validtrains[j]->getSeatsRemainingBusiness(validDeptIndexes[j]) >= passengers)   //if business class seats are available
        {
            business[j] = 1;
            cout<<"\n  Business Class Ticket Price (Per Person): BDT "<<2*(validtrains[j]->getDistanceBetween(validDeptIndexes[j], validArrIndexes[j]));
            cout<<"\n\tTotal Price ("<<passengers<<" passengers): BDT "<<passengers*2*(validtrains[j]->getDistanceBetween(validDeptIndexes[j], validArrIndexes[j]));
        }
        else
            business[j] = 0;
        if (validtrains[j]->getSeatsRemainingEconomy(validDeptIndexes[j]) >= passengers)    //if economy class seats are available
        {
            economy[j] = 1;
            cout<<"\n  Economy Class Ticket Price (Per Person): BDT "<<(validtrains[j]->getDistanceBetween(validDeptIndexes[j], validArrIndexes[j]));
            cout<<"\n\tTotal Price ("<<passengers<<" passengers): BDT "<<passengers*(validtrains[j]->getDistanceBetween(validDeptIndexes[j], validArrIndexes[j]));
        }
        else
            economy[j] = 0;
    }
    int choiceTrain = -1, choiceSeat = -1;
    while (choiceTrain == -1 || choiceSeat == -1)
    {
        cout<<"\n\n  Please chose a train: "; //getting chosen train
        cin>>choiceTrain;
        if (choiceTrain < 1 || choiceTrain > k)
        {
            cout<<"  Invalid choice."<<endl;
            choiceTrain = -1;
            continue;
        }
        if (business[choiceTrain-1] == 1 && economy[choiceTrain-1] == 1)    //getting chosen class
        {
            cout<<"\n  Please choose a ticket class:";
            cout<<"\n  1. Business Class\n  2. Economy Class\n  Choice: ";
            cin>>choiceSeat;
        }
        else if (business[choiceTrain-1] == 1)
            choiceSeat = 1; //or automatically assign if only one is available
        else if (economy[choiceTrain-1] == 1)
            choiceSeat = 2;
        if (choiceSeat < 1 || choiceSeat > 2)
        {
            cout<<choiceSeat<<endl;
            cout<<"  Invalid choice."<<endl;
            choiceSeat = -1;
            continue;
        }
    }


    for (int j=validDeptIndexes[choiceTrain-1]; j<validArrIndexes[choiceTrain-1]; j++)
        validtrains[choiceTrain-1]->occupySeat(choiceSeat, passengers, j);
    //changing available seats for chosen train
    // shift this look to Ticket class

    cout<<"\n  Seats booked."<<endl;
    cout<<"  ";
    system("PAUSE");
}
