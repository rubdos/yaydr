#include <QtGui>
#include <sqlite3.h>
#include "project/project_manager.hpp"

class ProjectManagerWindow : public QMainWindow
{
    Q_OBJECT
public:
    ProjectManagerWindow();
    ~ProjectManagerWindow();
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

    yaydr::ProjectManager* _projectManager;

    sqlite3* _databaseHandle; // Central database for yaydr

private slots:
    void quit();
    void iconActivated(QSystemTrayIcon::ActivationReason);
};
