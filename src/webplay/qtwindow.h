#ifndef QTWINDOW_H
#define QTWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include "log.h"
#include "runtime.h"
#include "web.h"
#include "playobject.h"

class QtWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QtWindow(QWidget *parent = nullptr);
    void playWeb(QString);
private:
    QWidget *m_window = nullptr;
    Web *m_web = nullptr;
    QStackedLayout *m_layout = nullptr;
public slots:
    void SigReceivedMessage(QString key, QString value); // 接收
signals:
    void SigSendMessageToJS(QString key, QString value); // 发送
};

#endif // QTWINDOW_H
