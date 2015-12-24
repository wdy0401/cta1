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
    void show_target(long);
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
    void update_dkx(double);
    void set_target();
    void set_bar_minute(int m){_bar_minute=m;}
private:
    void is_new_bar();
    bool is_trading_time(const std::string &);
    bool time_to_check(){return true;}

    std::string _symbol;
    bool _is_new_bar;
    double _lon;
    long target;
    std::queue<double> _dkx;
    int _bar_minute;
    struct bar
    {
        double open;
        double high;
        double low;
        double close;
        double volume;
        double a;//(o+h+l+3*c)/6
    };
    bar *_bar;
    struct dkx_b
    {
        std::queue<bar *> bars;
        double b;//sum(bar[n].(20-n))/210
    };
    dkx_b *_dkx_b;
    struct dkx_d
    {
        std::queue<dkx_b *> bs;
        double d;//sum(bar[0..19])/20
    }_dkx_d;
    //additional queue is needed when cal lon and dkx
};

#endif // TACTIC_H


//历史dkx的产生和load
//当日存储dkx可以不在程序内进行 使用perl进行


//历史数据格式使用perl处理成 时间  symbol ba level price size 这种形式 接收均使用此形式 然后回测时直接读取输出便是
