#include <iostream>
#include "Administrator.h"
#include "Customer.h"
#include "User.h"
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
        cout<<"Unable to open file 'Stations.txt'.\nSetup failed.\nExiting Program.\n"<<endl;
        exit(1);
    }
    while (getline(openFile, str))  temp.createStation(str, 1); //creating each of the stations

    openFile.close();   //done with stations

    openFile.open("\Trains.txt");   //working with trains
    if (!openFile)  //problem reading file; must stop program
    {
        cout<<"Unable to open file 'Trains.txt'.\nSetup failed.\nExiting Program.\n"<<endl;
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
}

int main()
{
    setup();

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

            if (userChoice == 1)    user->createStation("", 0);
            else if (userChoice == 2)
            {
                string tempStringArray[] = {""};
                float tempFloatArray[] = {0.0F};
                user->createTrain(-1, tempStringArray, tempStringArray, tempStringArray, tempFloatArray, 0);
            }
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
