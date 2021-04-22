#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QStringList>
#include <QString>
#include <QRect>
#include "log.h"

using namespace std;

class Configure
{
public:
    Configure();
public:
    void initialize(QStringList);
public:
    QString m_home; // 主目录
    QString m_version = "1.0.1";  // 版本
    QRect m_resolution = QRect(0, 0, 1920, 1080); // 分辨率
    bool m_window = false; // 窗口化
    bool m_no_cursor = false; // 隐藏光标
    bool m_no_scrollbars = false; // 隐藏滚动条
    bool m_chrome_gpu = false; // GPU
    bool m_remote_debug = false; // 远程调试
    QString m_webpage = "http://127.0.0.1:8080"; // 网页
};

#endif // CONFIGURE_H
