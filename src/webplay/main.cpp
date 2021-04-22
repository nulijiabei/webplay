#include <QApplication>
#include <QTextCodec>
#include "log4qt/logger.h"
#include "log4qt/logmanager.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/propertyconfigurator.h"
#include "runtime.h"
#include "qtwindow.h"
#include "util.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // 运行时初始化 ...
    Runtime::initialize();
    // 配置初始化 ...
    Runtime::m_configure->initialize(a.arguments());

    // 设置 QTWEBENGINE_CHROMIUM_FLAGS 启动参数
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS",  QString("%1 %2 %3 %4 %5 %6")
            // 为通常为沙盒的所有进程类型禁用沙箱
            .arg("--no-sandbox")
            // 允许启发式确定何时应使用SkiaGPU后端绘制图层磁贴栅
            .arg("--enable-gpu-rasterization")
            // 在可用时启用本机GPU内存缓冲支持
            .arg("--enable-native-gpu-memory-buffers")
            // 允许将图像解码延迟到图像解码服务
            .arg("--enable-checker-imaging")
            // Qt5.12 版本显示 audio 标签 control 控件高度异常 ...
            // 参考 https://bugre可以ports.qt.io/browse/QTBUG-74484
            .arg("--disable-features=UseModernMediaControls")
            // 在与浏览器same相同的过程中运行渲染器和插件
            .arg("--single-process")
            .toLocal8Bit());

    // 开启 Chrome Debug ...
    if (Runtime::m_configure->m_remote_debug) {
        // 在 Chrome 浏览器调试前端页面
        qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "0.0.0.0:1112");
    }

    // 是否隐藏光标
    if (Runtime::m_configure->m_no_cursor) {
        // 空白光标
        QApplication::setOverrideCursor(Qt::BlankCursor);
    }

#ifdef Q_OS_WINDOWS // Windows 使用 ...
    Runtime::m_configure->m_home = QCoreApplication::applicationDirPath();
    LOGD("Log information is output to webplay.log ...");
#endif

#ifdef Q_OS_LINUX // Linux 使用 ...
    Runtime::m_configure->m_home = "/etc/webplay";
    LOGD("Log information is output to /dev/shm/webplay.log ...");
#endif

    // 初始化 LOG4QT
    Log4Qt::BasicConfigurator::configure();
    QString properties = QString("%1/log4qt.properties").arg(Runtime::m_configure->m_home);
    Log4Qt::PropertyConfigurator::configure(properties);
    Log4Qt::LogManager::setHandleQtMessages(true);
    /*
        log4j.rootLogger=DEBUG,A
        log4j.appender.A=org.apache.log4j.RollingFileAppender
        log4j.appender.A.File=/dev/shm/webplay.log
        log4j.appender.A.MaxFileSize=5120KB
        log4j.appender.A.MaxBackupIndex=1
        log4j.appender.A.AppendFile=true
        log4j.appender.A.layout=org.apache.log4j.PatternLayout
        log4j.appender.A.layout.ConversionPattern=%d{yyyy-MM-dd HH:mm:ss,SSS} [%t] [%c] [%p] - %m%n
    */

    // 版本 ...
    LOGD("%s", qPrintable(Runtime::m_configure->m_version));

    // 保存 PID
    Util::SavePID(QString("%1/webplay.pid").arg(Runtime::m_configure->m_home));

    // QtWindow 初始化 ...
    QtWindow window;
    // 是否窗口化 ...
    if (!Runtime::m_configure->m_window) {
        // 窗口置顶
        window.setWindowFlags(Qt::WindowStaysOnTopHint);
        // 隐藏标题栏
        window.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowTitleHint);
    }
    // 设置显示分辨率 ...
    window.setGeometry(Runtime::m_configure->m_resolution);
    // 显示 ...
    window.show();

    return a.exec();
}
