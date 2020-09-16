#include <iostream>
#include "Administrator.h"
#include "Customer.h"
#include "User.h"
#include "Ticket.h"
#include <fstream>

using namespace std;

void setup()    //sets up all the stations and trains for the program to use
{
    fstream openFile;   //will store station and train files
    string str;         //store lines being read from files
    int num;            //stores integer numbers
    Administrator temp; // temporary object to create Station and Train objects

    openFile.open("\Stations.txt"); //working with stations
    if (!openFile)                  //problem reading file; must stop program
    {
        cout<<"  Unable to open file 'Stations.txt'.\n  Setup failed.\n  Exiting Program.\n"<<endl;
        exit(1);
    }
    while (getline(openFile, str))
    {
        Station* newStation = new Station();    // allocate memory for new station object
        addStation(str, newStation);    // add station to trie
    }

    openFile.close();   //done with stations

    openFile.open("\Trains.txt");   //working with trains
    if (!openFile)  //problem reading file; must stop program
    {
        cout<<"  Unable to open file 'Trains.txt'.\n  Setup failed.\n  Exiting Program.\n"<<endl;
        exit(1);
    }
    while (getline(openFile, str))  //creating each of the trains
    {
        openFile >> num;            //number of stations associated with train
        openFile.ignore(1, '\n');   // go to next line

        string stations[num];       //storing everything to pass to createTrain function
        string deptTimes[num];
        string arrTimes[num];
        float dist[num];

        for (int i=0; i<num; i++)   openFile >> stations[i];    //storing station names
        openFile.ignore(1, '\n');

        for (int i=0; i<num; i++)   openFile >> deptTimes[i];   //storing departure times
        openFile.ignore(1, '\n');

        for (int i=0; i<num; i++)   openFile >> arrTimes[i];    //storing arrival times
        openFile.ignore(1, '\n');

        for (int i=0; i<num; i++)   openFile >> dist[i];        //storing distance
        openFile.ignore(1, '\n');
        openFile.ignore(1, '\n');

        temp.createTrain(num, stations, deptTimes, arrTimes, dist, 1);  //creating train
    }
    openFile.close();

    Ticket tempTicket;
    tempTicket.read();  // bookings being read by Ticket class
}

int main()
{
    setup();

    int choice; // user choice

    while (choice != 3) // while not exiting
    {
        system("CLS");  // clear the screen
        cout<<endl; // leave a line gap on top
        cout<<"  1. Administrator\n  2. Customer\n  3. Exit\n  Choice: ";   // display choices
        cin>>choice;    // get choice
        int userChoice;

        if (choice == 1)    // if administrator
        {
            system("CLS");  // clear the screen
            cout<<endl; // leave a line gap on top

            Administrator* user = new Administrator();  // creating Administrator
            cout<<"  1. Add a station to database\n  2. Add a train to database\n"; // showing administrative choices
            cout<<"  3. View bookings\n  4. View Station Timetable\n  Choice: ";
            cin>>userChoice;

            if (userChoice == 1)    user->createStation(); // create new station function run in manual mode
            else if (userChoice == 2)   // create new train function run in manual mode
            {
                string tempStringArray[] = {""};    // needed to pass as default values to function; not used
                float tempFloatArray[] = {0.0F};
                user->createTrain(-1, tempStringArray, tempStringArray, tempStringArray, tempFloatArray, 0);
            }
            else if (userChoice == 3)   user->viewBooking();    // view bookings for a train
            else if (userChoice == 4)   user->viewTimeTable();  // view timetable for a station
            delete user;    // delete allocated memory for Administrator object
        }
        else if (choice == 2)   // Customer
        {
            system("CLS");  //clear the screen
            cout<<endl; // leave a line gap on top

            Customer* user = new Customer();    // creating Customer
            cout<<"  1. Book a ticket\n  2. View Booking\n  3. View Station Timetable\n  Choice: ";  //showing customer choices
            cin>>userChoice;

            if (userChoice == 1)    user->bookTicket(); // make a new booking
            else if (userChoice == 2)   user->viewBooking();    // view previously booked tickets
            else if (userChoice == 3)   user->viewTimeTable();  // view timetable for a station
            delete user;
        }
        else if (choice == 3)   deleteTree();   // delete all station and train objects
    }
}
