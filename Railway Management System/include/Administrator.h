#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"
#include <iostream>
using namespace std;


class Administrator : public User
{
public:
    Administrator();
    static void setup();

protected:

private:
    int adminId;
    static int adminCount;
    string pass;

    static void createStation (string str);
    static void createTrain(int n, string stations[], string deptTimes[], string arrTimes[], float distances[]);
};

#endif // ADMINISTRATOR_
