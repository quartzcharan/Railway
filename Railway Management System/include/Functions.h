#include <iostream>
#include <Station.h>
#include <Train.h>
using namespace std;


Station s1("Chittagong"), s2("Dhaka"), s3("Khulna");


void createTrains (Train *t)
{
    t->setStation("Chittagong", 0);
    t->setStation("Dhaka", 1);
    t->setStation("Khulna", 2);

    t->setDeptTime(11, 0);
    t->setArrTime(12, 1);
    t->setDeptTime(13, 1);
    t->setArrTime(14, 2);

    s1.setTrain(t, 0);
    s2.setTrain(t, 0);
}


void findTrains (string from, string to, int seatsToBeIssued)
{
    Station *A;
    Station B;
    Train tempTrain;
    int departure, arrival, trainFound, onBoard, selectedTrain;

    if(s1.Getlocation() == from)
        A = &s1;
    else if(s2.Getlocation() == from)
        A = &s2;
    else if(s3.Getlocation() == from)
        A = &s3;

    for(int i=0; i<A->getTotalTrains(); i++)
    {
        trainFound = 0, onBoard = 0;
        tempTrain = A->getTrain(i);

        for(int j=0; j<3; j++)
        {
            if(tempTrain.getStation(j) == from)
            {
                departure = tempTrain.getDeptTime(j);
                onBoard = 1;
            }

            else if(tempTrain.getStation(j) == to)
            {
                trainFound = 1;
                B.Setlocation(tempTrain.getStation(j));
                arrival = tempTrain.getArrTime(j);
                break;
            }

            if(onBoard == 1)// && tempTrain.getSeatsRemaining(j) < seatsToBeIssued)
                {
                    cout<<tempTrain.getSeatsRemaining(j)<<endl;
                    //break;
                }
        }

        if(trainFound == 1)
            cout<<"ID: "<<tempTrain.getTrainID()<<"   Departure Station: "<<A->Getlocation()<<"   Departure Time: "<<departure<<"   Arrival Station: "<<B.Getlocation()<<"   Arrival Time: "<<arrival<<endl;
    }

    if(trainFound == 0)
        cout<<"No train is available."<<endl;


    //book seats

    cout<<"Enter an ID to purchase: ";
    cin>>selectedTrain;
    onBoard = 0;

    for(int i=0; i<A->getTotalTrains(); i++)
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
                    cout<<tempTrain.getSeatsRemaining(j);
                    tempTrain.setSeatsRemaining(temp-seatsToBeIssued, j);
                    cout<<tempTrain.getSeatsRemaining(j);
                    A->trainArr[i] = &tempTrain;
                }
            }
        }
    }
}


void buyTicket()
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
