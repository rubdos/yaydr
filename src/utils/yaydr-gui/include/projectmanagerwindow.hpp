#include <QtGui>

class ProjectManagerWindow : public QMainWindow
{
    Q_OBJECT
public:
    ProjectManagerWindow();
private:
    void _createMenus();
    void _createTrayIcon();

    QTextEdit* _text;
    QMenu* _fileMenu;
    QSystemTrayIcon* _trayIcon;
    QMenu* _trayIconMenu;

private slots:
    void quit();
    void iconActivated(QSystemTrayIcon::ActivationReason);
};
