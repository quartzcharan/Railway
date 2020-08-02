#include "Station.h"

Station::Station() : location("")
{
    for (int i=0; i<MAXTRAINS; i++) t[i] = NULL;
}
