#include<iostream>
using namespace std;
#include "Ticket.h"
#include <fstream>
#include <string.h>

Ticket::Ticket()
{

}

Ticket::Ticket(string custName, string custNum, string dept, int deptPnt, int arrPnt, int tid, int seatCat, int passengers): deptInd(deptPnt), arrInd(arrPnt), trainID(tid), seatCategory(seatCat), seats(passengers)
{
    strncpy(departure, dept.c_str(), sizeof(departure));    // forced to store as char array; otherwise problems storing to file
    strncpy(name, custName.c_str(), sizeof(name));
    strncpy(number, custNum.c_str(), sizeof(number));
}

int Ticket::store()
{
    fstream openFile;
    openFile.open("\Tickets.dat", ios::app|ios::binary);    // append and binary mode
    if (!openFile)  //problem reading file; return to main menu
    {
        cout<<"  Unable to open file 'Tickets.dat'.\n"<<endl;
        cout<<"  ";
        system("PAUSE");    // wait for use to read message
        return 0; // return to main menu
    }
    openFile.write((char*)this, sizeof(*this)); // write object to file
    openFile.close();
    return 1;
}

void Ticket::bookSeats()    // books seats on the train
{
    Station *tempStation = getStation(departure);   // retrieve station
    for (int i=0; i<MAXTRAINS; i++) // check each train
    {
        Train *tempTrain = tempStation->getTrain(i);    // retrieve train
        if (tempTrain != NULL && tempTrain->getID() == trainID)  // found valid train
        {
            for (int j=deptInd; j<arrInd; j++)  tempTrain->occupySeat(seatCategory, seats, j);  // decrement number of seats in required category at each point between departure and arrival (not including arrival)
        }
    }
}

void Ticket::read(int mode, string custName, string custNum, int tid)   // read tickets from external file
{
    ifstream openFile;
    openFile.open("\Tickets.dat", ios::in|ios::binary); // read file in binary mode

    if (!openFile && (mode == 1 || mode == 2))  // show error for manual mode
    {
        cout<<"  Unable to open file 'Tickets.dat'.\n"<<endl;
        cout<<"  ";
        system("PAUSE");    // wait for user to read message
        return; // return to main menu
    }
    else if (!openFile) // error for auto mode
    {
        cout<<"  Unable to open file 'Tickets.dat'.\n  Setup failed.\n  Exiting Program.\n"<<endl;
        exit(1);    // could not setup program properly; must exit
    }
    openFile.read((char*)this, sizeof(*this));  // read an object

    int noResultFlag = 1;   // keeps track of whether or not any results are available for manual mode
    while (!openFile.eof())
    {
        if (mode == 0)  this->bookSeats();  // in auto mode, just book seats
        if ((mode == 1 && name == custName && number == custNum) || (mode == 2 && trainID == tid))  // in manual mode, check that train's id matches (for administrative request) or customer's name and phone number matches (for customer request)
        {
            string arrSt, deptTime, arrTime;
            float distance;
            Station *tempStation = getStation(departure);   // get departure station
            for (int i=0; i<MAXTRAINS; i++) // for each train in staion
            {
                Train *tempTrain = tempStation->getTrain(i);    // get each train
                if (tempTrain->getID() == trainID)  // found correct train
                {
                    arrSt = tempTrain->getStation(arrInd);  // storing arrival station name
                    deptTime = tempTrain->getDeptTime(deptInd); // storing departure time
                    arrTime = tempTrain->getArrTime(arrInd);    // storing arrival time
                    distance = tempTrain->getDistanceBetween(deptInd, arrInd);  // storing distance between departure and arrival points
                }
            }

            string seatCat;
            if (seatCategory == 1)  // checking seat category
            {
                seatCat = "Business";   // storing string version
                distance *= 2;  // distance double since it is used to calculate price; actual distance will not be shown so not a problem
            }
            else if (seatCategory == 2) seatCat = "Economy";

            cout<<"  Name: "<<name<<"\n  Phone Number: "<<number<<"\n  Train ID: "<<trainID;    // display information to user
            cout<<"\n  Departure Point: "<<departure<<"          \tArrival Point: "<<arrSt;
            cout<<"\n  Departure Time: "<<deptTime<<"          \tArrival Time: "<<arrTime;
            cout<<"\n  Seat Category: "<<seatCat<<"\n  Total Seats: "<<seats;
            cout<<"\n  Total Cost: BDT "<<distance*seats<<"\n"<<endl;   // calculate price and show
            noResultFlag = 0;   // indicate that at least one result was shown
        }
        openFile.read((char*)this, sizeof(*this));  // retrieve next object
    }
    if (noResultFlag && mode != 0)  cout<<"  No available bookings.\n"<<endl;   // no results in manual mode
    openFile.close();
}
