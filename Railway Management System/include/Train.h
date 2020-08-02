#ifndef TRAIN_H
#define TRAIN_H
#include <iostream>
using namespace std;
#define MAXSTATIONS 5    // maximum number of stations a train a visit



class Train
{
    public:
        Train();
        int getID() { return id; }
        void setStation (string str, int i) { station[i] = str; }
        string getStation (int i) { return station[i]; }
        void setDeptTime (string i, int ind) { deptTime[ind] = i; }
        string getDeptTime (int ind) { return deptTime[ind]; }
        void setArrTime (string i, int ind) { arrTime[ind] = i; }
        string getArrTime (int ind) { return arrTime[ind]; }
        int getSeatsRemainingEconomy (int i) { return seatsRemainingEconomy[i]; }
        int getSeatsRemainingBusiness (int i) { return seatsRemainingBusiness[i]; }
        void setDistanceToNext (float i, int ind) { distanceToNext[ind] = i; }
        void occupySeat (int seatCategory, int seatNumber, int ind);
        float getDistanceBetween (int dept, int arr);

    protected:

    private:
        int id;
        string station[MAXSTATIONS];
        string deptTime[MAXSTATIONS];
        string arrTime[MAXSTATIONS];
        static int totalTrains;
        int seatsRemainingEconomy[MAXSTATIONS];
        int seatsRemainingBusiness[MAXSTATIONS];
        float distanceToNext[MAXSTATIONS];    //to the next station that is
};

#endif // TRAIN_H
