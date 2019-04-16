#include "Analyse.h"
#include<stdio.h>    // printf
#include<stdlib.h>    // exit
#include<string.h>    // bzero
#include <iostream>
#include <res.h>

#define BUFFER_SIZE 1000
#define ladheader 0xF9ADC9C9
#define ladtrailer 0x5A5A5A5A
using namespace std;
Analyse::Analyse(QObject *parent) : QObject(parent)
{

}
Analyse::~Analyse()
{

}
int Analyse::analysedt(const char* file_name,int Event)
{

    int thefirst=1;
    FILE *fp= fopen(file_name, "ab+");

    if(NULL == fp)
    {
        printf("File:%s Not Found\n", file_name);
    }
    else
    {
        printf("File:%s has been open\n", file_name);
    }

    int length,packnum=0,bordid,pid,channel,P,offset,pcklength=0,a;
    unsigned char buffer[BUFFER_SIZE];

    bzero(buffer, BUFFER_SIZE);
    int eventnum=0,trigger=0,trigger_temp;
    bzero(Timedata,200);
    alleventnum=0;
    for(int i=0;i<500;i++)
    {
        for(int j=0;j<129;j++)
        {
            pidstc[i][j].bordnum=0;
            pidstc[i][j].channelnum=0;
            pidstc[i][j].get_length=0;
            pidstc[i][j].MaxQ=0;
            pidstc[i][j].RTS=0;
            pidstc[i][j].Tcount=0;
            pidstc[i][j].triggerid=0;
            pidstc[i][j].TS=0;
            bzero(pidstc[i][j].wavedata,300) ;
        }
    }
    while(eventnum<Event)
        //  int s=0;
        //  while(s<1)
    {
        //s++;
        length=fread(buffer, sizeof(char), 4, fp),offset=0;
        if(length<4)
            break;
        while ( ((buffer[0+offset]<<24)|(buffer[1+offset]<<16)|(buffer[2+offset]<<8)|(buffer[3+offset])) !=ladheader)  //　校验头部，注意括号　移位并

        {
            length=fread(&buffer[4+offset], sizeof(char),1,fp);

            if(offset==0)
                printf("****%02x %02x %02x%02x ",(buffer[0+offset]),(buffer[1+offset]),(buffer[2+offset]),(buffer[3+offset]));
            printf("%02x ",(buffer[3+offset]));
            fflush(stdout);
            offset++;
        }
        //printf("****%02x %02x %02x%02x \n",(buffer[0+offset]),(buffer[1+offset]),(buffer[2+offset]),(buffer[3+offset]));
        buffer[0]=(ladheader&(0xff000000) )>>24;
        buffer[1]= (ladheader&(0x00ff0000) )>>16 ;
        buffer[2]= (ladheader&(0x0000ff00) )>>8 ;
        buffer[3]= ladheader&(0x000000ff)  ;
        // printf("&&&&&%02x %02x %02x%02x \n",(buffer[0+offset]),(buffer[1+offset]),(buffer[2+offset]),(buffer[3+offset]));
        length=fread(&buffer[4], sizeof(char), 4, fp);
        P=( buffer[6]&(0x80) )>>7;

        // printf("buffer7is : %02x\n",buffer[7]);


        pcklength=( ( ( (buffer[6]&(0xf0))>>4)<<8)|(buffer[7]) )*8;
        //printf("pcklength is : %d\n",pcklength);
        length=fread(&buffer[8], sizeof(char), pcklength-8, fp);
        if(P==0)
        {
            if( ((buffer[  pcklength-4]<<24)|(buffer[ pcklength-3]<<16)|(buffer[ pcklength-2]<<8)|(buffer[ pcklength-1])) ==ladtrailer)
            {
                packnum++;
                printf("the %d package   is correct;",packnum);
                fflush(stdout);

            }
            else
            {
                packnum++;
                printf("!!!!!!!!!!!!!!!!trailer of the %d package is error:\n",packnum);
                printf("&&&&&%02x %02x %02x%02x \n",(buffer[pcklength-4]),(buffer[pcklength-3]),(buffer[pcklength-2]),(buffer[pcklength-1]));
                fflush(stdout);
                break;
            }
        }
        else
        {
            if(
                    ( ((buffer[  pcklength-4]<<24)|(buffer[ pcklength-3]<<16)|(buffer[ pcklength-2]<<8)|(buffer[ pcklength-1])) ==0x00000000)&&
                    (   ( ((buffer[  pcklength-8]<<24)|(buffer[ pcklength-7]<<16)|(buffer[ pcklength-6]<<8)|(buffer[ pcklength-5])) ==ladtrailer))
                    )
            {
                packnum++;
                printf("the %d package   is correct;\n",packnum);
                emit prompt(QString("the %1 package   is correct;").arg(packnum));
                fflush(stdout);

            }
            else
            {
                packnum++;
                printf("!!!!!!!!!!!!!!!!trailer of the %d package is error:  \n",packnum);
                fflush(stdout);
                break;
            }
        }
        if(thefirst==1)
        {
            trigger=(buffer[18]<<8)|buffer[19];
            thefirst=2;
        }
        trigger_temp=(buffer[18]<<8)|buffer[19];
        //        if( trigger_temp!=trigger)
        //        {
        //            trigger=trigger_temp;
        //         }
        //eventnum=0;
        eventnum= trigger_temp-trigger;

        bordid=buffer[9];
        //bordid=bordid-16;
        channel=buffer[12]&(0x3f);

        pid=(bordid/8-1)*64+channel;
        getlength=buffer[13];

        printf("EventNum: %d \n",eventnum);
        fflush(stdout);

        //printf(" pid: %4d    Eventnum:%4d    packid:%4d    cpc:%4d    trgsrc:%4x    RTS:%4d\n", pid,eventnum,buffer[10],(buffer[14]<<8)|buffer[15],buffer[17]&(0x7),(buffer[20]<<8)|buffer[21]);


        pidstc[eventnum][pid].RTS=(buffer[20]<<8)|buffer[21];
        pidstc[eventnum][pid].TS=(buffer[22]<<40)|(buffer[23]<<32)|(buffer[24]<<24)|(buffer[25]<<16)|(buffer[26]<<8)|(buffer[27]);

        pidstc[eventnum][pid].bordnum=bordid;
        pidstc[eventnum][pid].triggerid=trigger;
        pidstc[eventnum][pid].channelnum=channel;
        pidstc[eventnum][pid].get_length=getlength*16;
        Timedata[pidstc[eventnum][pid].RTS]++;
        //printf(" pid:%d  Eventnum:%d  Relative time stamp:%d   Timedata[%d]:%d\n", pid,eventnum,pidstc[eventnum][pid].RTS,pidstc[eventnum][pid].RTS , Timedata[pidstc[eventnum][pid].RTS]);
        emit prompt(QString("The %5 Package--> pid:%1  Eventnum:%2  Relative time stamp:%3  bordid:%4;").arg(pid).arg(eventnum).arg(pidstc[eventnum][pid].RTS).arg(bordid).arg(packnum));
        fflush(stdout);


        a=29;
        bzero( pidstc[eventnum][pid].wavedata, 300);
        pidstc[eventnum][pid].MaxQ=0;
        for(int i=1;i<pidstc[eventnum][pid].get_length+1;i++)
        {
            pidstc[eventnum][pid].wavedata[i]=(buffer[a-1]<<8)|(buffer[a]);a=a+2;
            if(  pidstc[eventnum][pid].wavedata[i]>pidstc[eventnum][pid].MaxQ)
                pidstc[eventnum][pid].MaxQ= pidstc[eventnum][pid].wavedata[i];
            pidstc[eventnum][pid].Tcount=i;

        }


        bzero(buffer, BUFFER_SIZE);

    }
    alleventnum=eventnum;
    emit prompt(QString("\nAnalysing Over;\n"));
    fflush(stdout);

    fclose(fp);
    return 1;
}
