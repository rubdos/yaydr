#include <QtGui>

class ProjectManagerWindow : public QMainWindow
{
    Q_OBJECT
public:
    ProjectManagerWindow();
private:
    void _createMenus();
    void _createTrayIcon();
    void _createGrid();

    QMenu* _fileMenu;
    QSystemTrayIcon* _trayIcon;
    QMenu* _trayIconMenu;

    QScrollArea* _viewportScrollArea;
    QWidget* _scrollWidget;
    QVBoxLayout* _mainGrid;

private slots:
    void quit();
    void iconActivated(QSystemTrayIcon::ActivationReason);
};
