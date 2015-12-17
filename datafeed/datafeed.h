#if defined(DATAFEED_LIBRARY)
#define DATAFEED_EXPORT Q_DECL_EXPORT
#else
#define DATAFEED_EXPORT Q_DECL_IMPORT
#endif

#ifndef DATAFEED_H
#define DATAFEED_H

#include <QtCore/qglobal.h>
#include <QObject>
#include<fstream>
#include<string>
#include<map>
#include<list>

#include"../../gpp_qt/wtimer/wtimer.h"

//合并数据已经实现，由于涉及到string的比较问题，效率较低
//这里仍旧涉及到标准数据的表示方式问题，如标准化则可以利用更有效的方式来进行比较


#define FILE_RECORD_BUFFER 10000

class DATAFEED_EXPORT datafeed : public QObject
{
    Q_OBJECT
public:
    explicit datafeed(QObject *parent = 0);

    datafeed * genp(){return new datafeed;}
    void set_timer(wtimer * p){timer=p;}
    void run();//开始cache


signals:
    void send_quote(const std::string & symbol,const std::string & bidask,long level,double price,long size);
public slots:

private:
    wtimer * timer;

};

#endif // DATAFEED_H
