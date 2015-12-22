#include "cta1_tactic.h"
#include<iostream>
#include<QDebug>
using namespace std;

void cta1_tactic::init()
{
    _dkx_b= new dkx_b;
    _dkx_d= new dkx_d;
    load_his_dkx();
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
    update_dkx(price);
    if(time_to_check()==true)
    {
        gen_order();
    }
}
bool cta1_tactic::is_new_bar()
{
    return true;
}
void cta1_tactic::update_dkx(double price)
{
    if(is_new_bar()==true)
    {
        _bar =new bar;
        _bar->open=price;
        _bar->high=price;
        _bar->low=price;
        _bar->close=price;
        _bar->a=price;

        for(auto iter=_dkx_d.bs.back();;)//把所有的b都更改 然后把不需要的b移出 还要把b输出以备次日使用
        {
            if(iter==_dkx_d.bs.front()){break;}
            iter--;
        }
    else
    {
        if(_bar->high <price){_bar->high=price;}
        if(_bar->low  >price){_bar->low =price;}
        _bar->close=price;
        _bar->a=(_bar->open+_bar->high+_bar->low+3*_bar->close)/6;
    }


    this->_dkx_b=new dkx_b;
    _dkx_d.bs.push(_dkx_b);


}
//struct bar
//{
//    double open;
//    double high;
//    double low;
//    double close;
//    double volume;
//    double a;//(o+h+l+3*c)/6
//};
//struct dkx_b
//{
//    std::queue<bar *> bars;
//    double b;//sum(bar[n].(20-n))/210
//} _dkx_b;
//struct dkx_d
//{
//    std::queue<dkx_b *> bs;
//    double d;//sum(bar[0..19])/20
//}_dkx_d;
