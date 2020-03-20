#include <iostream>
#include <Station.h>
#include <Train.h>
using namespace std;


Station s1("Chittagong"), s2("Dhaka"), s3("Khulna");


void createTrains ()
{
    Train *t;                       //train-1 of route chittagong-dhaka-khulna

    t->setStation("Chittagong", 0);
    t->setStation("Dhaka", 1);
    t->setStation("Khulna", 2);

    t->setDeptTime(11, 0);
    t->setArrTime(12, 1);
    t->setDeptTime(13, 1);
    t->setArrTime(14, 2);

    s1.setTrain(t, 0);             //t stops at chittagong and dhaka station to pick up passengers
    s2.setTrain(t, 0);
}


void findTrains (string from, string to, int seatsToBeIssued)     //search for available trains for routes selected by passengers
{
    Station *A;
    Station B;
    Train tempTrain;
    int departure, arrival, trainFound, onBoard, selectedTrain;

    if(s1.Getlocation() == from)              //A and B are the stations the passenger wants to travel in between
        A = &s1;
    else if(s2.Getlocation() == from)
        A = &s2;
    else if(s3.Getlocation() == from)
        A = &s3;

    for(int i=0; i<A->getTotalTrains(); i++)  //look for trains that will take passengers from station A
    {
        trainFound = 0, onBoard = 0;
        tempTrain = A->getTrain(i);

        for(int j=0; j<3; j++)                //find trains that have the destination station on its route
        {
            if(tempTrain.getStation(j) == from)
            {
                departure = tempTrain.getDeptTime(j);   //get departure time
                onBoard = 1;
            }

            else if(tempTrain.getStation(j) == to)
            {
                trainFound = 1;
                B.Setlocation(tempTrain.getStation(j)); //assign destination station to B
                arrival = tempTrain.getArrTime(j);      //get arrival time
                break;
            }

            if(onBoard == 1 && tempTrain.getSeatsRemaining(j) < seatsToBeIssued)
                break;               //the train won't be valid if it doesn't have enough seats
        }

        if(trainFound == 1)         //print details of the trains that are available
            cout<<"ID: "<<tempTrain.getTrainID()<<"   Departure Station: "<<A->Getlocation()<<"   Departure Time: "<<departure<<"   Arrival Station: "<<B.Getlocation()<<"   Arrival Time: "<<arrival<<endl<<endl;
    }

    if(trainFound == 0)
    {
        cout<<"No train is available."<<endl<<endl;
        return;
    }


    //book seats

    cout<<"Enter an ID to purchase: ";
    cin>>selectedTrain;
    onBoard = 0;

    for(int i=0; i<A->getTotalTrains(); i++)       //find the train again to decrement remaining seats after purchase
    {
        tempTrain = A->getTrain(i);

        if(tempTrain.getTrainID() == selectedTrain)
        {
            for(int j=0; j<3; j++)
            {
                if(tempTrain.getStation(j) == from)
                    onBoard = 1;

                else if(tempTrain.getStation(j) == to)
                    break;

                if(onBoard == 1)
                {
                    int temp = tempTrain.getSeatsRemaining(j);
                    tempTrain.setSeatsRemaining(temp-seatsToBeIssued, j);     //decrement seats
                    A->trainArr[i] = &tempTrain;
                }
            }
        }
    }
    cout<<"Purchased.."<<endl<<endl;
}


void buyTicket()             //user input for buying tickets
{
    string a, b;
    int passengers;
    cout<<"Enter route:"<<endl<<"From: ";
    cin>>a;
    cout<<"To: ";
    cin>>b;
    cout<<"Passengers: ";
    cin>>passengers;
    cout<<endl;
    findTrains(a, b, passengers);
}
