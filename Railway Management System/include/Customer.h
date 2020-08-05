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
    void viewTicket();
    void setPhoneNum (string str) { phoneNum = str;}

protected:

private:
    string phoneNum;
};

#endif // CUSTOMER_
