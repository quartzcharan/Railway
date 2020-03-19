#include <iostream>
#include <Functions.h>
using namespace std;

int main()
{
    Train t1;
    createTrains(&t1);
    string a, b;
    cout<<"Enter route:"<<endl<<"From: ";
    cin>>a;
    cout<<"To: ";
    cin>>b;
    cout<<endl;
    buyTicket(a, b);

}
