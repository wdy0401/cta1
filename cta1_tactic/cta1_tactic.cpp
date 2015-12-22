#include "cta1_tactic.h"
#include<iostream>
#include<QDebug>
using namespace std;

void cta1_tactic::init()
{
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
    update_dkx(price,quotesize);
    if(time_to_check()==true)
    {
        gen_order();
    }
}
