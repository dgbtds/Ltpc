#include "MainWindow.h"
#include "ui_MainWindow.h"

#include<create.h>
#include<stdlib.h>    // exit
#include<string.h>    // bzero
#include <iostream>
#include <res.h>
#include<QPoint>
#define pidwdith 1
#define pidheight 2
 bool once=true;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    alydt=new Analyse;
    loadconfig=new LoadConfig;

    connect(ui->widget_color, SIGNAL(mouseRelease(QMouseEvent*)),this, SLOT(slot_mouseRelese(QMouseEvent*)));
    connect(this,SIGNAL(prompt(QString)),this,SLOT(onPrompt(QString)));
    connect(alydt,SIGNAL(prompt(QString)),this,SLOT(onPrompt(QString)));
    connect( loadconfig,SIGNAL(prompt(QString)),this,SLOT(onPrompt(QString)));
    connect(ui->widget_color, SIGNAL(mousePress(QMouseEvent*)),this, SLOT(slot_mousePress_colormap(QMouseEvent*)));
    connect(ui->widget_RTS, SIGNAL(mousePress(QMouseEvent*)),this, SLOT(slot_mousePress_Rtime(QMouseEvent*)));
    std::string path="module1.dat";
//    loadconfig->loadfile(path,pidnum,lnum);
     loadconfig->loadfile(path);


    //设置标签
    ui->tabWidget->setTabText(0,"wavedata");
    ui->tabWidget->setTabText(1,"RTS");
    ui->tabWidget->setTabText(2,"style");
    ui->tabWidget->setTabText(3,"colormap");
    ui->analyseevent->setText("0");
    ui->eventnum->setText("499");
    ui->channel->setText("1");

    QVector<QPoint>pidpoints;
    pidpoints.append(QPoint(0,5));
    pidpoints.append(QPoint(1,2));
    pidpoints.append(QPoint(2,3));
    pidpoints.append(QPoint(3,2));
    pidpoints.append(QPoint(4,3));
    pidpoints.append(QPoint(5,2));
    pidpoints.append(QPoint(6,3));
    pidpoints.append(QPoint(7,2));
    pidpoints.append(QPoint(8,3));
    pidpoints.append(QPoint(9,2));
    pidpoints.append(QPoint(10,3));
    pidpoints.append(QPoint(11,5));

    int codnum=0;
    for(int j=0;j<sizeof(lnum);j++)
    {
        if( lnum[j]==0)
            break;
            for(int i=0;i<lnum[j];i++)
            {
                pidcod[codnum].pid_a= QPoint(pidpoints[j].x(),pidpoints[j].y()+2*i);
                pidcod[codnum].pid_b= QPoint(pidpoints[j].x(),pidpoints[j].y()-pidheight+2*i);
                pidcod[codnum].pid_c= QPoint(pidpoints[j].x()+pidwdith,pidpoints[j].y()-pidheight+2*i);
                pidcod[codnum].pid_d= QPoint(pidpoints[j].x()+pidwdith,pidpoints[j].y()+2*i);
                codnum++;
            }
       }
            for(int i=0;i<128;i++)
            {
                pidcod[i].pid= pidnum[i]+(i/64)*64;

            }
//            for(int i=0;i<9;i++)
//            {
//                pidcod[i].pid_a= QPoint(0,5+2*i);
//                pidcod[i].pid_b= QPoint(0,3+2*i);
//                pidcod[i].pid_c= QPoint(1,3+2*i);
//                pidcod[i].pid_d= QPoint(1,5+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+9].pid_a= QPoint(1,2+2*i);
//                pidcod[i+9].pid_b= QPoint(1,0+2*i);
//                pidcod[i+9].pid_c= QPoint(2,0+2*i);
//                pidcod[i+9].pid_d= QPoint(2,2+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+20].pid_a= QPoint(2,3+2*i);
//                pidcod[i+20].pid_b= QPoint(2,1+2*i);
//                pidcod[i+20].pid_c= QPoint(3,1+2*i);
//                pidcod[i+20].pid_d= QPoint(3,3+2*i);
//            }

//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+31].pid_a= QPoint(3,2+2*i);
//                pidcod[i+31].pid_b= QPoint(3,0+2*i);
//                pidcod[i+31].pid_c= QPoint(4,0+2*i);
//                pidcod[i+31].pid_d= QPoint(4,2+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+42].pid_a= QPoint(4,3+2*i);
//                pidcod[i+42].pid_b= QPoint(4,1+2*i);
//                pidcod[i+42].pid_c= QPoint(5,1+2*i);
//                pidcod[i+42].pid_d= QPoint(5,3+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+53].pid_a= QPoint(5,2+2*i);
//                pidcod[i+53].pid_b= QPoint(5,0+2*i);
//                pidcod[i+53].pid_c= QPoint(6,0+2*i);
//                pidcod[i+53].pid_d= QPoint(6,2+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+64].pid_a= QPoint(6,3+2*i);
//                pidcod[i+64].pid_b= QPoint(6,1+2*i);
//                pidcod[i+64].pid_c= QPoint(7,1+2*i);
//                pidcod[i+64].pid_d= QPoint(7,3+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+75].pid_a= QPoint(7,2+2*i);
//                pidcod[i+75].pid_b= QPoint(7,0+2*i);
//                pidcod[i+75].pid_c= QPoint(8,0+2*i);
//                pidcod[i+75].pid_d= QPoint(8,2+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+86].pid_a= QPoint(8,3+2*i);
//                pidcod[i+86].pid_b= QPoint(8,1+2*i);
//                pidcod[i+86].pid_c= QPoint(9,1+2*i);
//                pidcod[i+86].pid_d= QPoint(9,3+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+97].pid_a= QPoint(9,2+2*i);
//                pidcod[i+97].pid_b= QPoint(9,0+2*i);
//                pidcod[i+97].pid_c= QPoint(10,0+2*i);
//                pidcod[i+97].pid_d= QPoint(10,2+2*i);
//            }
//            for(int i=0;i<11;i++)
//            {
//                pidcod[i+108].pid_a= QPoint(10,3+2*i);
//                pidcod[i+108].pid_b= QPoint(10,1+2*i);
//                pidcod[i+108].pid_c= QPoint(11,1+2*i);
//                pidcod[i+108].pid_d= QPoint(11,3+2*i);
//            }
//            for(int i=0;i<9;i++)
//            {
//                pidcod[i+119].pid_a= QPoint(11,5+2*i);
//                pidcod[i+119].pid_b= QPoint(11,3+2*i);
//                pidcod[i+119].pid_c= QPoint(12,3+2*i);
//                pidcod[i+119].pid_d= QPoint(12,5+2*i);
//            }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonclick(int Bnum)
{
    ui->tabWidget->setCurrentWidget(ui->widget_bars);
    int eventnum;
    bool ok;
    QString datanum=ui->analyseevent->text();

    if(datanum!=NULL)
    {
        eventnum=datanum.toUInt(&ok,10);
    }


    ui->widget_bars->clearGraphs();
    QString maxq;
    ui->MaxQ->setText(maxq.setNum(pidstc[eventnum][Bnum].MaxQ));

    emit prompt(QString("The Wavesplot Belong to event:%1; bordid: %2; chanum: %3;").arg(eventnum).arg(pidstc[eventnum][Bnum].bordnum).arg(pidstc[eventnum][Bnum].channelnum));
    fflush(stdout);

    printf("\nEvent:%d;Bordid: %d;Chanum: %d; \n",eventnum,pidstc[eventnum][Bnum].bordnum,pidstc[eventnum][Bnum].channelnum);

    for(int j=1;j<pidstc[eventnum][Bnum].get_length+1;j++)
        //printf("wavedata%d:%d;\n",j,pidstc[eventnum][Bnum].wavedata[j]);
        //emit prompt(QString("wavedata %1 :%2;").arg(j).arg(pidstc[eventnum][Bnum].wavedata[j]));
    fflush(stdout);

    ui->widget_bars->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |
                                     QCP::iSelectLegend | QCP::iSelectPlottables);


    QVector<double> x(pidstc[eventnum][Bnum].get_length+1), y(pidstc[eventnum][Bnum].get_length+1);

    for (int i=1; i<pidstc[eventnum][Bnum].get_length+1; i++)
    {
        x[i] = i;
        y[i] =(double)(pidstc[eventnum][Bnum].wavedata[i]);

    }
    ui->widget_bars->addGraph();
    ui->widget_bars->graph()->setData(x, y);
    ui->widget_bars->graph()->setLineStyle(QCPGraph::lsLine);
    ui->widget_bars->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    ui->widget_bars->xAxis->setRange(0,pidstc[eventnum][Bnum].get_length+1);
     ui->widget_bars->graph()->rescaleAxes();

    ui->widget_bars->replot();
}
void MainWindow::on_pushButton_clicked()//paint
{


    ui->tabWidget->setCurrentWidget(ui->widget_color);
    int eventnum;
    bool ok;
    QString datanum=ui->analyseevent->text();

    if(datanum!=NULL)
    {
        eventnum=datanum.toUInt(&ok,10);
    }


    ui->widget_color->clearGraphs();
    ui->widget_color->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->widget_color->axisRect()->setupFullAxesBox(true);
    ui->widget_color->xAxis->setLabel("x");
    ui->widget_color->yAxis->setLabel("y");



    ui->widget_color->setBackground(QBrush(QColor(Qt::white)));




    // set up the QCPColorMap and pidcod
    QCPColorMap *colorMap = new QCPColorMap(ui->widget_color->xAxis, ui->widget_color->yAxis);

    int nx = 12;
    int ny = 24;
    colorMap->data()->setSize(nx, ny);
    colorMap->data()->setRange(QCPRange(0.5, 11.5), QCPRange(0.5, 23.5));

    // set up the pidcod
    paintpid();

    // set up the QCPColorMap
    double  z;int Bnum;
    int xIndex,yIndex;
    xIndex=0;yIndex=3;
    for (int i=0; i<9; i++)
    {

        Bnum=pidnum[i];
        z =pidstc[eventnum][Bnum].MaxQ;
        // z=1;
        colorMap->data()->setCell(xIndex, yIndex, z);
        colorMap->data()->setCell(xIndex, yIndex+1, z);



//        printf("\nx:%d,y:%d,z:%d\n",xIndex,yIndex,pidstc[eventnum][Bnum].MaxQ);
//        fflush(stdout);
        yIndex=yIndex+2;
    }
    for( xIndex=1;xIndex<11;xIndex++)
    {
        if(xIndex%2==1)
            yIndex=0;
        else
            yIndex=1;
        for (int i=0; i<11; i++)
        {

            Bnum=pidnum[i+11*xIndex-2];
            z =pidstc[eventnum][Bnum].MaxQ;
            // z=1;
            colorMap->data()->setCell(xIndex, yIndex, z);
            colorMap->data()->setCell(xIndex, yIndex+1, z);


//            printf("\nx:%d,y:%d,z:%d\n",xIndex,yIndex,pidstc[eventnum][Bnum].MaxQ);
//            fflush(stdout);
            yIndex=yIndex+2;
        }
    }
    xIndex=11;yIndex=3;
    for (int i=0; i<9; i++)
    {

        Bnum=pidnum[119+i];
        z =pidstc[eventnum][Bnum].MaxQ;
        // z=1;

        colorMap->data()->setCell(xIndex, yIndex, z);
        colorMap->data()->setCell(xIndex, yIndex+1, z);


//        printf("\nx:%d,y:%d,z:%d\n",xIndex,yIndex,pidstc[eventnum][Bnum].MaxQ);
//        fflush(stdout);
        yIndex=yIndex+2;
    }



    // add a color scale:

    if( once)
    {
         QCPMarginGroup *marginGroup1 = new QCPMarginGroup(ui->widget_color);
        QCPColorScale *colorScale = new QCPColorScale(ui->widget_color);
        ui->widget_color->plotLayout()->addElement(0, 1, colorScale);
        colorScale->setType(QCPAxis::atRight);
        colorMap->setColorScale(colorScale);
        colorScale->axis()->setLabel("LTPC");
        colorScale->autoMargins();
        colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup1);

        once=false;
    }

    colorMap->setInterpolate(false);//使用非渐变
    colorMap->setTightBoundary(false) ;
    colorMap->setGradient(QCPColorGradient::gpJet);// 使用图例

    colorMap->rescaleDataRange(true);
    



    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->widget_color);
    ui->widget_color->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    ui->widget_color->rescaleAxes();
    ui->widget_color->replot();


}



void MainWindow::on_pushButton_7_clicked()
{
    Create create;
    create.creatdata();
}

void MainWindow::on_pushButton_8_clicked()
{

    QString qFileName=QFileDialog::getOpenFileName(this,tr("open file"), "/home/wy/Desktop/LTPC/",tr("Files(*.txt *.bin *.dat)"));
    if (qFileName.isNull())
    {
        QMessageBox::information(NULL, tr("Warning"), tr("You didn't select any files."));
        return;
    }
    else
        //QMessageBox::information(NULL, tr("path"), tr("You selected ") + qFileName,QMessageBox::Ok | QMessageBox::Cancel);
        emit prompt("You selected : "+qFileName);


    //    QString qFileName;
    //    QFileDialog *fileDialog = new QFileDialog(this);
    //    fileDialog->setWindowTitle(tr("Open File"));
    //    fileDialog->setDirectory("/home/wy/Desktop/LTPC/");
    //    fileDialog->setNameFilter(tr("Image Files(*.txt *.bin)"));
    //    if(fileDialog->exec() == QDialog::Accepted) {
    //        qFileName = fileDialog->selectedFiles()[0];
    //        QMessageBox::information(NULL, tr("path"), tr("You selected ") + qFileName);
    //    }
    //    else {
    //        QMessageBox::information(NULL, tr("path"), tr("You didn't select any files."));
    //        return;
    // }
    std::string str = qFileName.toStdString();
    const char* filename= str.c_str();
    int Event;
    bool ok;
    QString datanum=ui->eventnum->text();

    if(datanum!=NULL)
    {
        Event=datanum.toUInt(&ok,10);
    }

    alydt->analysedt(filename,Event);

}


void MainWindow::on_DWave_clicked()
{
    int Event;
    bool ok;
    QString datanum=ui->channel->text();

    if(datanum!=NULL)
    {
        Event=datanum.toUInt(&ok,10);
    }
    buttonclick(Event);
}
void MainWindow::paintpid()
{
    QPen Pen;
    Pen.setColor(Qt::white);
    Pen.setWidth(3);
    QVector<double> xLineVector1,xLineVector2, yLineVector1,yLineVector2;
    QCPGraph * curGraph1 = ui->widget_color->addGraph();
    curGraph1->setPen(Pen);
    curGraph1->setLineStyle(QCPGraph::lsLine   );
    curGraph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone , 3));
    QCPGraph * curGraph2 = ui->widget_color->addGraph();
    curGraph2->setPen(Pen);
    curGraph2->setLineStyle(QCPGraph::lsLine   );
    curGraph2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone , 3));

    for(int i=0;i<128;i++)
    {
        double ax=pidcod[i].pid_a.x();
        double ay=pidcod[i].pid_a.y();
        double bx=pidcod[i].pid_b.x();
        double by=pidcod[i].pid_b.y();
        double cx=pidcod[i].pid_c.x();
        double cy=pidcod[i].pid_c.y();
        double dx=pidcod[i].pid_d.x();
        double dy=pidcod[i].pid_d.y();


        xLineVector1 << bx <<ax << dx ;
        yLineVector1 << by<< ay <<dy  ;
        xLineVector2 <<bx <<cx << dx ;
        yLineVector2 << by<< cy << dy  ;

        curGraph1->setData(xLineVector1, yLineVector1,true);
        curGraph2->setData(xLineVector2, yLineVector2,true);
    }
}
void MainWindow::slot_mouseRelese(QMouseEvent *event)
{
    //排除非左鼠标键
    if (event->button() != Qt::LeftButton){        return;    }

    //获取点击的点坐标
    QPointF ChickedPoint = event->pos();
    //排除区间外鼠标点
    if(!ui->widget_color->viewport().contains(event->pos())){return;}
    //将像素坐标转换为轴值
    double currentx = ui->widget_color->xAxis->pixelToCoord(ChickedPoint.x());
    double currenty = ui->widget_color->yAxis->pixelToCoord(ChickedPoint.y());

    // QToolTip::showText(mapToGlobal(event->pos()),QString("当前点值为：%1").arg(currenty),this);
    int xh=belongtocoord(currentx,currenty); int pid;
    if(xh!=-1)
    {
        pid=pidnum[xh];
        cout<<pid;
        fflush(stdout);

        QString spid=QString::number(pid);

        ui->channel->setText(spid);
        buttonclick(pid);
    }
}
void MainWindow::slot_mousePress_colormap(QMouseEvent *event)
{
    //排除非左鼠标键
    if (event->button() != Qt::LeftButton){        return;    }

    //获取点击的点坐标
    QPointF ChickedPoint = event->pos();
    //排除区间外鼠标点
    if(!ui->widget_color->viewport().contains(event->pos())){return;}
    //将像素坐标转换为轴值
    double currentx = ui->widget_color->xAxis->pixelToCoord(ChickedPoint.x());
    double currenty = ui->widget_color->yAxis->pixelToCoord(ChickedPoint.y());
    int xh=belongtocoord(currentx,currenty); int pid;
    if(xh!=-1)
    {
        pid=pidcod[xh].pid;
        //QString spid=QString::number(pid);
        QToolTip::showText(mapToGlobal(event->pos()),QString("模块编号:%1").arg(pid),this);
    }
}
void MainWindow::slot_mousePress_Rtime(QMouseEvent *event)
{
    //排除非左鼠标键
    if (event->button() != Qt::LeftButton){        return;    }

    //获取点击的点坐标
    QPointF ChickedPoint = event->pos();
    //排除区间外鼠标点
    if(!ui->widget_RTS->viewport().contains(event->pos())){return;}
    //将像素坐标转换为轴值
    double currentx = ui->widget_RTS->xAxis->pixelToCoord(ChickedPoint.x());
    double currenty = ui->widget_RTS->yAxis->pixelToCoord(ChickedPoint.y());
    QToolTip::showText(mapToGlobal(event->pos()),QString("x:%1,y:%2").arg(currentx).arg(currenty),this);

}
int MainWindow::belongtocoord( double x, double y)
{
    int xx=x;
    int yy=y;
    int xh=-1;
    if (xx==0)
    {
        if( (yy>=3)&&(yy<=20))
        {
            xh=(yy-3)/2;
            return xh;
        }
        else
            return -1;
    }

    if (xx==1)
    {
        if( (yy>=0)&&(yy<=21))
        {
            xh=yy/2+9;
            return xh;
        }
        else
            return -1;
    }
    if (xx==2)
    {
        if( (yy>=1)&&(yy<=22))
        {
            xh=(yy-1)/2+20;
            return xh;
        }
        else
            return -1;
    }
    if (xx==3)
    {
        if( (yy>=0)&&(yy<=21))
        {
            xh=yy/2+31;
            return xh;
        }
        else
            return -1;
    }
    if (xx==4)
    {
        if( (yy>=1)&&(yy<=22))
        {
            xh=(yy-1)/2+42;
            return xh;
        }
        else
            return -1;
    }
    if (xx==5)
    {
        if( (yy>=0)&&(yy<=21))
        {
            xh=yy/2+53;
            return xh;
        }
        else
            return -1;
    }
    if (xx==6)
    {
        if( (yy>=1)&&(yy<=22))
        {
            xh=(yy-1)/2+64;
            return xh;
        }
        else
            return -1;
    }
    if (xx==7)
    {
        if( (yy>=0)&&(yy<=21))
        {
            xh=yy/2+75;
            return xh;
        }
        else
            return -1;
    }
    if (xx==8)
    {
        if( (yy>=1)&&(yy<=22))
        {
            xh=(yy-1)/2+86;
            return xh;
        }
        else
            return -1;
    }
    if (xx==9)
    {
        if( (yy>=0)&&(yy<=21))
        {
            xh=yy/2+97;
            return xh;
        }
        else
            return -1;
    }
    if (xx==10)
    {
        if( (yy>=1)&&(yy<=22))
        {
            xh=(yy-1)/2+108;
            return xh;
        }
        else
            return -1;
    }
    if (xx==11)
    {
        if( (yy>=3)&&(yy<=20))
        {
            xh=(yy-3)/2+119;
            return xh;
        }
        else
            return -1;
    }
    return xh;


}


void MainWindow::on_R_TMaps_clicked()
{
    bars = new Form;
    bars->show();

    ui->tabWidget->setCurrentWidget(ui->widget_RTS);
    ui->widget_RTS->clearPlottables();

    ui->widget_RTS->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->widget_RTS->xAxis->setLabel("x");
    ui->widget_RTS->yAxis->setLabel("y");



    ui->widget_RTS->xAxis->setRange(90,110);
    ui->widget_RTS->yAxis->setRange(0,1500);
    QPen Pen1;
    Pen1.setColor(Qt::blue);
    Pen1.setWidth(1);

    QVector<double> xLineVector1, yLineVector1;
    QCPBars*RTS= new QCPBars(ui->widget_RTS->xAxis, ui->widget_RTS->yAxis);
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
    ui->widget_RTS->addGraph();
    QPen Pen2;
    Pen2.setColor(Qt::red);
    Pen2.setWidth(2);
    ui->widget_RTS->graph()->setData(xLineVector1, yLineVector1);
    ui->widget_RTS->graph()->setPen(Pen2);
    ui->widget_RTS->graph()->setLineStyle(QCPGraph::lsLine);
    ui->widget_RTS->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    ui->widget_RTS->replot();
}
void MainWindow::onPrompt(QString title)
{
    QString hi=title;
    ui->log->append(hi);
}
