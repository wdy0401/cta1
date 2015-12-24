#include "datafeed.h"

#include"../../gpp_qt/wfunction/wfunction.h"

#include<QFile>
#include<iostream>
#include<string>
#include<list>

#include<QDebug>

using namespace std;

datafeed::datafeed(QObject *parent) :
    QObject(parent)
{
}



void datafeed::run()
{
    QFile file(_file.c_str());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       return;
    }
    while (!file.atEnd())
    {
        string tmpstring= file.readLine().data();
        if(tmpstring!="")
        {
            list<string> lists=wfunction::splitstring(tmpstring);
            list<string>::iterator iter=lists.begin();

            double	nowtime=atof(iter->c_str());
            timer->settic(nowtime);
            string	ctr=(++iter)->c_str();
            string	bidask=(++iter)->c_str();
            long     level=atol((++iter)->c_str());
            double	price=atof((++iter)->c_str());
            long     size=atol((++iter)->c_str());
            emit send_quote(ctr,bidask,level,price,size);
        }
    }
}

