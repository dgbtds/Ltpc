#include "create.h"
#include "Analyse.h"
#include<stdio.h>    // printf
#include<stdlib.h>    // exit
#include<string.h>    // bzero
#include <iostream>
#include <res.h>

#define file_name "creat_LTPC.dat"
#define BUFFER_SIZE 5000

using namespace std;
Create::Create()
{

}
void Create::creatdata()
{
   system("rm creat_LTPC.dat");
    FILE *fp= fopen(file_name, "ab+");
    if(NULL == fp)
    {
        printf("File:%s Not Found\n", file_name);
    }
    else
    {
        printf("File:%s has been open\n", file_name);
    }

    int offset=0;char channel;
    unsigned char buffer[BUFFER_SIZE];

    bzero(buffer, BUFFER_SIZE);
    unsigned char rouse[BUFFER_SIZE];

    bzero(rouse, BUFFER_SIZE);
    for(int i=0;i<=128;i++)
    {
        buffer[0]=0x1e,buffer[1]=0xad,buffer[2]=0xc0,buffer[3]=0xde;//header

        buffer[4]=0x00,buffer[5]=0xdb,buffer[6]=0x00,buffer[7]=0x4c;//PER

        buffer[8]=0x00;buffer[9]=i/32+16;buffer[10]=0x00;buffer[11]=0x30;//boardid

        channel=(i%32);
//        printf("channel: %d",channel);
//          fflush(stdout);
      buffer[12]=((0x3f)&(channel))|(0xc0);buffer[13]=buffer[7]/4-1;buffer[14]=0x00;buffer[15]=0x00;//channel

       buffer[16]=0x00,buffer[17]=0x00,buffer[18]=0x00,buffer[19]=0x00;//reserve

         buffer[20]=0x00,buffer[21]=0x00,buffer[22]=0x00,buffer[23]=0x00;//teime stamp1

        buffer[24]=0x00,buffer[25]=0x00,buffer[26]=0x00,buffer[27]=0x00;//teime stamp2
        for(int s=0;s<8*buffer[13];s++)
        {
              buffer[28+s*4]=0x01,buffer[29+s*4]=0x6e,buffer[30+s*4]=0x01,buffer[31+s*4]=0x68;//wavedata1,2
        }

if( (i==4)|(i==14)|(i==25) |(i==36) |(i==47) |(i==58)|(i==69) |(i==80) |(i==91) |(i==102)|(i==113) |(i==123)     )
    buffer[68]=0x01,buffer[69]=0x6e,buffer[70]=0x01,buffer[71]=0x68;

  buffer[buffer[7]*8-4]=0x5a,buffer[buffer[7]*8-3]=0x5a,buffer[buffer[7]*8-2]=0x5a,buffer[buffer[7]*8-1]=0x5a;//trailer

        fwrite(buffer, sizeof(char),8*buffer[7] , fp);
        bzero(buffer, BUFFER_SIZE);
        offset=0;
    }
    fclose(fp);
    printf("creat data succeed!");
    fflush(stdout);
}
