#include "Train.h"

Train::Train() : id(totalTrains+1), capacityEconomy(20), capacityBusiness(20)
{
    totalTrains++;
    for (int i=0; i<5; i++)
    {
        station[i] = "";
        deptTime[i] = -1;
        arrTime[i] = -1;
        seatsRemainingEconomy[i] = capacityEconomy;
        seatsRemainingBusiness[i] = capacityBusiness;
        distanceToNext[i] = 0.0F;
    }
}

int Train::totalTrains = 0;

void Train::occupySeat (int seatCategory, int passengers, int ind)  //decrements available seats at an index
{
    if (seatCategory == 1)  seatsRemainingBusiness[ind] -= passengers;
        //business class
    else if (seatCategory == 2) seatsRemainingEconomy[ind] -= passengers;
    //economy class
}

float Train::getDistanceBetween (int dept, int arr)    //gets distance traveled between two stations
{
    float res = 0.0F;
    for (int i=dept; i<arr; i++)    res += distanceToNext[i];
    return res;
}
