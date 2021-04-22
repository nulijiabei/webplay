#include "util.h"

Util::Util()
{

}

bool Util::SavePID(QString _f)
{
    QFile file(_f);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);
    out << getpid();
    out.flush();
    file.flush();
    file.close();
    return true;
}
