#include "playobject.h"

PlayObject::PlayObject(QObject *parent) : QObject(parent)
{

}

void PlayObject::SendMessageToQt(QString key, QString value) {
    emit SigReceivedMessage(key, value);
}
