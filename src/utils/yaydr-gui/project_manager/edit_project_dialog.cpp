#include <iostream>

#include "project_manager/edit_project_dialog.hpp"
#include "project/image.hpp"

EditProjectDialog::EditProjectDialog(QWidget* parent, yaydr::Project* p)
    :QDialog(parent)
{
    this->_project = p;
    
    this->setWindowTitle(
            tr(
                ("Yaydr project: \"" + _project->getName() + "\"").c_str())
            );

    this->_mainLayout = new QVBoxLayout();
    setLayout(this->_mainLayout);
    resize(600, 400);

    QMenuBar* mb = new QMenuBar();
    QMenu* proj = mb->addMenu( tr("Project" ) );
    QAction* a; 

    a = proj->addAction(tr("Add xml file"));
    
    connect(a, SIGNAL(triggered()),
            this, SLOT(selectFile()));
    a = proj->addAction(tr("Add directory"));
    connect(a, SIGNAL(triggered()),
            this, SLOT(selectDirectory()));

    this->_mainLayout->setMenuBar(mb);
}
void EditProjectDialog::selectFile()
{
    std::string file = QFileDialog::getOpenFileName(this,
            tr("Open XML scene"), "", 
            tr("Yafaray scenes (*.xml)")).toStdString();
    yaydr::Image* img = new yaydr::Image(file);
    
    this->_refreshGrid();
}
void EditProjectDialog::_refreshGrid()
{
    // STUB
    delete this->_grid;
    this->_grid = new QGridLayout();
    
}
void EditProjectDialog::selectDirectory()
{

}
