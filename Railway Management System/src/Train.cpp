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
