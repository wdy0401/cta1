#if defined(DATAFEED_LIBRARY)
#define DATAFEED_EXPORT Q_DECL_EXPORT
#else
#define DATAFEED_EXPORT Q_DECL_IMPORT
#endif

#ifndef DATAFEED_H
#define DATAFEED_H

#include <QtCore/qglobal.h>
#include <QObject>
#include<string>
#include<map>
#include<list>

#include"../../gpp_qt/wtimer/wtimer.h"





class DATAFEED_EXPORT datafeed : public QObject
{
    Q_OBJECT
public:
    explicit datafeed(QObject *parent = 0);

    datafeed * genp(){return new datafeed;}
    void set_timer(wtimer * p){timer=p;}
    void set_file(const std::string & file){_file=file;}
    void run();//开始cache


signals:
    void send_quote(const std::string & ctr,const std::string & bidask,long level,double price,long size);
public slots:

private:
    wtimer * timer;
    std::string _file;

};

#endif // DATAFEED_H
