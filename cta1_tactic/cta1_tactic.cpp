#include "cta1_tactic.h"
#include<iostream>
#include<QDebug>
using namespace std;

void cta1_tactic::init()
{
    load_his_dkx();
    target=0;
}
void cta1_tactic::book(const snapshot *p){if(p!=nullptr){;}}
//{
////    qDebug() <<endl << "Tactic Book" << endl;
//}

void cta1_tactic::ack(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> ack from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void cta1_tactic::done(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> done from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void cta1_tactic::rej(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> rej from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void cta1_tactic::fill(const std::string & ordername,const std::string & symbol,const std::string & buysell,double price, long size)
{
    qDebug()<<endl<<"--->>> fill from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\tsymbol\t"<<symbol.c_str() << "\tbuysell\t"<< buysell.c_str() <<"\tprice\t"<<price<<"\tsize\t"<<size<<endl;
}


void cta1_tactic::quote(const std::string & symbol, const std::string & ba, long level, double price, long quotesize)
{
    if(symbol != _symbol){return;}
    is_new_bar();
    if(_is_new_bar==true)
    {
        set_target();
    }
    else
    {

    }
    if(target!=0)
    {
        emit show_target(target);
    }
    update_dkx(price);
}
void cta1_tactic::is_new_bar()
{
    //static int minute=0; 问题在于now_minute如何得到
    //在分发quote时检查是否在交易时间 或在quote中检查时间 目前倾向于在quote中检查时间
//    if(int(now_minute/15)==minute)
//    {
//        _is_new_bar=false;
//    }
//    else
//    {
//        minute=int(now_minute/15);
//        _is_new_bar=false;
//    }
    _is_new_bar=true;
}
void cta1_tactic::update_dkx(double price)
{
    if(_is_new_bar==true)
    {
        _bar =new bar;
        _bar->open=price;
        _bar->high=price;
        _bar->low=price;
        _bar->close=price;
        _bar->a=price;

        this->_dkx_b=new dkx_b;
        _dkx_d.bs.push(_dkx_b);

       //用次新b给最新b赋值，然后再将最近bar放入最新b
       if(_dkx_d.bs.size()!=0)
       {
           dkx_b * lastb=_dkx_d.bs.back();
           for(auto iter=lastb->bars.front();;iter++)
           {
                _dkx_b->bars.push(iter);
                if(iter==lastb->bars.back())
                {
                    break;
                }
           }
       }
       _dkx_b->bars.push(_bar);
    }
    else
    {
        if(_bar->high < price){_bar->high=price;}
        if(_bar->low  > price){_bar->low =price;}
        _bar->close=price;
        _bar->a=(_bar->open+_bar->high+_bar->low+3*_bar->close)/6;
    }
}
void cta1_tactic::set_target()
{
    if(int(_dkx_d.bs.size())<=20)
    {
        return;
    }
    if(int(_dkx_d.bs.back()->bars.size())<=20)
    {
        return;
    }
    int count=20;
    double sum=0;
    for(auto iter=_dkx_d.bs.front();;)
    {
        double sum_next=0;
        int count_next=20;
        for(auto iter_next=iter->bars.front();;)
        {
            sum_next+=count_next*iter_next->a;
            count_next--;
            if(count_next==0)
            {
                break;
            }
        }
        iter->b=sum_next/210;
        sum+=iter->b;
        count--;
        if(count==0)
        {
            break;
        }
    }
    if(_dkx_d.bs.front()->b > sum/20 && this->_lon > 0)
    {
        target=1;
    }
    if(_dkx_d.bs.front()->b < sum/20 && this->_lon < 0)
    {
        target=-1;
        //emit f(_symbol,BUY,1,price);
    }
}
