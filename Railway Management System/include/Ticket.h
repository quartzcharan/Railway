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
        Ticket(string custName, string custNum, string dept, int deptPnt, int arrPnt, int tid, int seatCat, int passengers);
        void store();
        void read(int mode=0, string custName="", string custNum="", int tid=-1);
        void bookSeats();

    protected:

    private:
        int deptInd;
        int arrInd;
        int trainID;
        int seatCategory;
        int seats;
        char departure[30];
        char name[30];
        char number[30];

};

#endif // TICKET_H
