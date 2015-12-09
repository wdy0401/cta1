#include"orderbook.h"
#include<string>
#include<vector>
//主要功能
//实时更新orderbook，一遍match_engine使用

//目前未实现full book信息
//接口已预留

using namespace std;
void orderbook::init()
{
	_fillsize=0;
    _bidsize=0;
    _asksize=0;
}
void orderbook::updateorderbook(const std::string &bidask, long level, double price, long size)
{
	//更新nbbo
	if (level==1)
	{
        if (bidask=="BID")
		{
			_bidprice=price;
			_bidsize=size;
		}
        if (bidask=="ASK")
		{
			_askprice=price;
			_asksize=size;
		}
	}
	//更新book
    if(bidask=="BID")
	{
		_bidlevelprice[level]=price;
		_bidlevelsize[level]=size;
	}
    if(bidask=="ASK")
	{
		_asklevelprice[level]=price;
		_asklevelsize[level]=size;
	}
    if(bidask=="FILL")
	{
		_lastfillsize=_fillsize;
		_fillsize=size;
	}
}

void orderbook::setsymbol(const std::string &symbol)
{
	_symbol=symbol;
}

std::string orderbook::getsymbol()
{
	return _symbol;
}

double orderbook::getbidprice(long level)
{
	if (level<=MAXLEVEL && _bidlevelprice[level] != 0)
	{
		return _bidlevelprice[level];
	}
	return 0;	
}

double orderbook::getaskprice(long level)
{
	if (level<=MAXLEVEL && _asklevelprice[level] != 0)
	{
		return _asklevelprice[level];
	}
	return 0;
}

long orderbook::getbidsize(long level)
{
	if (level<=MAXLEVEL && _bidlevelsize[level] != 0)
	{
		return _bidlevelsize[level];
	}
	return 0;
}

long orderbook::getasksize(long level)
{
	if (level<=MAXLEVEL && _asklevelsize[level] != 0)
	{
		return _asklevelsize[level];
	}
	return 0;
}
long orderbook::getbidsize()
{
	return getbidsize(1);
}
long orderbook::getasksize()
{
	return getasksize(1);
}
double orderbook::getbidprice()
{
	return getbidprice(1);
}
double orderbook::getaskprice()
{
	return getaskprice(1);
}
long orderbook::getfillsize()
{
	return _fillsize;
}
