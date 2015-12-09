#include "match_engine.h"
#include"../orderbook/orderbook.h"
#include"../fillpolicy/fillpolicy.h"
#include"../tactic/tactic.h"

#include"../../gpp_qt/wfunction/wfunction.h"

using namespace std;
match_engine::match_engine(QObject *parent) :
    QObject(parent)
{
    order_count=0;
}

std::string match_engine::new_order(const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size)
{
    order_count++;
    string ordername=symbol+"_"+buysell+"_"+openclose+"_"+wfunction::ftos(price)+"_"+wfunction::itos(size)+"_"+wfunction::ftos(order_count);
    emit send_new_order(ordername,symbol,buysell,openclose,price,size);
    return "";
}

void match_engine::rec_quote(const std::string & symbol,const std::string & bidask,long level,double price,long size)
{
    emit send_quote_fp(symbol,bidask,level,price,size);
    emit send_quote_tactic(symbol,bidask,level,price,size);
}

