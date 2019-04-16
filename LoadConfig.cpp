#include "LoadConfig.h"
#include <iostream>
#include <fstream>
#include<res.h>
using namespace std;

LoadConfig::LoadConfig()
{

}
LoadConfig::~LoadConfig()
{
}
//int LoadConfig::loadfile( std::string path, int*pidnum, int*lnum)
int LoadConfig::loadfile( std::string path)
{
    fstream file(path);
    string line,k[20];

    int p=0,q=0;

    if ( !file )
    {
        emit prompt("open file error");
        fflush(stdout);
        return -1;
    }
    emit prompt("open file successful;");
    while(!file.eof())
    {
        getline(file, line);
        int count=0;
        for(int i=0;i<20;i++)
        {
            k[i]=" ";
        }
        for (int i = 0; i < line.length(); i++) { //将字符串分割成字符串数组
            if (line[i] == ' ') {                 //以空格作为分隔符
                count++;
                continue;
            }
            k[count] += line[i];                //将分割好的字符串放到K数组里
        }
        if(count!=0)
        {
            lnum[q]=count+1;
            //     emit prompt(QString("\nlnum[%1]:%2; \n").arg(q).arg(lnum[q]));
            //            printf("***************lnum[%d]:%d\n ",q,lnum[q]);
            //            fflush(stdout);
            q++;

            for(int i=0;i<count+1;i++)
            {
                pidnum[p]=atoi(k[i].c_str());
                p++;
                //              printf("!!!!!!!!!!!lnum[0]:%d\n ",lnum[0]);
                //                 fflush(stdout);
            }
            //            printf("################lnum[0]:%d\n ",lnum[0]);
            //            fflush(stdout);
        }//如果ｉｆ没有把for框入的话pidnum就会越界１次，修改lnum的首个值为０
    }
    //    printf("@@@@@@@@@@@@lnum[0]:%d\n ",lnum[0]);
    //    fflush(stdout);

    file.close();

    emit prompt("config over! module num:");
    printf("config over! module num:\n");
    int cnt=0;

    for(int j=0;j<sizeof(lnum);j++)
    {
       if( lnum[j]==0)
           break;
        QString s="";
        for(int i=0;i<lnum[j];i++)
        {
            cout.setf(ios::left);
            cout.width(5);
            cout.fill(' ');
            cout<<pidnum[cnt];
            if(pidnum[cnt]>=10)
                s=s+QString("%1    ").arg(pidnum[cnt]);
            else
                s=s+QString("  %1    ").arg(pidnum[cnt]);
            //printf("% 10d",pidnum[cnt]);
            // cout<<pidnum[cnt]<<" ";
            cnt++;
        }
        //printf("\n");
        cout<<endl;
        emit prompt(s);
    }
    fflush(stdout);

    return 1;

}


