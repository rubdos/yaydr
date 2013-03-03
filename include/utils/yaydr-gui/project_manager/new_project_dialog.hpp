#ifndef YAYDR_NPD
#define YAYDR_NPD

#include <QtGui>
#include <sqlite3.h>
#include "project/project.hpp"

class NewProjectDialog : public QDialog
{
    Q_OBJECT
    public:
        NewProjectDialog(sqlite3* db);
        
        yaydr::Project* getNewProject();

    private:
        sqlite3* _databaseHandle;

        QVBoxLayout* _mainLayout;

        QFormLayout* _form;
        QWidget* _formWidget;

        /* Form items */
        QLineEdit* _txtName;
        QTextEdit* _txtDescription;

        QHBoxLayout* _buttonLayout;
        QWidget* _buttonLayoutWidget;
        
        QPushButton* _save;
        QPushButton* _cancel;

        yaydr::Project* _project;
    private slots:
        void onSaveClicked();
        void onCancelClicked();
};
#endif
