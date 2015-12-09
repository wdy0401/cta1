#if defined(ORDER_LIBRARY)
#define ORDER_EXPORT Q_DECL_EXPORT
#else
#define ORDER_EXPORT Q_DECL_IMPORT
#endif

#ifndef ORDER_H
#define ORDER_H

#include <QtCore/qglobal.h>
#include<string>

struct order
{
    std::string ordername;

    std::string symbol;
    std::string openclose;
    std::string buysell;
    double price;
    long size;

    long size_to_fill;
    long size_filled;

    long queue_position;
};

#endif // ORDER_H
