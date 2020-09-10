#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <iostream>
using namespace std;


class Customer : public User
{
public:
    Customer();
    void bookTicket();
    void viewBooking();

protected:

private:

};

#endif // CUSTOMER_
