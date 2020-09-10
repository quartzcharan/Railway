#include "Customer.h"
#include "../StationTree.h"
#include "Train.h"
#include "Station.h"
#include "Ticket.h"
#define MAXSUGGESTIONS 10   // maximum number of results user is shown

Customer::Customer()
{

}

void Customer::bookTicket()    //search for available trains for routes selected by passengers
{
    string dept, arr;
    int passengers;

    system("CLS");  // clearing screen
    cout<<endl; // leave a line gap at top

    //getting user input
    cout<<"\n  Enter departure station name: ";
    cin>>dept;
    cout<<"  Enter arrival station name: ";
    cin>>arr;
    cout<<"  Enter number of passengers: ";
    cin>>passengers;

    Train* validtrains[MAXSUGGESTIONS];     //to store trains that are valid for this journey
    int validDeptIndexes[MAXSUGGESTIONS];   //indexes inside each train at which the departure station lies; used to display departure times
    int validArrIndexes[MAXSUGGESTIONS];    //same as above for arrival stations and arrival times
    bool business[MAXSUGGESTIONS];          //confirms that business class seats are available
    bool economy[MAXSUGGESTIONS];           //same as above for economy class seats
    Station *s = getStation(dept);  //retrieving departure station
    if (s == NULL)  // invalid departure point
    {
        cout<<"  Departure point invalid."<<endl;
        cout<<"  ";
        system("PAUSE");
        return;
    }
    int i = 0, k = 0;
    Train *t = s->getTrain(i);  //each train from departure station being retrieved in turn
    while (t != NULL && i<MAXTRAINS)    //while trains are available and station capacity not exceeded
    {
        if (k == MAXSUGGESTIONS)    break;  //maximum number of options given to user
        int deptInd = -1, arrInd = -1;  //index for departure and arrival stations for ith train
        for (int j=0; j<MAXSTATIONS; j++) //for each station in the trains list
        {
            if (t->getStation(j) == dept)   deptInd = j;  //departure station found
            if (t->getStation(j) == arr)    arrInd = j;   //arrival station found
        }
        int flag = -1;  // used to track that a valid train was found
        if (deptInd != -1 && arrInd != -1 && deptInd < arrInd)  //check if required number of seats are available from departure to arrival station
        {
            flag = 0;   // valid for now
            for (int j=deptInd; j<arrInd; j++)  // check seats available at each point
                if (t->getSeatsRemainingEconomy(j) < passengers && t->getSeatsRemainingBusiness(j) < passengers)    flag = 1;   // not enough seats in either category, so becomes invalid
        }
        if (flag == 0)  //if everything is good, store train and the departure and arrival indexes so it can be displayed
        {
            validtrains[k] = t;
            validDeptIndexes[k] = deptInd;
            validArrIndexes[k] = arrInd;
            k++;    // increment number of results found
        }
        i++;
        t = s->getTrain(i); // get next train from this station
    }
    if (k == 0) //k will be 0 if no trains are found
    {
        cout<<"  There are no available trains."<<endl;
        cout<<"  ";
        system("PAUSE");    // wait for user to see message
        return; // return to main menu
    }

    system("CLS");  // clear screen
    cout<<endl; // leave a line gap at the top

    cout<<"  Departure: "<<dept<<"\n  Arrival: "<<arr<<"\n\n"<<endl;    // heading for results

    for (int j=0; j<k; j++) //displaying valid trains
    {
        cout<<"\n  "<<j+1<<". ";    // numbered ordered
        cout<<"\n  Train ID: "<<validtrains[j]->getID();
        cout<<"\n  Departure Time: "<<validtrains[j]->getDeptTime(validDeptIndexes[j]);
        cout<<"\n  Arrival Time: "<<validtrains[j]->getArrTime(validArrIndexes[j]);

        if (validtrains[j]->getSeatsRemainingBusiness(validDeptIndexes[j]) >= passengers)   //if business class seats are available
        {
            business[j] = 1;    // indicate that business class available for this train
            cout<<"\n  Business Class Ticket Price (Per Person): BDT "<<2*(validtrains[j]->getDistanceBetween(validDeptIndexes[j], validArrIndexes[j]));    // calculating price based on distance between departure and arrival points
            cout<<"\n\tTotal Price ("<<passengers<<" passengers): BDT "<<passengers*2*(validtrains[j]->getDistanceBetween(validDeptIndexes[j], validArrIndexes[j]));
        }
        else
            business[j] = 0;    // indicate that business class not available for this train
        if (validtrains[j]->getSeatsRemainingEconomy(validDeptIndexes[j]) >= passengers)    //if economy class seats are available
        {
            economy[j] = 1; // indicate that economy class available for this train
            cout<<"\n  Economy Class Ticket Price (Per Person): BDT "<<(validtrains[j]->getDistanceBetween(validDeptIndexes[j], validArrIndexes[j]));   // calculating price based on distance between departure and arrival points
            cout<<"\n\tTotal Price ("<<passengers<<" passengers): BDT "<<passengers*(validtrains[j]->getDistanceBetween(validDeptIndexes[j], validArrIndexes[j]));
        }
        else
            economy[j] = 0; // indicate that economy class not available for this train
    }
    int choiceTrain = -1, choiceSeat = -1;  // used to keep track of which train and which category user picks
    while (choiceTrain == -1 || choiceSeat == -1)   // while invalid entries
    {
        cout<<"\n\n  Please chose a train: "; //getting chosen train
        cin>>choiceTrain;
        if (choiceTrain < 1 || choiceTrain > k) // invalid input
        {
            cout<<"  Invalid choice."<<endl;
            choiceTrain = -1;
            continue;
        }
        if (business[choiceTrain-1] == 1 && economy[choiceTrain-1] == 1)    //getting chosen class
        {
            cout<<"\n  Please choose a ticket class:";
            cout<<"\n  1. Business Class\n  2. Economy Class\n\n  Choice: ";
            cin>>choiceSeat;
        }
        else if (business[choiceTrain-1] == 1)  choiceSeat = 1; //or automatically assign if only one is available
        else if (economy[choiceTrain-1] == 1)   choiceSeat = 2;
        if (choiceSeat < 1 || choiceSeat > 2)   // invalid choice
        {
            cout<<choiceSeat<<endl;
            cout<<"  Invalid choice."<<endl;
            choiceSeat = -1;
            continue;
        }
    }

    string custName, custPhNum; // need name and phone number
    cout<<"\n  Please enter your name and phone number to confirm the booking.\n  Name: ";
    cin>>custName;
    cout<<"  Phone Number: ";
    cin>>custPhNum;

    Ticket tempTicket(custName, custPhNum, dept, validDeptIndexes[choiceTrain-1], validArrIndexes[choiceTrain-1], validtrains[choiceTrain-1]->getID(), choiceSeat, passengers);
    if (tempTicket.store()) // successfully stored booking information in external file
    {
        tempTicket.bookSeats(); // books seats in the train
        cout<<"\n  Seats booked."<<endl;    // confirm booking
        cout<<"  ";
        system("PAUSE");    // wait for user to read
    }
}

void Customer::viewBooking()    // view booked tickets for particular customer; overloaded from parent
{
    string custName, custPhNum;
    system("CLS");  // clear screen
    cout<<endl; // leave a line gap at the top
    cout<<"  Please enter your name and phone number to view the booking.\n  Name: ";   // get name and phone number to check for bookings
    cin>>custName;
    cout<<"  Phone Number: ";
    cin>>custPhNum;

    Ticket tempTicket;  // create Ticket object
    cout<<endl; // leave a line gap
    tempTicket.read(1, custName, custPhNum, -1);  // call read function
    cout<<"  ";
    system("Pause");    // wait for user to read any messages
}
