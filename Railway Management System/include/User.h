#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;


class User
{
public:
    User();
    void viewTimeTable ();
    void setName (string str) { name = str;}

protected:

private:
    string name;
};

#endif // USER_
