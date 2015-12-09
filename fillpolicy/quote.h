#ifndef QUOTE_H
#define QUOTE_H

#include<string>

struct quote
{
    std::string _symbol;
    std::string _bidask;
    long _level;
    double _price;
    long _size;
    void update(const std::string & symbol,const std::string & bidask,long level,double price,long size)
    {
        _symbol=symbol;
        _bidask=bidask;
        _level=level;
        _price=price;
        _size=size;
    }
};

struct fill_record
{
    std::string _symbol;
    double _price;
    long _size;
    void init(const std::string & symbol,double price,long size)
    {
        _symbol=symbol;
        _price=price;
        _size=size;
    }
};

#endif // ORDER_H
