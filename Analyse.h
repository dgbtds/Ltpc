#ifndef ANALYSE_H
#define ANALYSE_H

#include <QObject>

class Analyse : public QObject
{
    Q_OBJECT
public:
    ~Analyse();
    explicit Analyse(QObject *parent = nullptr);
   int analysedt(const char* file_name,int Event);
signals:
   void prompt(QString title);

public slots:
};

#endif // ANALYSE_H
