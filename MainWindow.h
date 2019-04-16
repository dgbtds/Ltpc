#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <form.h>
#include <Analyse.h>
#include<LoadConfig.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void buttonclick(int i);
    int belongtocoord( double x, double y);
  Form*bars;
private slots:

   void onPrompt(QString title);
    void paintpid( );
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();
    void on_pushButton_clicked();
     void on_DWave_clicked();
     void slot_mouseRelese(QMouseEvent*);
      void slot_mousePress_colormap(QMouseEvent*);
      void slot_mousePress_Rtime(QMouseEvent*);
      void on_R_TMaps_clicked();


signals:
       void prompt(QString title);

private:
 Ui::MainWindow *ui;
  Analyse*alydt;
  LoadConfig*loadconfig;
};


#endif // MAINWINDOW_H
