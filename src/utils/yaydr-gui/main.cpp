#include <QtGui>
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
        QObject::tr("I couldn't detect any system tray "
            "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    QWidget window;
    window.show();
    
    return app.exec();
}
