#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void set_qa(QApplication * p){qa=p;}
public slots:
    void show_quote(const std::string & symbol,const std::string & bidask,long level,double price,long size);
    void show_order(const std::string ordername,const std::string symbol,const std::string buysell, const std::string & openclose ,double price,long size);
    void show_fill(const std::string & ordername,const std::string symbol,const std::string buysell,double price, long size);
private:
    Ui::MainWindow *ui;
    QApplication * qa;
};

#endif // MAINWINDOW_H
