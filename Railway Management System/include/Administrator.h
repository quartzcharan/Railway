#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"
#include <iostream>
using namespace std;


class Administrator : public User
{
public:
    Administrator();
    void createStation (string str);
    void createTrain(int n, string stations[], string deptTimes[], string arrTimes[], float distances[]);

protected:

private:
    int adminId;
    static int adminCount;
    string pass;
};

#endif // ADMINISTRATOR_
