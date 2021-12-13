//
// Created by Ziming on 2021/12/13.
//

#include "Status.h"
using namespace std;
void change_status(Floor *f,vector <Vehicle>::iterator &v,int vec_n) {

    int mtime=f->get_time();

    switch(v->get_status())
    {
        case 0:{
            ///if the time reaches
            ///enter into the plot
            if(mtime==v->get_enter_time())
            {
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" enters the parking plot"<<endl;
                v->set_status(1);
            }
            break;
        }

        case 1:{

            /// find the plot for the car

            if(v->get_plot().row==-1){
                bool flag =0;
                if(v->get_type()==4)   flag=true;
                v->set_plot(f->find_slot(flag));
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" Find plot for the vehicle ["<<v->get_plot().row<<","<<v->get_plot().col<<"]"<<endl;
                break;
            }
            ///print the enter ticket

            ///begin the self-detect process
            v->self_detect();
            //self-detect process for the front car to decide whether to stop

            ///begin the straight auto-move process
            // if the stop signs remains false, do move for constant speed per unit
            if(!v->get_stop())
                v->move_straight(1);

            if(v->get_anchor().getY()>=f->get_main_turnpoint(v->get_plot().row,1).getY()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" prepares for turning to side road"<<endl;
                v->set_status(2);
            }
            break;
        }
        ///if reach the turning point --> calculating for the turning point
        ///then enter into the side road
        case 2:{
            /// send continuous signal to the following car to **wait behind**
            //   if their distance to the *branch* is less than the normal car distance

            Vec spin=f->get_main_turnpoint(v->get_plot().row,1)+Vec(f->get_owidth()/2,.0);
            v->move_curly(spin,1); /// put your curve algorithm here
            ///begin the curving the auto-move process
            ///begin the auto-rotate process
            
            if(v->get_anchor().getX()>=f->get_side_turnpoint(v->get_plot().row,1).getX()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" finished the turning process"<<endl;
                v->set_status(3);
            }
            break;
        }
        /// if the anchor point totally enter into the side road
        case 3:{
            ///self detect process

            ///signal to the **possible** car staying in the plot aside the car and prevent them from going out


            ///begin the straight auto-move process
            //change back -> move straight
            v->move_straight(4);

            ///end the auto-rotate process

            ///SPECIAL: once the car move past the parking lot,
            // send continuous signal to the following car to **wait behind**
            // if their distance to the *plot* is less than the normal car distance
            if(v->get_anchor().getX()>=f->get_reversing_point(v->get_plot()).getX()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" began to reverse into the plot"<<endl;
                v->set_status(4);
            }
            break;
        }
        ///if reach the plotting point --> calculating for the plotting point
        ///enter into the planned plotting place
        case 4:{

            /// CONTINUE from case 3
            /// send continuous signal to the following car to **wait behind**
            //   if their distance to the *plot* is less than the normal car distance

            ///begin the curving auto-move process (reverse version)
            Vec spin=f->get_reversing_point(v->get_plot())+Vec(.0,f->get_owidth()/2);
            //            cout<<"<1> "<<v->get_anchor().getY()<<endl;
            //            cout<<"<2> "<<f->get_slot_bound(v->get_plot()).getY()<<endl;
            if(v->get_anchor().getY()<f->get_slot_bound(v->get_plot()).getY())
            {
                v->move_curly(spin,1);
                // cout<<"Y"<<endl;
            }
            else
                v->move_straight(1);



            if(v->get_anchor().getY()>=f->get_slot_center(v->get_plot()).getY()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" successfully reaches the plot"<<endl;
                v->set_status(5);
                v->set_final_enter_time(mtime);
            }
            break;
        }
        /// the anchor point of the car is set right in the center of the plot
        /// staying the plot (inert state)
        case 5:{
            ///wait for the time to change the status


            if(mtime>=v->get_final_enter_time()+v->get_interval()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" stays for "<<v->get_interval()<<" seconds in the slot and finally begins to leave"<<endl;
                v->set_status(6);
            }
            break;
        }
        /// after triggered by case 5
        /// exit the plot and reach the side road
        case 6:{
            /// send continuous signal to the following car to **wait behind**
            //   if their distance to the *plot* is less than the normal car distance
            ///begin the curving auto-move process
            Vec spin=f->get_reversing_point(v->get_plot())+Vec(.0,f->get_owidth()/2);
            if(v->get_anchor().getY()<f->get_slot_bound(v->get_plot()).getY())
            {
                v->move_curly(spin,0);
            }
            else
                v->move_straight(2);
            ///begin the auto-rotate process
            if(v->get_anchor().getX()>=f->get_reversing_point(v->get_plot()).getX()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" successfully moves out of the plot"<<endl;
                f->get_slot()[v->get_plot().row][v->get_plot().col]->exit_slot();
                v->set_status(7);
            }
            break;
        }
        /// after reach the plotting point
        /// move straight at the side road
        case 7:{


            ///self-detect process

            ///change the self-detect process
            // change -> back the the original one // keep the distance with the front

            ///signal to the **possible** car staying in the plot aside the car and prevent them from going out


            ///begin the straight auto-move process
            //change back -> move straight
            v->move_straight(4);
            ///end the auto-rotate process
            if(v->get_anchor().getX()>=f->get_side_turnpoint(v->get_plot().row,0).getX()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" begins to merge into the side road"<<endl;
                v->set_status(8);
            }
            break;
        }
        /// after reach the boundary of the side road
        ///move from the side road to the main road
        case 8:{
            Vec spin=f->get_side_turnpoint(v->get_plot().row,0)-Vec(.0,f->get_owidth()/2);
            v->move_curly(spin,1);
            /// send continuous signal to the following car to **wait behind**
            //   if their distance to the *branch* is less than the normal car distance
            if(v->get_anchor().getY()<=f->get_main_turnpoint(v->get_plot().row,0).getY()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" successfully merge into the main road"<<endl;
                v->set_status(9);
            }
            break;
        }
        ///after reach the turning point
        ///move straight on the main road
        case 9:{
            ///self-detect process
            //self-detect process for the front car to decide whether to stop
            ///straight auto-move process
            v->move_straight(2);
            // if the stop signs remains false, do move for constant speed per unit
            if(v->get_anchor().getY()<=f->get_exit().getY()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" reaches the exit"<<endl;
                v->set_status(10);
            }
            break;
        }
        ///after having reached the exit
        /// relevant functions with the exit of a car
        case 10:{
            ///print_ticket
#ifdef OPEN_GL
            v->get_vehicle()->move(Vec(.0,-999.0));
#endif

            v->set_exit(true);
            //cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" successfully leaves the plot"<<endl;
            //v->delete_vehicle();

            break;
        }
        default:{
            std::cerr<<"Abnormal State! Please check out for the error"<<std::endl;
        }
    }
}

void Read_Log(vector <Vehicle> &v,Floor *f){
    int car_num;
    ifstream a("Car.log");
    if(a.is_open()){
        a>>car_num;
        for(int i = 0;i<car_num;i++)
        {
            int begin;
            int type;
            int interv;

            //        bool flag=0;
            a>>type;
            a>>begin;
            a>>interv;
            //cout<<type<<" "<<begin<<" "<<interv<<endl;
            Vehicle vh;
            f->get_owidth();

            Vec start=f->get_anchor()+Vec(f->get_owidth()/2,-2*f->get_owidth());

            vh.create_vehicle(start,type,begin,interv);
#ifdef OPEN_GL
            vh.get_vehicle()->zoom(f->get_owidth()/vh.get_vehicle()->get_width()/2);
            //        if(type==4)   flag=true;
            //        vh.set_plot(f->find_slot((flag)));
            //        cout<<vh.get_plot().row<<" "<<vh.get_plot().col<<endl;
#endif
            v.push_back(vh);
        }
        a.close();
    }

}
