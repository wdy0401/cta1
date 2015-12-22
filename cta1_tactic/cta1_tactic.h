#if defined(TACTIC_LIBRARY)
#define TACTIC_EXPORT Q_DECL_EXPORT
#else
#define TACTIC_EXPORT Q_DECL_IMPORT
#endif

#ifndef TACTIC_H
#define TACTIC_H

#include<QtCore/qglobal.h>
#include<QObject>

#include<queue>
#include<string>

#include "../../gpp_qt/bar/bar.h"
#include "../parameter.h"
#include"../../gpp_qt/wtimer/wtimer.h"

#include"../snapshot/snapshot.h"
#include"../match_engine/match_engine.h"

class TACTIC_EXPORT cta1_tactic: public QObject
{
    Q_OBJECT
public:
    void set_match_engine(match_engine * p){om=p;}
    cta1_tactic *genp(){return new cta1_tactic;}
    void init();
    void send_order();
    void set_timer(wtimer * p){timer=p;}
signals:
    void tactic_info(const std::string & info);
public slots:
    virtual void book(const snapshot *p);
    virtual void quote(const std::string & symbol, const std::string & ba, long level, double price, long quotesize);
    virtual void ack(const std::string & ordername,const std::string & type,const std::string & info);
    virtual void done(const std::string & ordername,const std::string & type,const std::string & info);
    virtual void rej(const std::string & ordername,const std::string & type,const std::string & info);
    virtual void fill(const std::string & ordername,const std::string & symbol,const std::string & buysell,double price, long size);
private:
    match_engine * om;
    wtimer * timer;


    //for cta1 tactic
public:
    void set_symbol(const std::string & symbol){_symbol=symbol;}
    void load_his_lon(){}
    void load_his_dkx(){}
    void update_dkx(double a,long b){}
    void gen_order(){}
private:
    std::string _symbol;
    bool time_to_check(){return true;}
    double  _lon;
    std::queue<double> _dkx;
    struct bar
    {
        double open;
        double high;
        double low;
        double close;
        double volume;
        double a;//(o+h+l+3*c)/6
    };
    struct dkx_b
    {
        std::queue<bar *> bars;
        double b;//sum(bar[n].(20-n))/210
    } _dkx_b;
    struct dkx_d
    {
        std::queue<dkx_b *> bs;
        double d;//sum(bar[0..19])/20
    }_dkx_d;
    //additional queue is needed when cal lon and dkx
};

#endif // TACTIC_H
