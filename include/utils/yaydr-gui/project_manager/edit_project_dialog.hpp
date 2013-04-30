#ifndef YAYDR_EPD
#define YAYDR_EPD

#include <QtGui>
#include <sqlite3.h>
#include "project/project.hpp"

class EditProjectDialog : public QDialog
{
    Q_OBJECT
    public:
        EditProjectDialog(QWidget* parent, yaydr::Project*);

        QVBoxLayout* _mainLayout;

    private:
        yaydr::Project* _project;
        void _refreshGrid();
    private slots:
        void selectDirectory();
        void selectFile();
};
#endif
