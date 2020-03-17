#include <Station.h>

void createStations ()
{
    Station s1("Dhaka"), s2("Chittagong"), s3("Khulna");
    s1.connection[1] = &s2;
    s2.connection[0] = &s1;
    s2.connection[1] = &s3;
    s3.connection[0] = &s2;
}
