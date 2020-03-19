#include <iostream>
#include <Station.h>
#include <Train.h>
using namespace std;

void createTrains (Train *t)
{
    t->setStation("Chittagong", 0);
    t->setStation("Dhaka", 1);
    t->setStation("Khulna", 2);

    t->setDeptTime(11, 0);
    t->setArrTime(12, 1);
    t->setDeptTime(13, 1);
    t->setArrTime(14, 2);
}

Station createStations (Train *t)
{
    Station s1("Chittagong"), s2("Dhaka"), s3("Khulna");
    s1.setTrain(t, 0);
    return s1;
}

void bookTicket (Station s, string str)
{
    Train tempTrain, chosenTrain;
    int deptInd = -1, arrInd = -1;
    string tempString;
    for (int i=0; i<1; i++)
    {
        tempTrain = s.getTrain(i);
        for (int i=0; i<3; i++)
        {
            if (tempTrain.getStation(i) == s.Getlocation())   deptInd = i;
            if (tempTrain.getStation(i) == str && deptInd != -1)
            {
                tempString = str;
                arrInd = i;
                chosenTrain = tempTrain;
                break;
            }
        }
    }
    cout<<"Ticket Booked:\nDeparture Station: "<<s.Getlocation()<<"\nDeparture Time: "<<chosenTrain.getDeptTime(deptInd)<<"\nArrival Station: "<<str<<"\nArrival Time: "<<chosenTrain.getArrTime(arrInd);

}
