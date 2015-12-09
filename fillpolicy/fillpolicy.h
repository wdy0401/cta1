#if defined(FILLPOLICY_LIBRARY)
#define FILLPOLICY_EXPORT Q_DECL_EXPORT
#else
#define FILLPOLICY_EXPORT Q_DECL_IMPORT
#endif

#ifndef FILLPOLICY_H
#define FILLPOLICY_H

#include <QtCore/qglobal.h>

#include <QObject>
#include <set>
#include <map>
#include"order.h"
#include"quote.h"
#include"../orderbook/orderbook.h"
#include"../../gpp_qt/wtimer/wtimer.h"

class FILLPOLICY_EXPORT fillpolicy : public QObject
{
    Q_OBJECT
public:
    explicit fillpolicy(QObject *parent = 0);
    fillpolicy *genp(){return new fillpolicy;}
    void init();
    void check_fill_on_quote(const std::string & symbol,const std::string & fpn);
    void check_fill_on_quote(const std::string & symbol);
    void check_fill_on_fill(const std::string & symbol,const std::string & fpn);
    void check_fill_on_fill(const std::string & symbol);
    void set_timer(wtimer * p){timer=p;}
    bool set_fpname(const std::string & fpn){fpname=fpn;return fpnames.find(fpn)!=fpnames.end();}

signals:
    void ack(const std::string & ordername,const std::string & type,const std::string & info);
    void done(const std::string & ordername,const std::string & type,const std::string & info);
    void rej(const std::string & ordername,const std::string & type,const std::string & info);
    void fill(const std::string & ordername,const std::string symbol,const std::string buysell,double price, long size);
public slots:
    void rec_quote(const std::string & symbol,const std::string & bidask,long level,double price,long size);
    void rec_fill(const std::string & symbol,double price,long size);
    void rec_new_order(const std::string ordername,const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size);

private:
    std::map<std::string,orderbook * > ob;
    std::map <std::string,order *> _pend_order;
    std::map <std::string,order *> _run_order;
    std::map <std::string,order *> _done_order;
    std::set<std::string> fpnames;
    std::string fpname;
    wtimer * timer;
    quote * last_quote;
    fill_record * last_fill;
};

#endif // FILLPOLICY_H
