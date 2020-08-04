#include<iostream>
using namespace std;
#include "Ticket.h"
#include <fstream>

Ticket::Ticket()
{

}

Ticket::Ticket(string dept, int deptPnt, int arrPnt, int tid, int seatCat, int passengers): departure(dept), deptInd(deptPnt), arrInd(arrPnt), trainID(tid), seatCategory(seatCat), seats(passengers)
{

}

void Ticket::store()
{
    fstream openFile;
    openFile.open("\Tickets.dat", ios_base::app);
    if (!openFile)  //problem reading file; return to main menu
    {
        cout<<"Unable to open file 'Tickets.dat'.\n"<<endl;
        system("PAUSE");
        return;
    }
    openFile<<"Ticket"<<endl;
    openFile<<departure<<" "<<deptInd<<" "<<arrInd<<" "<<trainID<<" "<<seatCategory<<" "<<seats<<endl;
    openFile<<endl;
    openFile.close();
}

void Ticket::bookSeats()
{
    Station *tempStation = getStation(departure);
    for (int i=0; i<MAXTRAINS; i++)
    {
        Train *tempTrain = tempStation->getTrain(i);
        if (tempTrain->getID() == trainID)
        {
            for (int j=deptInd; j<arrInd; j++)  tempTrain->occupySeat(seatCategory, seats, j);
        }
    }
}
