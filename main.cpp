#include "mainwindow.h"

#include <QApplication>
#include <QPluginLoader>
#include<QDateTime>
#include<QFileInfo>
#include<QDebug>
#include<QMessageBox>

#include"parameter.h"

#include"datafeed/datafeed.h"
#include"fillpolicy/fillpolicy.h"
#include"match_engine/match_engine.h"
#include"snapshot/snapshot.h"
#include"tactic/tactic.h"

#include"../gpp_qt/cmd_line/cmd_line.h"
#include"../gpp_qt/log_info/logs.h"
#include"../gpp_qt/wfunction/qtfunction.h"
#include"../gpp_qt/wtimer/wtimer.h"


int main(int argc, char *argv[])
{

    QDateTime time_counter=QDateTime::currentDateTime();//.toString("yyyy-MM-dd hh:mm:ss ddd");
    qDebug()<<time_counter.toString("yyyy-MM-dd hh:mm:ss ddd");
    QApplication a(argc, argv);

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd");
    if(current_date>"2015-12-31")
    {
        QMessageBox::about(0,"本软件已过期","请联系兴证期货资管部续期");
        return 0;
    }
    if(current_date<"2015-05-11")
    {
        QMessageBox::about(0,"日期错误","请联系兴证期货资管部");
        return 0;
    }

    cmd_line * cl=new cmd_line(argc,argv);
    logs * ls = new logs;
    wtimer * timer=new wtimer;

    datafeed * df=((datafeed *)(qtfunction::load_dll("datafeed")))->genp();
    fillpolicy * fp= ((fillpolicy *)(qtfunction::load_dll("fillpolicy")))->genp();
    match_engine * me= ((match_engine *)(qtfunction::load_dll("match_engine")))->genp();
    snapshot * ss= ((snapshot *)(qtfunction::load_dll("snapshot")))->genp();
    tactic * tc= ((tactic *)(qtfunction::load_dll("tactic")))->genp();

    df->set_timer(timer);

    fp->set_timer(timer);

    ls->set_timer(timer);
    ls->set_dir(cl->get_para("dir"));

    me->set_snapshot(ss);
    me->set_timer(timer);

    tc->set_match_engine(me);
    tc->set_timer(timer);

    QObject::connect(df,&datafeed::send_quote,me,&match_engine::rec_quote);
    QObject::connect(fp,&fillpolicy::ack,tc,&tactic::ack);
    QObject::connect(fp,&fillpolicy::fill,tc,&tactic::fill);
    QObject::connect(fp,&fillpolicy::rej,tc,&tactic::rej);
    QObject::connect(fp,&fillpolicy::done,tc,&tactic::done);
    QObject::connect(me,&match_engine::send_quote_fp,fp,&fillpolicy::rec_quote);
    QObject::connect(me,&match_engine::send_quote_tactic,tc,&tactic::quote);
    QObject::connect(me,&match_engine::send_new_order,fp,&fillpolicy::rec_new_order);
    QObject::connect(fp,&fillpolicy::fill,ls,&logs::fill);
    QObject::connect(tc,&tactic::tactic_info,ls,&logs::tactic_info);


    if(cl->has_para("gui"))
    {
        MainWindow w;
        w.set_qa(&a);
        w.show();
        QObject::connect(df,&datafeed::send_quote,&w,&MainWindow::show_quote);
        QObject::connect(me,&match_engine::send_new_order,&w,&MainWindow::show_order);
        QObject::connect(fp,&fillpolicy::fill,&w,&MainWindow::show_fill);

        fp->init();
        ls->init();
        tc->init();

        df->setfile(cl->get_para("quote_file"));
        df->run();

        qDebug()<<time_counter.msecsTo(QDateTime::currentDateTime())<<"ms";
        qDebug()<< QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        return a.exec();
    }
    else
    {
        fp->init();
        ls->init();
        tc->init();

        df->setfile(cl->get_para("quote_file"));
        df->run();

        qDebug()<<time_counter.msecsTo(QDateTime::currentDateTime())<<"ms";
        qDebug()<< QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        return 0;
    }
}
