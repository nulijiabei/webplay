#include "configure.h"

Configure::Configure()
{

}

void Configure::initialize(QStringList arguments)
{
    int idx = -1;
    // --------------------------------------- //
    // 版本 ...
    idx = arguments.indexOf(QLatin1String("-version"));
    if (idx > 0) {
        LOGD("Application Version : %s", qPrintable(m_version));
        exit(0);
    }
    // --------------------------------------- //
    // 分辨率 ...
    idx = arguments.indexOf(QLatin1String("-R"));
    if (idx > 0) {
        QString res = arguments.at(idx + 1);
        QStringList rs = res.split(',');
        this->m_resolution = QRect(rs.at(0).toInt(),
                                   rs.at(1).toInt(),
                                   rs.at(2).toInt(),
                                   rs.at(3).toInt());
    }
    // --------------------------------------- //
    // 窗口化
    idx = arguments.indexOf(QLatin1String("-window"));
    if (idx > 0) {
        this->m_window = true;
    }
    // --------------------------------------- //
    // 隐藏光标
    idx = arguments.indexOf(QLatin1String("-no-cursor"));
    if (idx > 0) {
        this->m_no_cursor = true;
    }
    // --------------------------------------- //
    // 隐藏滚动条
    idx = arguments.indexOf(QLatin1String("-no-scrollbars"));
    if (idx > 0) {
        this->m_no_scrollbars = true;
    }
    // --------------------------------------- //
    // GPU
    idx = arguments.indexOf(QLatin1String("-gpu"));
    if (idx > 0) {
        this->m_chrome_gpu = true;
    }
    // --------------------------------------- //
    // GPU
    idx = arguments.indexOf(QLatin1String("-remote-debug"));
    if (idx > 0) {
        this->m_remote_debug = true;
    }
    // --------------------------------------- //
    // 网页 ...
    idx = arguments.indexOf(QLatin1String("-webpage"));
    if (idx > 0) {
        this->m_webpage = arguments.at(idx + 1);
    }
    // --------------------------------------- //
}
