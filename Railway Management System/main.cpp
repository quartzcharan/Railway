#include <iostream>
#include "Administrator.h"
#include "Customer.h"
#include "User.h"

using namespace std;

int main()
{
    Administrator::setup();

    int choice;

    while (choice != 3)
    {
        system("CLS");
        cout<<endl;
        cout<<"  1. Administrator\n  2. Customer\n  3. Exit\n  Choice: ";
        cin>>choice;
        int userChoice;

        if (choice == 1)
        {
            system("CLS");
            Administrator* user = new Administrator();
            cout<<endl;
            cout<<"  1. Add a station to database [UNIMPLEMENTED]\n  2. Add a train to database [UNIMPLEMENTED]\n";
            cout<<"  3. View bookings [UNIMPLEMENTED]\n  4. View Station Timetable\n  Choice: ";
            cin>>userChoice;

            if (userChoice == 1)    continue;
            else if (userChoice == 2)   continue;
            else if (userChoice == 3)   continue;
            else if (userChoice == 4)   user->viewTimeTable();
        }
        else if (choice == 2)
        {
            system("CLS");
            Customer* user = new Customer();
            cout<<endl;
            cout<<"  1. Book a ticket\n  2. View Station Timetable\n  Choice: ";
            cin>>userChoice;

            if (userChoice == 1)    user->bookTicket();
            else if (userChoice == 2)   user->viewTimeTable();
        }
    }
}
