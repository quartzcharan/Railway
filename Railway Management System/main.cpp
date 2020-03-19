#include <iostream>
#include <Functions.h>
using namespace std;

int main()
{
    Train t1;
    Station s;
    createTrains(&t1);
    s = createStations(&t1);
    bookTicket(s, "Khulna");

}
