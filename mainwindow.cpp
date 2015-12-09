#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"../gpp_qt/wfunction/wfunction.h"
#include<string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_quote(const std::string & symbol,const std::string & bidask,long level,double price,long size)
{
    std::string tmpstr;
    tmpstr=symbol+"\t"+bidask+"\t"+wfunction::itos(level)+"\t"+wfunction::ftos(price)+"\t"+wfunction::itos(size)+"\t";
    this->ui->textBrowser->append(QString::fromStdString(tmpstr));
    qa->processEvents();
}
void MainWindow::show_order(const std::string ordername,const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size)
{

    string tmpstr=ordername+"    \t"+symbol+"\t"+buysell+"\t"+openclose+"\t"+wfunction::ftos(price)+"\t"+wfunction::itos(size);
    this->ui->textBrowser_2->append(QString::fromStdString(tmpstr));
    qa->processEvents();
}

void MainWindow::show_fill(const std::string & ordername,const std::string symbol,const std::string buysell,double price, long size)
{
    std::string tmpstr;
    tmpstr=ordername+"    \t"+symbol+"\t"+buysell+"\t"+wfunction::ftos(price)+"\t"+wfunction::itos(size);
    this->ui->textBrowser_4->append(QString::fromStdString(tmpstr));
    qa->processEvents();
}
