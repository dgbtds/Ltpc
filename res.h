#ifndef RES_H
#define RES_H
#include<iostream>
#include<QPoint>
using namespace std;
  extern int getlength;
  extern int alleventnum;
  extern  int Timedata[200];
   extern int pidnum[300];
   extern int lnum[20];

  
struct pckmessage{
     int triggerid;
    int Tcount;
    int MaxQ;
    int bordnum;
    int channelnum;
    int wavedata[300];
    int get_length;
    int TS;
   int RTS;

};

extern    pckmessage pidstc[1000][129];

struct pidcoordinate{
    int pid;
   QPoint pid_a;
   QPoint pid_b;
   QPoint pid_c;
   QPoint pid_d;

};

extern    pidcoordinate pidcod[128];

#endif // RES_H
