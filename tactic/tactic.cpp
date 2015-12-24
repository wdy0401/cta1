#include "tactic.h"
#include<iostream>
#include<algorithm>
#include<QDebug>
#include<QFile>
#include"../../gpp_qt/wfunction/wfunction.h"
using namespace std;

void tactic::init()
{
    load_his_dkx();
    _target=0;
    _bar_minute=15;
}
void tactic::book(const snapshot *p){if(p!=nullptr){;}}
//{
////    qDebug() <<endl << "Tactic Book" << endl;
//}

void tactic::ack(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> ack from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void tactic::done(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> done from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void tactic::rej(const std::string & ordername,const std::string & type,const std::string & info)
{
    qDebug()<<endl<<"--->>> rej from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\ttype\t"<<type.c_str()<<"\tinfo\t"<<info.c_str()<<endl;
}
void tactic::fill(const std::string & ordername,const std::string & ctr,const std::string & buysell,double price, long size)
{
    qDebug()<<endl<<"--->>> fill from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\tctr\t"<<ctr.c_str() << "\tbuysell\t"<< buysell.c_str() <<"\tprice\t"<<price<<"\tsize\t"<<size<<endl;
}


void tactic::quote(const std::string & ctr, const std::string & ba, long level, double price, long quotesize)
{
    if(ctr != _ctr){return;}
    if(is_trading_time(_symbol)==false){return;}
    is_new_bar();
    if(_is_new_bar==true)
    {
        set_target();
    }
    else
    {

    }
    if(_target!=0)
    {
        emit show_target(_target);
    }
    update_dkx(price);
}
void tactic::is_new_bar()
{
    static int minute=0;
    //在分发quote时检查是否在交易时间 或在quote中检查时间 目前倾向于在quote中检查时间
    static int nt=timer->nowtic();//now time
    nt=nt-0.000001;//第0秒的不计入新bar
    nt=int(nt*10000)-(int(nt*100))*100;
    if(int(nt/15)==minute)
    {
        _is_new_bar=false;
    }
    else
    {
        minute=int(nt/15);
        _is_new_bar=false;
    }
}
void tactic::update_dkx(double price)
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
void tactic::set_target()
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
        _target=1;
    }
    if(_dkx_d.bs.front()->b < sum/20 && this->_lon < 0)
    {
        _target=-1;
        //emit f(_ctr,BUY,1,price);
    }
}

bool tactic::is_trading_time(const string & _symbol)
{
    string sym=_symbol;
    transform(sym.begin(), sym.end(), sym.begin(), ::toupper);
    int nt=timer->nowtic();//now time
    int hour=int(nt*100)-int(nt)*100;
    int minute=int(nt*10000)-int(nt*100)*100;
    if(sym=="IF" ||sym=="IH" ||sym=="IC" ||sym=="TF" ||sym=="TF")
    {
        if(
                 (hour==9 && minute>=15)
            ||   (hour==10)
            ||   (hour==11 && minute<=30)
            ||   (hour==1)
            ||   (hour==2)
            ||   (hour==3 && minute<=15)
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(
                 (hour==9)
            ||   (hour==10 && minute<=15)
            ||   (hour==10 && minute>=30)
            ||   (hour==11 && minute<=30)
            ||   (hour==1)
            ||   (hour==2)
            ||   (hour==3 && minute<1)
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
void tactic::load_his_dkx()
{
    QFile file(QString::fromStdString("c:/dkx/"+_symbol+".txt"));

   if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       return;
   }
   while (!file.atEnd()) {
       QByteArray line = file.readLine();
       string tmpstring=line.data();
       if(tmpstring!="")
       {
           list<string> lists=wfunction::splitstring(tmpstring);
           list<string>::iterator iter=lists.begin();

           double	nowtime=atof(iter->c_str());
           timer->settic(nowtime);
           string	ctr=(++iter)->c_str();
           string	bidask=(++iter)->c_str();
           long     level=atol((++iter)->c_str());
           double	price=atof((++iter)->c_str());
           long     size=atol((++iter)->c_str());
           if(bidask=="OPEN")
           {
               _is_new_bar=true;
           }
           else
           {
               _is_new_bar=false;
           }
           update_dkx(price);
       }
   }
    timer->settic(0);
    _is_new_bar=false;
}
