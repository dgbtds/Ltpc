#include "form.h"
#include "ui_form.h"
#include<res.h>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    ui->widget_bars->clearPlottables();

    ui->widget_bars->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->widget_bars->xAxis->setLabel("x");
    ui->widget_bars->yAxis->setLabel("y");



    ui->widget_bars->xAxis->setRange(90,110);
    ui->widget_bars->yAxis->setRange(0,1500);
    QPen Pen1;
    Pen1.setColor(Qt::blue);
    Pen1.setWidth(1);

    QVector<double> xLineVector1, yLineVector1;
    QCPBars*RTS= new QCPBars(ui->widget_bars->xAxis, ui->widget_bars->yAxis);
   RTS->setPen(Pen1);


    for(int i=0;i<200;i++)
    {
        if(Timedata[i]!=0)
        {
            xLineVector1.append(i);
            yLineVector1.append( Timedata[i]);
            printf("data[%d]:%d\n",i,Timedata[i]);
            fflush(stdout);
        }
    }
    RTS->setData(xLineVector1, yLineVector1);
    ui->widget_bars->addGraph();
    QPen Pen2;
    Pen2.setColor(Qt::red);
    Pen2.setWidth(2);
    ui->widget_bars->graph()->setData(xLineVector1, yLineVector1);
    ui->widget_bars->graph()->setPen(Pen2);
    ui->widget_bars->graph()->setLineStyle(QCPGraph::lsLine);
    ui->widget_bars->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    ui->widget_bars->replot();
}

Form::~Form()
{
    delete ui;
}
