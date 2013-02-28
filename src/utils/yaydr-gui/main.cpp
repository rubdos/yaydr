#include <QtGui>

#include "project_manager/project_manager_window.hpp"

int main(int argc, char** argv)
{
    Q_INIT_RESOURCE(resources);
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
        QObject::tr("I couldn't detect any system tray "
            "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    ProjectManagerWindow window;
    window.show();
    
    return app.exec();
}
