#include "qtwindow.h"

QtWindow::QtWindow(QWidget *parent) : QMainWindow(parent)
{

    // Window ...
    m_window = new QWidget();
    m_window->setAutoFillBackground(true);
    QPalette palette = m_window->palette();
    palette.setColor(QPalette::Background, Qt::black);
    m_window->setPalette(palette);
    this->setCentralWidget(m_window);

    // Web ...
    m_web = new Web(parent);
    m_web->setGeometry(this->geometry());
#ifdef Q_OS_LINUX
    QWebChannel *wc = new QWebChannel(m_web->page());
    PlayObject *po = new PlayObject(this);
    wc->registerObject(QStringLiteral("pobj"), po); // 注册
    m_web->page()->setWebChannel(wc);
    connect(po, &PlayObject::SigReceivedMessage, this, &QtWindow::SigReceivedMessage);
    connect(this, &QtWindow::SigSendMessageToJS, po, &PlayObject::SigSendMessageToJS);
#endif

    // Layout ...
    m_layout = new QStackedLayout();
    m_layout->setStackingMode(QStackedLayout::StackAll);
    m_layout->insertWidget(0, m_web); // 后插入的在上面 ...
    m_window->setLayout(m_layout);

    // 加载网页 ...
    if (Runtime::m_configure->m_chrome_gpu) {
        // 加载 GPU 页面 ...
        m_web->play("chrome://gpu");
    } else {
        // 加载指定页面 ...
        m_web->play(Runtime::m_configure->m_webpage);
    }

}

void QtWindow::SigReceivedMessage(QString key, QString value)
{
    // 接收 JS 发来的指令 ...
    LOGD(">>> %s", QString("%1 %2").arg(key).arg(value).toStdString().c_str());
}
