#include <QtGui>
#include <sqlite3.h>
#include "project/project.hpp"
#include "project/project_manager.hpp"
#include "project_manager/project_list_item_widget.hpp"

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
    void _createNewProjectDialog();

    void _fillGrid();

    void _AddProjectToGrid(yaydr::Project*);

    QMenu* _fileMenu;
    QSystemTrayIcon* _trayIcon;
    QMenu* _trayIconMenu;
    QToolBar* _toolbar;

    QScrollArea* _viewportScrollArea;
    QWidget* _scrollWidget;
    QVBoxLayout* _mainGrid;
    QSpacerItem* _stretchItem;

    NewProjectDialog* _newProjectDialog;

    yaydr::ProjectManager* _projectManager;

    std::vector<ProjectListItemWidget*> _projectWidgets;

    sqlite3* _databaseHandle; // Central database for yaydr

private slots:
    void quit();
    void newClicked();
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void onProjectDeleted(ProjectListItemWidget* p);
};
