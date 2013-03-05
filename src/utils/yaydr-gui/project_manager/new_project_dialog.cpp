#include "project_manager/new_project_dialog.hpp"
#include "project/project.hpp"

NewProjectDialog::NewProjectDialog(QWidget* parent, sqlite3* db)
    :QDialog(parent)
{
    this->_databaseHandle = db;

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
    this->setWindowTitle(tr("Add a new project to Yaydr"));

    // Create layout
    this->_mainLayout = new QVBoxLayout(this);

    // Push the form
    this->_formWidget = new QWidget();
    this->_form = new QFormLayout(this->_formWidget);
    this->_txtName = new QLineEdit();
    this->_form->addRow( tr("Project name"), this->_txtName );
    this->_txtDescription = new QTextEdit();
    this->_form->addRow( tr("Project description"), this->_txtDescription );

    this->_mainLayout->addWidget(this->_formWidget);

    // Push the buttons
    this->_buttonLayoutWidget = new QWidget();
    this->_buttonLayout = new QHBoxLayout(this->_buttonLayoutWidget);
    this->_mainLayout->addWidget(this->_buttonLayoutWidget);

    this->_save = new QPushButton(tr("&Save"));
    this->_save->setDefault(true);
    connect(this->_save, SIGNAL(clicked()),
            this, SLOT(onSaveClicked())
            );
    connect(this->_save, SIGNAL(clicked()),
            this, SLOT(accept()));
    this->_buttonLayout->addWidget(this->_save);
    
    this->_cancel = new QPushButton(tr("&Cancel"));
    connect(this->_cancel, SIGNAL(clicked()),
            this, SLOT(onCancelClicked())
            );
    connect(this->_cancel, SIGNAL(clicked()),
            this, SLOT(reject()));
    this->_buttonLayout->addWidget(this->_cancel);
}
void NewProjectDialog::onSaveClicked()
{
    // Save to project && return.
    this->_project = new yaydr::Project(this->_databaseHandle, 
            this->_txtName->text().toStdString(), 
            this->_txtDescription->toPlainText().toStdString()); // Is autoadded to db
}
yaydr::Project* NewProjectDialog::getNewProject()
{
    return this->_project;
}
void NewProjectDialog::onCancelClicked()
{
    // Reject changes and return.
}
