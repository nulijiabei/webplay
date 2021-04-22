#ifndef WEB_H
#define WEB_H

#include <QWidget>
#include "log.h"
#include "runtime.h"

#ifdef Q_OS_LINUX
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QUrl>
#include <QWebChannel>
#endif

#ifdef Q_OS_LINUX
class Web : public QWebEngineView
        #else
class Web : public QWidget
        #endif
{
    Q_OBJECT
public:
    explicit Web(QWidget *parent = nullptr);
    void play(QString);
};

#endif // WEB_H
