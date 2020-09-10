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
    virtual void viewBooking() = 0;

protected:

private:

};

#endif // USER_
