#include "optionf.h"
#include "math.h"
#include "../../gpp_qt/wfunction/wmath.h"

using namespace std;\

optionf::optionf()
{
    inited=false;
}
void optionf::set_vol(long second,double price)
{
    if(inited==false)
    {
        lastp=price;
        inited=true;
        return;
    }
    vol_map[second]=log(price)-log(lastp);
    vol_list.push_front(log(price)-log(lastp));

    map <long,map<long,double>*>::iterator iter=vol_snap_map.begin();
    while(iter!=vol_snap_map.end())
    {
        if((*(iter->second)).rbegin()->first/iter->first!=second/iter->first)
        {
            (*iter->second)[second]=price;
        }
    }
}
double optionf::get_vol()
{   
    return wmath::stdev(&vol_list);
}
double optionf::get_vol_adjust()
{
    return get_vol_adjust(&vol_map);
}
double optionf::get_vol_adjust(std::map<long, double> * now_vol_map)
{
    map<long,double>::iterator it1=now_vol_map->begin();
    map<long,double>::iterator it2=it1;it2++;
    if(it2==now_vol_map->end())
    {
        return 0;
    }
    long time_length=0;
    double sum_vol=0;
    double sum_ave=0;
    while(it1!=now_vol_map->end())
    {
        if(it2!=now_vol_map->end())
        {
            long time_dur=it2->first-it1->first;
            sum_vol+=(time_dur-1)*(it2->second+it1->second)*(it2->second+it1->second)/4 + it1->second*it1->second;
            sum_ave+=it1->second+(time_dur-1)*(it2->second+it1->second)/2;
            time_length+=time_dur;
        }
        else
        {
            sum_vol+=it1->second*it1->second;
            sum_ave+=it1->second;
        }
        it1++;
        it2++;
    }
    return sqrt((sum_vol-sum_ave*sum_ave/(time_length+1))/time_length);
}
double optionf::get_vol(long seconds)
{
    map <long,map<long,double>*>::iterator iter=vol_snap_map.find(seconds);
    if(iter!=vol_snap_map.end())
    {
        return get_vol_adjust(iter->second);
    }
    else
    {
        map<long,double> * new_map=new map<long,double>;
        vol_snap_map[seconds]=new_map;
        map<long,double>::iterator it=vol_map.begin();
        long lastsec;
        while(it!=vol_map.end())
        {
            long sec=it->first;
            double value=it->second;
            if(new_map->size()==0)
            {
                (*new_map)[sec]=value;
                lastsec=sec/seconds;
            }
            else if(lastsec!=sec/seconds)
            {
                (*new_map)[sec]=value;
                lastsec=sec/seconds;
            }
            it++;
        }
        return get_vol_adjust(new_map);
    }
}

