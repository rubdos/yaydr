#ifndef YAYDR_PLIW
#define YAYDR_PLIW

#include <QtGui>
#include <sqlite3.h>
#include "project/project.hpp"
#include "project_manager/edit_project_dialog.hpp"

/** Represents visually a yaydr::project.
 *
 */
class ProjectListItemWidget : public QWidget
{
    Q_OBJECT
    public:
        ProjectListItemWidget(yaydr::Project*);
        ~ProjectListItemWidget();

    signals:
        void onProjectDelete(ProjectListItemWidget* /* sender */);
    private slots:
        void onDeleteButtonClick();
        void onEditButtonClick();

    protected:
        void paintEvent(QPaintEvent*);
    private:
        yaydr::Project* _project;

        QLabel* _name;
        QLabel* _description;
        QVBoxLayout* _right;
        QWidget* _rightWidget;

        QVBoxLayout* _buttonLayout;
        QWidget* _buttonWidget;
        QPushButton* _deleteButton;
        QPushButton* _editButton;

        QLabel* _leftWidget;

        QHBoxLayout* _layout;

        EditProjectDialog* _epd;
};

#endif
