#include "Train.h"

Train::Train() : trainID(totalTrains+1), capacity(5)
{
    for (int i=0; i<5; i++)
    {
        stArr[i] = "";
        deptTime[i] = -1;
        arrTime[i] = -1;
        seatsRemaining[i] = 5;
    }
}

int Train::totalTrains = 0;
