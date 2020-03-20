#include "Train.h"
using namespace std;

Train::Train() : trainID(totalTrains+1), capacity(5)
{
    totalTrains++;
    for (int i=0; i<5; i++)
    {
        stArr[i] = "";
        deptTime[i] = -1;
        arrTime[i] = -1;
        seatsRemaining[i] = capacity;
    }
}

int Train::totalTrains = 0;
