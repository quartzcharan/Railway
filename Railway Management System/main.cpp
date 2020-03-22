#include <iostream>
#include <StationTree.h>
#include <ProgramFunctions.h>

using namespace std;

void setup()
{
    createStation("dhaka");             //creating stations; station names always need to be small letters because of trie
    createStation("chittagong");
    createStation("khulna");
    string stations1[3] = {"chittagong", "dhaka", "khulna"};
    int deptTimes1[3] = {11, 13, -1};
    int arrTimes1[3] = {-1, 12, 14};
    createTrain(3, stations1, deptTimes1, arrTimes1);  //train-1 of route chittagong-dhaka-khulna
    string stations2[2] = {"dhaka", "chittagong"};
    int deptTimes2[2] = {10, -1};
    int arrTimes2[2] = {-1, 11};
    createTrain(2, stations2, deptTimes2, arrTimes2);   //train-2 of route dhaka-chittagong
}

int main()
{
    setup();
    bookTicket();
    bookTicket();
    bookTicket();
    viewTimeTable("dhaka");             //station name
}
