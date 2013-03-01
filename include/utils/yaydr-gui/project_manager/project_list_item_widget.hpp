#ifndef YAYDR_PLIW
#define YAYDR_PLIW

#include <QtGui>
#include <sqlite3.h>
#include "project/project.hpp"

/** Represents visually a yaydr::project.
 *
 */
class ProjectListItemWidget : public QWidget
{
    Q_OBJECT
public:
    ProjectListItemWidget(yaydr::Project*);
    ~ProjectListItemWidget();
protected:
    void paintEvent(QPaintEvent*);
private:
    yaydr::Project* _project;

    QLabel* _name;
    QLabel* _description;
    QVBoxLayout* _right;
    QWidget* _rightWidget;

    QLabel* _leftWidget;

    QHBoxLayout* _layout;

private slots:
};

#endif
