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

class tactic: public QObject
{
    Q_OBJECT
public:
    void set_match_engine(match_engine * p){om=p;}
    tactic *genp(){return new tactic;}
    void init();
    void send_order(){;}
    void set_timer(wtimer * p){timer=p;}
signals:
    void tactic_info(const std::string & info);
    void show_target(long);
public slots:
    virtual void book(const snapshot *p);
    virtual void quote(const std::string & ctr, const std::string & ba, long level, double price, long quotesize);
    virtual void ack(const std::string & ordername,const std::string & type,const std::string & info);
    virtual void done(const std::string & ordername,const std::string & type,const std::string & info);
    virtual void rej(const std::string & ordername,const std::string & type,const std::string & info);
    virtual void fill(const std::string & ordername,const std::string & ctr,const std::string & buysell,double price, long size);
private:
    match_engine * om;
    wtimer * timer;


    //for cta1 tactic
public:
    void set_ctr(const std::string & ctr){_ctr=ctr;}
    void set_symbol(const std::string & symbol){_symbol=symbol;}
    void set_target();
    void set_bar_minute(int m){_bar_minute=m;}
    void set_lon(double lon){_lon=lon;}
    void load_his_dkx();
    void update_dkx(double);
private:
    void is_new_bar();
    bool is_trading_time(const std::string &);

    bool        _is_new_bar;
    double      _lon;
    long        _target;
    int         _bar_minute;

    std::string         _symbol;
    std::string         _ctr;
    std::queue<double>  _dkx;

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
};

#endif // TACTIC_H


//历史dkx的产生
//dkx格式与quote一致 time ctr ba level price size每个bar有4行 分别为ohlc 使用ba来表示ohlc
//load lon

//历史数据格式使用perl处理成 time ctr ba level price size 这种形式 接收均使用此形式 然后回测时直接读取输出便是
