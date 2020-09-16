#include "Train.h"

Train::Train() : id(totalTrains+1)  // constructor
{
    totalTrains++;  // used to keep track of ID of train
    for (int i=0; i<MAXSTATIONS; i++)   // for each station
    {
        station[i] = "";    // no station name
        deptTime[i] = -1;   // no departure time
        arrTime[i] = -1;    // no arrival time
        seatsRemainingEconomy[i] = 20;  // default number of seats, before any bookings
        seatsRemainingBusiness[i] = 20;
        distanceToNext[i] = 0.0F;   // no distances
    }
}

int Train::totalTrains = 0; // initializer for static variable

void Train::occupySeat (int seatCategory, int passengers, int ind)  //decrements available seats at an index
{
    if (seatCategory == 1)  seatsRemainingBusiness[ind] -= passengers;  //business class
    else if (seatCategory == 2) seatsRemainingEconomy[ind] -= passengers;   //economy class
}

float Train::getDistanceBetween (int dept, int arr)    //gets distance travelled between two stations
{
    float res = 0.0F;
    for (int i=dept; i<arr; i++)    res += distanceToNext[i];   //sum
    return res;
}
