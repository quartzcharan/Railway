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
        void setDeptTime (int i, int ind) { deptTime[ind] = i; }
        int getDeptTime (int i) { return deptTime[i]; }
        void setArrTime (int i, int ind) { arrTime[ind] = i; }
        int getArrTime (int i) { return arrTime[i]; }
        void setCapacity (int i) { capacity = i; }
        int getCapacity () { return capacity; }
        void setSeatsRemaining (int i, int ind) { seatsRemaining[ind] = i; }
        int getSeatsRemaining (int i) { return seatsRemaining[i]; }
        //total stations attribute removed; not required


    protected:

    private:
        int id;
        string station[3];
        int deptTime[5];
        int arrTime[5];
        static int totalTrains;
        int capacity;
        int seatsRemaining[5];
};

#endif // TRAIN_H
