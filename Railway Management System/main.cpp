#include <iostream>
#include "Administrator.h"
#include "Customer.h"
#include "User.h"

using namespace std;

int main()
{
    Administrator::setup();

    int choice;
    cout<<"1. Administrator\n2. Customer\nChoice: ";
    cin>>choice;

    if (choice == 1)
    {
        Administrator* user = new Administrator();
    }
    else if (choice == 2)
    {
        Customer* user = new Customer();
        user->bookTicket();
        user->bookTicket();
        user->bookTicket();
        user->viewTimeTable();             //station name
    }
}
