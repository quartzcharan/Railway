#include<iostream>
#ifndef TRAIN_H
#define TRAIN_H

class Train
{
    public:
        Train();
        int getTrainID() {return trainID;}
        void setStation (std::string s, int ind) { stArr[ind] = s; }
        std::string getStation (int i) { return stArr[i]; }
        void setDeptTime (int i, int ind) { deptTime[ind] = i; }
        int getDeptTime (int i) { return deptTime[i]; }
        void setArrTime (int i, int ind) { arrTime[ind] = i; }
        int getArrTime (int i) { return arrTime[i]; }
        void setCapacity (int i) { capacity = i; }
        int getCapacity () { return capacity; }
        void setSeatsRemaining (int i, int ind) { seatsRemaining[ind] = i; }
        int getSeatsRemaining (int i) { return seatsRemaining[i]; }

    protected:

    private:
        int trainID;
        std::string stArr[5];
        int deptTime[5];
        int arrTime[5];
        static int totalTrains;
        int capacity;
        int seatsRemaining[5];
};

#endif // TRAIN_H
