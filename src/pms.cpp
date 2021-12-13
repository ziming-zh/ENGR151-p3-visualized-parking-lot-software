#include <iostream>
#include <stack>
#include "Status.h"


#include <time.h>
using namespace std;
void wait ( int m_seconds )
{
    clock_t end;
    end = clock () + m_seconds /1000.0 * CLOCKS_PER_SEC ;
    while (clock() < end) {

    }
}
void pms(){
    cout<<"Parking Management Software"<<std::endl;
    cout<<"Creating parking lot..."<<endl;


    cout<<"Create Successfully"<<endl;

    cout<<"Creating floor..."<<endl;

    int row,col;
    cout<<"Now input the number of slot for each column and each row (default:3*10)"<<endl;
    cin>>row;
    cin>>col;
    Floor f(row,col);

    cout<<"Create Successfully"<<endl;

    while(1){
        f.set_time();
        //cout<<f.get_time()<<endl;
        if(f.get_slot()==NULL)
        {
            f.init_slot();
            f.create_slot();
        }
        static vector<Vehicle> v;
        if(v.empty()){
            Read_Log(v,&f);
        }
        /// search each car find potential changes
        vector<Vehicle>::iterator it;
        int i =0;
        for(it=v.begin();it!=v.end();it++){
            i++;
            change_status(&f,it,i);
        }
        bool flag=true;
        for(it=v.begin();it!=v.end();it++){
            if(!it->get_exit())
                flag= false;
        }
        if(flag==true)
        {
            cout<<"ALL Vehicles exit successfully! The program will end automatically"<<endl;
            exit(0);
        }
        wait(50);
    }

}
int main() {
    /// create parking lot
    pms();

    return 0;


}