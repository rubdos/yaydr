#include <iostream>

#include "project_manager/project_manager_window.hpp"

ProjectManagerWindow::ProjectManagerWindow()
{
    int rc = sqlite3_open("yaydr.sqlite3", &this->_databaseHandle); 
    
    this->_createMenus();
    this->_createTrayIcon();
    this->_createGrid();
    this->_createNewProjectDialog();

    this->setWindowTitle(tr("Yaydr project manager"));
    this->setWindowIcon(QIcon(":/images/yaydr.svg"));
    this->resize(800,600);

    if( rc )
    {
        std::cerr << "Error" << std::endl;
    }
    // FIXME drop in a common directory. Find a good way to do this

    this->_projectManager = new yaydr::ProjectManager(this->_databaseHandle);
    this->_fillGrid();
}
void ProjectManagerWindow::_createGrid()
{
    /* Initialize stretch item */
    this->_stretchItem = new QSpacerItem(0, 20,
            QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
    /* Initialize the scrollarea */
    this->_viewportScrollArea = new QScrollArea();
    this->_viewportScrollArea->setWidgetResizable(true);
    this->_viewportScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    /* Initialze the Vertical layout */
    this->_mainGrid = new QVBoxLayout(this->_viewportScrollArea);
    this->_mainGrid->setSizeConstraint(QLayout::SetNoConstraint);
    this->_mainGrid->setSpacing(3);

    /* Initialize the scrollable widget */
    this->_scrollWidget = new QWidget();
    this->_scrollWidget->setLayout(this->_mainGrid);

    /* Add the widget to the scrollarea */
    this->_viewportScrollArea->setWidget(this->_scrollWidget);

    this->setCentralWidget(this->_viewportScrollArea);
}
void ProjectManagerWindow::_fillGrid()
{
    yaydr::ProjectList* ps = this->_projectManager->GetProjectList();
    for(yaydr::ProjectList::iterator pit = ps->begin();
            pit != ps->end();
            ++pit)
    {
        this->_AddProjectToGrid(*pit);
    }
    this->_mainGrid->addSpacerItem(this->_stretchItem); // make it nice and clean
}
void ProjectManagerWindow::_createMenus()
{
    // Create the main menu
    this->_fileMenu = menuBar()->addMenu( tr("&File") );

    /* Then create some actions */
    // New action
    QAction* aNew = new QAction(QIcon::fromTheme("document-new"), 
            tr("&New project"), this);
    connect(aNew, SIGNAL(triggered()), 
            this, SLOT(newClicked()));
    aNew->setShortcut(QKeySequence(tr("Ctrl+N")));
    this->_fileMenu->addAction(aNew);

    // Exit action
    QAction* aExit = new QAction(QIcon::fromTheme("application-exit"), 
            tr("&Exit"), this);
    connect(aExit, SIGNAL(triggered()),
            this, SLOT(quit()));
    aExit->setShortcut(QKeySequence(tr("Ctrl+Q")));
    this->_fileMenu->addAction(aExit);

    // Now toolbar
    this->_toolbar = new QToolBar("Yaydr Tools");
    this->_toolbar->addAction(aNew);

    this->addToolBar(Qt::LeftToolBarArea, this->_toolbar);
}
void ProjectManagerWindow::_createTrayIcon()
{
    this->_trayIcon = new QSystemTrayIcon(this);
    this->_trayIcon->setIcon(QIcon(":/images/yaydr.svg"));
    
    connect(this->_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                         this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    
    
    this->_trayIconMenu = new QMenu(this);

    connect(this->_trayIconMenu->addAction(tr("&Show/hide")), SIGNAL(triggered()),
            this, SLOT(_ShowToggle()));
    connect(this->_trayIconMenu->addAction(tr("&Exit")), SIGNAL(triggered()),
            this, SLOT(quit()));
    
    this->_trayIcon->setContextMenu(this->_trayIconMenu);
    this->_trayIcon->show();
}
void ProjectManagerWindow::_createNewProjectDialog()
{
    this->_newProjectDialog = new NewProjectDialog(this, this->_databaseHandle);
}
void ProjectManagerWindow::newClicked()
{
    // Open the new project dialog
    if(this->_newProjectDialog->exec())
    {
        // First remove stretch
        this->_mainGrid->removeItem(this->_stretchItem);

        this->_AddProjectToGrid(this->_newProjectDialog->getNewProject());
        
        // Readd spacer
        this->_mainGrid->addSpacerItem(this->_stretchItem);
        
        // Recreate the dialog
        delete this->_newProjectDialog;
        this->_createNewProjectDialog();
    }
}
void ProjectManagerWindow::_AddProjectToGrid(yaydr::Project* p)
{
    // Add to list
    ProjectListItemWidget* pliw = 
        new ProjectListItemWidget(p);
    this->_projectWidgets.push_back(pliw);
    this->_mainGrid->addWidget(pliw);

    connect(pliw, SIGNAL(onProjectDelete(ProjectListItemWidget*)),
            this, SLOT(onProjectDeleted(ProjectListItemWidget*)));
}
void ProjectManagerWindow::onProjectDeleted(ProjectListItemWidget* pliw)
{
    for(std::vector<ProjectListItemWidget*>::iterator 
            pliwit = this->_projectWidgets.begin();
            pliwit != this->_projectWidgets.end();
            ++pliwit)
    {
        if(*pliwit == pliw)
        {
            this->_projectWidgets.erase(pliwit);
            break;
        }
    }
    this->_mainGrid->removeWidget(pliw);
    pliw->deleteLater();
}
void ProjectManagerWindow::_ShowToggle()
{
    if(this->isVisible())
    {
        this->hide();
    }
    else
    {
        this->show();
    }
}
void ProjectManagerWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            {
                this->_ShowToggle();
                break;
            }
        default:
        break;
    }
}
void ProjectManagerWindow::quit()
{
    qApp->exit();
}
ProjectManagerWindow::~ProjectManagerWindow()
{
    delete this->_projectManager;
    sqlite3_close(this->_databaseHandle);
}
