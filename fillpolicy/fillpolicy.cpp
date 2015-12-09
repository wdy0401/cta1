#include "fillpolicy.h"
#include<QDebug>
#include<QPluginLoader>
#include<QFileInfo>
#include"../../gpp_qt/wfunction/qtfunction.h"

using namespace std;

fillpolicy::fillpolicy(QObject *parent) :
    QObject(parent)
{
    fpnames.insert("cross_fill");
    fpnames.insert("queue_fill");
    this->set_fpname("cross_fill");
    last_quote=new quote;
}
void fillpolicy::init()
{
}
void fillpolicy::rec_quote(const std::string & symbol,const std::string & bidask,long level,double price,long size)
{
    static std::map<std::string,orderbook * >::iterator iter;
    iter=ob.find(symbol);
    if(iter!=ob.end())
    {
        iter->second->updateorderbook(bidask,level,price,size);
    }
    else
    {

        orderbook * tob= ((orderbook *)(qtfunction::load_dll("orderbook")))->genp();

       // orderbook * tob=new orderbook;
        ob[symbol]=tob;
        tob->updateorderbook(bidask,level,price,size);
    }
    last_quote->update(symbol,bidask,level,price,size);
    check_fill_on_quote(symbol);
}

void fillpolicy::rec_fill(const std::string & symbol,double price,long size)
{
    //    qDebug()<<"rec_fill function not finished"<< QString::fromStdString(symbol) << price << size;
    last_fill->init(symbol,price,size);
    check_fill_on_fill(symbol);
}
void fillpolicy::rec_new_order(const std::string ordername,const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size)
{
    qDebug()<<"fillpolicy rec_new_order\n";
    order * tmporder=new order;
    tmporder->ordername=ordername;
    tmporder->symbol=symbol;
    tmporder->buysell=buysell;
    tmporder->openclose=openclose;
    tmporder->price=price;
    tmporder->size=size;
    tmporder->size_to_fill=size;
    tmporder->size_filled=0;
    tmporder->queue_position=-1;
    _pend_order[ordername]=tmporder;
}

void fillpolicy::check_fill_on_fill(const string & symbol)
{
    check_fill_on_fill(symbol,this->fpname);
}

void fillpolicy::check_fill_on_fill(const string & symbol,const string &fpn)
{
    if(fpn=="queue_fill")
    {
        for(map<string,order *>::iterator iter=_run_order.begin(); iter!=_run_order.end();)
        {
            if(iter->second->symbol != symbol)
            {
                ++iter;
            }
            else if(iter->second->price == last_fill->_price)
            {
               if(iter->second->queue_position>=last_fill->_size)
               {
                   iter->second->queue_position -= last_fill->_size;
                   iter++;
               }
               else if(iter->second->size_to_fill < (last_fill->_size - iter->second->queue_position))
               {
                   iter->second->size_filled+=(last_fill->_size - iter->second->queue_position);
                   iter->second->size_to_fill=iter->second->size - iter->second->size_filled;
                   emit fill(iter->first,symbol,iter->second->buysell,last_fill->_price,last_fill->_size - iter->second->queue_position);
                   iter->second->queue_position = 0;
                   iter++;
               }
               else
               {
                    emit fill(iter->first,symbol,iter->second->buysell,last_fill->_price,iter->second->size_to_fill);
                    _done_order[iter->first]=iter->second;
                    _run_order.erase(iter++);
               }
            }
            else if((iter->second->price > last_fill->_price && iter->second->buysell=="BUY") || (iter->second->price < last_fill->_price && iter->second->buysell=="SELL"))
            {
                emit fill(iter->first,symbol,iter->second->buysell,iter->second->price,iter->second->size_to_fill);
                _done_order[iter->first]=iter->second;
                _run_order.erase(iter++);
            }
            else
            {
                ++iter;
            }
        }
    }
}
void fillpolicy::check_fill_on_quote(const string & symbol)
{
    check_fill_on_quote(symbol,this->fpname);
}

void fillpolicy::check_fill_on_quote(const string & symbol,const string &fpn)
{
    if(fpn=="cross_fill")
    {
        //消息fill					检测run上有哪些order可成交 成交之
        //转区fill					将成交完成的移入done list
        //消息change ack rej done	检测run done这两个list中的change tag 并处理之
        //转区						将pend区转换到run区

        //消息fill
        //转区fill

       orderbook * now_ob=ob[symbol];
        if(now_ob->init_done()==false)
        {
            return;
        }
        for(map<string,order *>::iterator iter=_run_order.begin(); iter!=_run_order.end();)
        {
            qDebug()<<"orderprice"                        <<"\t"<<iter->second->price                      <<"\t"<< iter->second->buysell.c_str()                          <<"\t"<<now_ob->getaskprice()                        <<"\t"<< now_ob->getbidprice()                        <<endl;
            if(iter->second->symbol != symbol)
            {
                ++iter;
            }
            else if(iter->second->price>=now_ob->getaskprice() && iter->second->buysell=="BUY")
            {
                emit fill(iter->first,symbol,"BUY",now_ob->getaskprice(),iter->second->size_to_fill);
                _done_order[iter->first]=iter->second;
                _run_order.erase(iter++);
            }
            else if(iter->second->price<=now_ob->getbidprice() &&iter->second->buysell=="SELL")
            {
                emit fill(iter->first,symbol,"SELL",now_ob->getbidprice(),iter->second->size_to_fill);
                _done_order[iter->first]=iter->second;
                _run_order.erase(iter++);
            }
            else
            {
                ++iter;
            }
        }

        //消息change
        //成功部分
        /*
        for(map<string,order *>::iterator iter=_run_order.begin(); iter!=_run_order.end();)
        {
            if(iter->second->_tag_cancel)
            {
                iter->second->changeack("cancel");
                _done_order[iter->first]=iter->second;
                iter->second->changedone("cancel");
                _run_order.erase(iter++);
                continue;
            }
            else
            {
                ++iter;
                continue;
            }
            if(iter->second->_tag_changeprice)
            {
                iter->second->changeack("price");
                iter->second->price=iter->second->_tag_changeprice;
                iter->second->changedone("price");
            }
            if(iter->second->_tag_changesize)
            {

                iter->second->changeack("size");
                iter->second->price=iter->second->_tag_changesize;
                iter->second->changedone("size");
            }
            ++iter;
        }
        //失败部分
        for(map<string,order *>::iterator iter=_done_order.begin();iter!=_done_order.end();iter++)
        {
            if(iter->second->_tag_cancel)
            {
                iter->second->changeack("cancel");
                iter->second->changerej("cancel");
            }
            if(iter->second->_tag_changeprice)
            {
                iter->second->changeack("price");
                iter->second->changerej("price");
            }
            if(iter->second->_tag_changesize)
            {
                iter->second->changeack("size");
                iter->second->changerej("size");
            }
        }
        */
        //转区pend 并清空
        for(map<string,order *>::iterator iter=_pend_order.begin();iter!=_pend_order.end();iter++)
        {
            _run_order[iter->first]=iter->second;
        }
        _pend_order.clear();

        return;
    }
    if(fpn=="queue_fill")
    {
/////////////////////////////////////////////////////////////////////////////////////////////////
//只有第一次需要orderbook信息
//其他时间只需要quote信息与fil信息
//quote信息决定了queue max位置
//fill信息决定了在order 是如何在queue中前进的
//也就是只在 pending时候看一看orderbook 之后就只看quote与fill
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
//	更复杂的做法是达到队列头后看fill数 或价格达到触价后看触价size  下面说明了复杂方法带来的问题
//	看fill需要处理一旦跳的更高，其后端的各个level问题
//	我们无法知悉所有可fiil level 的size加总信息，
//	即便能得到加总信息，也无法利用此加总信息，
//	因为若认为加总size就是本次fp执行的size，
//	存在着与利用交易方给出fillsize重复统计的问题。
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
//	综合上面讨论，本fp方式为：
//	在level one
//	队首 看此价位fill size成交
//	队中 利用此价位fill size移动位置 同时此价位ob中的size 为order的max queue size
//	在level n 不成交，会利用此价位此价位ob中的size 为order的max queue size
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
//虽然可以只看quote 但为同一处理逻辑起见 仍旧写成看ob的形式
/////////////////////////////////////////////////////////////////////////////////////////////////
        orderbook * now_ob=ob[symbol];
         if(now_ob->init_done()==false)
         {
             return;
         }
        for(map<string,order *>::iterator iter=_run_order.begin(); iter!=_run_order.end();)
        {
            qDebug()<<"orderprice"                        <<"\t"<<iter->second->price                      <<"\t"<< iter->second->buysell.c_str()                          <<"\t"<<now_ob->getaskprice()                        <<"\t"<< now_ob->getbidprice()                        <<endl;
            if(iter->second->symbol != symbol)
            {
                ++iter;
            }
            else if(iter->second->price >= now_ob->getaskprice() && iter->second->buysell=="BUY")
            {
                emit fill(iter->first,symbol,"BUY",now_ob->getaskprice(),iter->second->size_to_fill);
                _done_order[iter->first]=iter->second;
                _run_order.erase(iter++);
            }
            else if(iter->second->price == now_ob->getbidprice() && iter->second->buysell=="BUY")
            {
                if(iter->second->queue_position > now_ob->getbidsize())
                {
                    iter->second->queue_position=now_ob->getbidsize();
                }
                iter++;
            }
            else if(iter->second->price <= now_ob->getbidprice() &&iter->second->buysell=="SELL")
            {
                emit fill(iter->first,symbol,"SELL",now_ob->getbidprice(),iter->second->size_to_fill);
                _done_order[iter->first]=iter->second;
                _run_order.erase(iter++);
            }
            else if(iter->second->price == now_ob->getaskprice() && iter->second->buysell=="SELL")
            {
                if(iter->second->queue_position > now_ob->getasksize())
                {
                    iter->second->queue_position=now_ob->getasksize();
                }
                iter++;
            }
            else
            {
                ++iter;
            }
        }
        for(map<string,order *>::iterator iter=_pend_order.begin();iter!=_pend_order.end();)
        {
            if((last_quote->_bidask=="BID" && iter->second->buysell=="BUY")||(last_quote->_bidask=="ASK" && iter->second->buysell=="SELL"))
            {
                iter->second->queue_position= last_quote->_size;
                _run_order[iter->first]=iter->second;
                _pend_order.erase(iter++);
            }
            iter++;
        }
    }
}

