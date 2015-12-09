#if defined(MATCH_ENGINE_LIBRARY)
#define MATCH_ENGINE_EXPORT Q_DECL_EXPORT
#else
#define MATCH_ENGINE_EXPORT Q_DECL_IMPORT
#endif

#ifndef MATCH_ENGINE_H
#define MATCH_ENGINE_H

#include <QtCore/qglobal.h>

#include <QObject>
#include<string>
#include"../../gpp_qt/wtimer/wtimer.h"
class orderbook;
class snapshot;
class MATCH_ENGINE_EXPORT match_engine : public QObject
{
    Q_OBJECT
public:
    match_engine *genp(){return new match_engine;}
    explicit match_engine(QObject *parent = 0);
    std::string new_order(const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size);

    void set_snapshot(snapshot * p){ss=p;}
    void set_timer(wtimer * p){timer=p;}

signals:
    void send_quote_fp(const std::string & symbol,const std::string & bidask,long level,double price,long size);
    void send_quote_tactic(const std::string & symbol,const std::string & bidask,long level,double price,long size);
    void send_new_order(const std::string ordername,const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size);

public slots:
    void rec_quote(const std::string & symbol,const std::string & bidask,long level,double price,long size);

private:
    snapshot * ss;
    wtimer * timer;
    long order_count;
};

#endif // MATCH_ENGINE_H
