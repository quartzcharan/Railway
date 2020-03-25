#ifndef TRAIN_H
#define TRAIN_H
#include <iostream>
using namespace std;


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
        void setCapacityEconomy (int i) { capacityEconomy = i; }
        int getCapacityEconomy () { return capacityEconomy; }
        int getSeatsRemainingEconomy (int i) { return seatsRemainingEconomy[i]; }
        void setCapacityBusiness (int i) { capacityBusiness = i; }
        int getCapacityBusiness () { return capacityBusiness; }
        int getSeatsRemainingBusiness (int i) { return seatsRemainingBusiness[i]; }
        void setDistanceToNext (float i, int ind) { distanceToNext[ind] = i; }
        void occupySeat (int seatCategory, int seatNumber, int ind);
        float getDistanceBetween (int dept, int arr);


    protected:

    private:
        int id;
        string station[5];
        string deptTime[5];
        string arrTime[5];
        static int totalTrains;
        int capacityEconomy;
        int capacityBusiness;
        int seatsRemainingEconomy[5];
        int seatsRemainingBusiness[5];
        float distanceToNext[5];    //to the next station that is
};

#endif // TRAIN_H
