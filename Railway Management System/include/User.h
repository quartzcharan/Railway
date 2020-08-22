#ifndef USER_H
#define USER_H

#include "Ticket.h"

#include <iomanip>
#include <iostream>
using namespace std;


class User
{
public:
    User();
    void viewTimeTable ();
    void viewBooking(string custName="", string custNum="", int tid=-1, int mode=-1);
    void setName (string str) { name = str;}

protected:

private:
    string name;
};

#endif // USER_
