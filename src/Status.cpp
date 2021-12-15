#include "Ticket.h"
#include "Status.h"

using namespace std;

bool detect_safe(Floor *f,vector <Vehicle>::iterator &v,int vec_n,int allv)
{
    vector<Vehicle>::iterator fv;
    fv=v-vec_n+1;
    float temp=0;
    float dis=0;
    switch(v->get_status())
    {
        case 0:
            for(int jj=0;jj<allv;jj++)
            {
                temp=fv->get_anchor().getY()-v->get_anchor().getY();
                if(fv!=v&&fv->get_status()==1)if(temp<f->get_owidth())return false;
                fv++;
            }
            break;
        case 1:
        case 2:
            for(int ii=0;ii<=f->get_row();ii++)
            {
                temp=v->get_anchor().getY()+v->get_speed();
                if(temp>f->get_main_turnpoint(ii,1).getY())
                {
                    for(int jj=0;jj<allv;jj++)
                    {
                        if(fv->get_warn_rowl()==ii&&fv->get_status()>v->get_status())return false;
                        fv++;
                    }
                }
            }
            break;
        case 3:
        case 7:
            for(int jj=0;jj<allv;jj++)
            {
                if(fv->get_plot().row==v->get_plot().row)
                {
                    if(fv->get_status()==4||fv->get_status()==6)
                    {
                        temp=f->get_slot_bound(fv->get_plot()).getX()-v->get_anchor().getX();
                        dis=(f->get_owidth()+f->get_slot_w())/2;
                        if(temp>dis&&temp-v->get_speed()<dis)return false;
                    }
                    else if(fv->get_status()==3&&fv->get_plot().col!=0&&fv!=v)
                    {
                        unit sl={fv->get_plot().row,fv->get_plot().col-1};
                        temp=fv->get_anchor().getX()-f->get_slot_bound(sl).getX();
                        dis=(-f->get_owidth()+f->get_slot_w())/2;
                        if(temp+dis>=0)
                            {
                                if(f->get_slot_bound(sl).getX()-dis<=v->get_anchor().getX()&&v->get_anchor().getX()<f->get_slot_bound(sl).getX())
                                {
                                    return false;
                                }
                            }
                    }
                }
                fv++;
            }
            break;
        case 6:
            for(int jj=0;jj<allv;jj++)
            {
                if(fv!=v)
                {
                    if(fv->get_status()!=3 &&fv->get_status()!=7)
                        continue;
                    temp=(v->get_anchor()).getX()-fv->get_anchor().getX();
                    dis=(f->get_owidth()+f->get_slot_w())/2;
                    if(temp<dis&&temp>-dis)
                        return false;
                }
            }
            break;
    }
    return true;
}

void self_dect(Floor *f,vector <Vehicle>::iterator &v,int vec_n,int allv)
{
    vector<Vehicle>::iterator fv;
    fv=v-vec_n+1;
    float temp=0;
    for(int jj=0;jj<allv;jj++)
    {
        bool flag1=true;
        if(fv!=v&&fv->get_status()==v->get_status())
        {
            switch(v->get_status())
            {
                case 1:
                    temp=fv->get_anchor().getY()-v->get_anchor().getY();
                    break;
                case 3:
                case 7:
                    temp=fv->get_anchor().getX()-v->get_anchor().getX();
                    if(fv->get_plot().row!=v->get_plot().row)flag1=false;
                    break;
                case 9:
                    temp=v->get_anchor().getY()-fv->get_anchor().getY();
                    break;
            }
            if(temp<=f->get_owidth()&&temp>0&&flag1)
            {
                v->receive_signal();
                if((v->get_status()==7||v->get_status()==3)&&v->warned_slot(0))
                {
                    v->change_warn_rowl(v->get_plot().row);
                }
                else if(v->get_plot().col!=0)v->change_warn_rowl(-1);
                break;
            }
        }
        fv++;
    }
    return;
}

void change_status(Floor *f,vector <Vehicle>::iterator &v,int vec_n,int allv) {

    int mtime=f->get_time();
    float temp=0;
    float dis=0;
    v->restart();
    switch(v->get_status())
    {
        case 0:{
            if(detect_safe(f,v,vec_n,allv))
            {
                if(mtime>=v->get_enter_time())
                {
                    cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" enters the parking plot"<<endl;
                    v->set_status(1);
                }
            }
            break;
        }

        case 1:{
            if(v->get_plot().row==-1){
                bool flag =0;
                if(v->get_type()==4)   flag=true;
                v->set_plot(f->find_slot(flag));
                v->get_arrival_ticket()->set_arr(v->get_enter_time());
                v->get_arrival_ticket()->set_dep(v->get_interval());
                v->get_arrival_ticket()->set_col(v->get_plot().col);
                v->get_arrival_ticket()->set_row(v->get_plot().row);
                v->get_arrival_ticket()->set_type(v->get_type());

                v->get_arrival_ticket()->printTicket();

                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" Find plot for the vehicle ["<<v->get_plot().row<<","<<v->get_plot().col<<"]"<<endl;
                break;
            }
            self_dect(f,v,vec_n,allv);
            if(!v->get_stop()&&detect_safe(f,v,vec_n,allv))
                v->move_straight(1);
            if(v->get_anchor().getY()+v->get_speed()>=f->get_main_turnpoint(v->get_plot().row,1).getY())
            {
                v->change_warn_rowl(v->get_plot().row);
            }
            if(v->get_anchor().getY()>=f->get_main_turnpoint(v->get_plot().row,1).getY()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" prepares for turning to side road"<<endl;
                v->set_status(2);
            }
            break;
        }
        case 2:{

            Vec spin=f->get_main_turnpoint(v->get_plot().row,1)+Vec(f->get_owidth()/2,.0);
            if(!v->get_stop()&&detect_safe(f,v,vec_n,allv))
                v->move_curly(spin,1);
            if(v->get_anchor().getX()>=f->get_side_turnpoint(v->get_plot().row,1).getX()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" finished the turning process"<<endl;
                v->set_status(3);
                if(v->get_plot().col!=0)v->change_warn_rowl(-1);
            }
            break;
        }
        case 3:{
            self_dect(f,v,vec_n,allv);
            unit sl={v->get_plot().row,0};
            temp=v->get_anchor().getX()-f->get_slot_bound(sl).getX();
            dis=(f->get_owidth()+f->get_slot_w())/2;
            if(v->get_plot().col!=0)v->change_warn_rowl(-1);
            if(v->get_stop()&&temp<dis&&temp>-dis)v->change_warn_rowl(v->get_plot().row);
            if(!v->get_stop()&&detect_safe(f,v,vec_n,allv))
                v->move_straight(4);
            if(v->get_anchor().getX()>=f->get_reversing_point(v->get_plot()).getX()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" began to reverse into the plot"<<endl;
                v->set_status(4);
            }
            break;
        }
        case 4:{
            Vec spin=f->get_reversing_point(v->get_plot())+Vec(.0,f->get_owidth()/2);
            if(v->get_anchor().getY()<f->get_slot_bound(v->get_plot()).getY())
            {
                v->move_curly(spin,1);
            }
            else
                v->move_straight(1);

            if(v->get_anchor().getY()>=f->get_slot_center(v->get_plot()).getY()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" successfully reaches the slot"<<endl;
                v->set_status(5);
                v->set_final_enter_time(mtime);
                if(v->get_plot().col==0)v->change_warn_rowl(-1);
            }
            break;
        }
        case 5:{
            if(mtime>=v->get_final_enter_time()+v->get_interval()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" stays for "<<v->get_interval()<<" seconds in the slot and finally begins to leave"<<endl;
                v->set_status(6);
            }
            break;
        }
        case 6:{
            if(detect_safe(f,v,vec_n,allv)){
                Vec spin=f->get_reversing_point(v->get_plot())+Vec(.0,f->get_owidth()/2);
                if(v->get_anchor().getY()<f->get_slot_bound(v->get_plot()).getY())
                {
                    v->move_curly(spin,0);
                }
                else
                    v->move_straight(2);
                if(v->get_anchor().getX()>=f->get_reversing_point(v->get_plot()).getX()){
                    cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" successfully moves out of the plot"<<endl;
                    f->get_slot()[v->get_plot().row][v->get_plot().col]->exit_slot();
                    v->set_status(7);
                }
            }
            break;
        }
        case 7:{
            self_dect(f,v,vec_n,allv);
            if(!v->get_stop()&&detect_safe(f,v,vec_n,allv))
                v->move_straight(4);
            if(v->get_anchor().getX()>=f->get_side_turnpoint(v->get_plot().row,0).getX()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" begins to merge into the side road"<<endl;
                v->set_status(8);
            }
            break;
        }
        case 8:{
            Vec spin=f->get_side_turnpoint(v->get_plot().row,0)-Vec(.0,f->get_owidth()/2);
            v->move_curly(spin,1);
            if(v->get_anchor().getY()<=f->get_main_turnpoint(v->get_plot().row,0).getY()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" successfully merge into the main road"<<endl;
                v->set_status(9);
            }
            break;
        }
        case 9:{
            v->move_straight(2);
            if(v->get_anchor().getY()<=f->get_exit().getY()){
                cout<<"Vehicle No."<<vec_n<<" <type> "<<v->get_type()<<" reaches the exit"<<endl;

                v->set_status(10);
                v->get_departure_ticket()->set_arr(v->get_enter_time());
                v->get_departure_ticket()->set_dep(f->get_time());
                v->get_departure_ticket()->set_col(v->get_plot().col);
                v->get_departure_ticket()->set_row(v->get_plot().row);
                v->get_departure_ticket()->set_type(v->get_type());

                v->get_departure_ticket()->printTicket();
            }
            break;
        }
        case 10:{
            v->set_exit(true);
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
            vh.get_vehicle()->initsize();
            //        if(type==4)   flag=true;
            //        vh.set_plot(f->find_slot((flag)));
            //        cout<<vh.get_plot().row<<" "<<vh.get_plot().col<<endl;
#endif
            v.push_back(vh);
        }
        a.close();
    }

}
