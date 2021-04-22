#include "web.h"

#ifdef Q_OS_LINUX
Web::Web(QWidget *parent) : QWebEngineView(parent) {
    // 禁止播放媒体内容，直到用户与页面互动为止。
    this->settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
    // 是否隐藏滚动条 ...
    if (Runtime::m_configure->m_no_scrollbars) {
        // 设置 WebEngine 隐藏滚动条
        this->settings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);
    }
#else
Web::Web(QWidget *parent) : QWidget(parent) {
#endif
}

void Web::play(QString url) {
#ifdef Q_OS_LINUX
    // 加载指定页面
    this->load(QUrl(url));
#else
    LOGD("Not Supported ...");
#endif
}
