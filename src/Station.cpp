#include "Station.h"

Station::Station() : location("")   // constructor
{
    for (int i=0; i<MAXTRAINS; i++) t[i] = NULL;    // assign each train to NULL by default
}
