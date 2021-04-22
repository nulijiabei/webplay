#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QString>

class Util
{
public:
    Util();
public:
    static bool SavePID(QString);
};

#endif // UTIL_H
