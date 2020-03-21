#include "Train.h"

Train::Train() : id(totalTrains+1), capacity(5)
{
    totalTrains++;
    for (int i=0; i<3; i++)
    {
        station[i] = "";
        deptTime[i] = -1;
        arrTime[i] = -1;
        seatsRemaining[i] = capacity;
    }
}

int Train::totalTrains = 0;
