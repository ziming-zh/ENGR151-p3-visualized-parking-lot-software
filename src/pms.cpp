#include <iostream>
#include <stack>
#include "Floor.h"
#include "Plot.h"
using namespace std;
int main() {
    /// create parking lot
    cout<<"Parking Management Software"<<std::endl;
    cout<<"Creating parking lot..."<<endl;

    stack<Floor*> lot;

    cout<<"Create Successfully"<<endl;
    cout<<"Now input the number of floors of your parking lot(default 2):"<<endl;
    int fl_num;
    cin>>fl_num;
    cout<<"Creating floor..."<<endl;
    for(int i = 0;i<fl_num;i++){
        int row,col;
        cout<<"Now input the number of slot for each column and each row (default:2*5)"<<endl;
        cin>>row;
        cin>>col;
        Floor *pfl= new Floor(row,col);
        lot.push(pfl);
    }
    cout<<"Create Successfully"<<endl;



    cout<<"Deleting floor(default 2)..."<<endl;
    while(!lot.empty())
    {
        delete lot.top();
        lot.pop();
    }
    cout<<"Delete Successfully"<<endl;

    return 0;

}
