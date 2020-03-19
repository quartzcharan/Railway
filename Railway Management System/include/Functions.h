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

void buyTicket(string from, string to)
{
    Station A, B;
    int departure, arrival;
    if(s1.Getlocation() == from)
        A = s1;
    else if(s2.Getlocation() == from)
        A = s2;
    else if(s3.Getlocation() == from)
        A = s3;
    for(int i=0; i<A.getTotalTrains(); i++)
    {
        int trainFound = 0;
        Train tempTrain = A.getTrain(i);
        for(int j=0; j<3; j++)
        {
            if(tempTrain.getStation(j) == from)
                departure = tempTrain.getDeptTime(j);

            if(tempTrain.getStation(j) == to)
            {
                trainFound = 1;
                B = tempTrain.getStation(j);
                arrival = tempTrain.getArrTime(j);
                break;
            }
        }
        if(trainFound == 1)
            cout<<"ID: "<<tempTrain.getTrainID()<<"   Departure Station: "<<A.Getlocation()<<"   Departure Time: "<<departure<<"   Arrival Station: "<<B.Getlocation()<<"   Arrival Time: "<<arrival<<endl;
    }

}
