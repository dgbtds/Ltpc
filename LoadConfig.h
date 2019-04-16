#ifndef LOADCONFIG_H
#define LOADCONFIG_H



#include <QObject>
class LoadConfig: public QObject
{
Q_OBJECT

public:
    LoadConfig();
    ~LoadConfig();

public slots:
    int loadfile( std::string path);
    // int loadfile( std::string path, int*pidnum, int*lnum);

signals:
    void prompt(QString title);



};

#endif // LOADCONFIG_H
