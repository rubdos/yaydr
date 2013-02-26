#include "include/projectmanagerwindow.hpp"

ProjectManagerWindow::ProjectManagerWindow()
{
    this->_createMenus();
    this->_createTrayIcon();
    this->_createGrid();

    this->setWindowTitle(tr("Yaydr project manager"));
    this->setWindowIcon(QIcon(":/images/yaydr.svg"));
    this->resize(800,600);

    this->_projectManager = new yaydr::ProjectManager();
}
void ProjectManagerWindow::_createGrid()
{
    /* Initialize the scrollarea */
    this->_viewportScrollArea = new QScrollArea();
    this->_viewportScrollArea->setWidgetResizable(true);
    this->_viewportScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    /* Initialze the Vertical layout */
    this->_mainGrid = new QVBoxLayout(this->_viewportScrollArea);
    this->_mainGrid->setSizeConstraint(QLayout::SetNoConstraint);

    /* Initialize the scrollable widget */
    this->_scrollWidget = new QWidget();
    this->_scrollWidget->setLayout(this->_mainGrid);

    /* Add the widget to the scrollarea */
    this->_viewportScrollArea->setWidget(this->_scrollWidget);

    this->setCentralWidget(this->_viewportScrollArea);
}
void ProjectManagerWindow::_createMenus()
{
    this->_fileMenu = menuBar()->addMenu( tr("&File") );
    connect(
            this->_fileMenu->addAction( tr("&Exit") ), SIGNAL(triggered()),
            this, SLOT(quit())
            );
}
void ProjectManagerWindow::_createTrayIcon()
{
    this->_trayIcon = new QSystemTrayIcon(this);
    this->_trayIcon->setIcon(QIcon(":/images/yaydr.svg"));
    
    connect(this->_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                         this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    
    
    this->_trayIconMenu = new QMenu(this);

    connect(this->_trayIconMenu->addAction(tr("&Exit")), SIGNAL(triggered()),
            this, SLOT(quit()));
    
    this->_trayIcon->setContextMenu(this->_trayIconMenu);
    this->_trayIcon->show();
}
void ProjectManagerWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            {
                if(this->isVisible())
                {
                    this->hide();
                }
                else
                {
                    this->show();
                }
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
}