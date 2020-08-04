#ifndef TICKET_H
#define TICKET_H
#define MAXTRAINS 3
#define MAXSTATIONS 5
#include "../StationTree.h"
#include "Station.h"
#include "Train.h"
#include<iostream>
using namespace std;


class Ticket
{
    public:
        Ticket();
        Ticket(string dept, int deptPnt, int arrPnt, int tid, int seatCat, int passengers);
        void store();
        void bookSeats();
        int deptInd;
        int arrInd;
        int trainID;
        int seatCategory;
        int seats;
        string departure;

    protected:

    private:

};

#endif // TICKET_H
