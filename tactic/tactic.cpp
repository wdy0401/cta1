#include "tactic.h"
#ifndef SIMU
#include"ctp_order_manager.h"
#endif
#include<iostream>
#include<QDebug>
using namespace std;

void tactic::init()
{
//    load_ctrs();
//    init_ctrs();
}
void tactic::book(const CThostFtdcDepthMarketDataField *p){if(p!=nullptr){;}}
//{
////    qDebug() <<endl << "Tactic Book" << endl;
//}
void tactic::quote(const std::string & symbol, const std::string & ba, long level, double price, long quotesize)
{
//om->new_order(symbol,"SELL","OPEN",price-PRICESTEP,ORDERSZ);
}

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
void tactic::fill(const std::string & ordername,const std::string & symbol,const std::string & buysell,double price, long size)
{
    qDebug()<<endl<<"--->>> fill from tactic"<<endl;
    qDebug() << "ordername " << ordername.c_str() <<"\tsymbol\t"<<symbol.c_str() << "\tbuysell\t"<< buysell.c_str() <<"\tprice\t"<<price<<"\tsize\t"<<size<<endl;
}
