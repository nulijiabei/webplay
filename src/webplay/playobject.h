#ifndef PLAYOBJECT_H
#define PLAYOBJECT_H

#include <QObject>

class PlayObject : public QObject
{
    Q_OBJECT
public:
    PlayObject(QObject *parent = nullptr);
    Q_INVOKABLE void SendMessageToQt(QString key, QString value);
signals:
    void SigReceivedMessage(QString key, QString value);
    void SigSendMessageToJS(QString key, QString value);
};

#endif // PLAYOBJECT_H
