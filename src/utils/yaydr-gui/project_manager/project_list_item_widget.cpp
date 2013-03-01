#include <QtGui>
#include "project_manager/project_list_item_widget.hpp"

ProjectListItemWidget::ProjectListItemWidget(yaydr::Project* p)
{
    this->_project = p;

    this->_layout = new QHBoxLayout(this);

    QImage icon(":/images/yaydr.svg");
    this->_leftWidget = new QLabel();
    this->_leftWidget->setPixmap(QPixmap::fromImage(icon.scaledToHeight(75)));
    this->_layout->addWidget(this->_leftWidget);

    this->_rightWidget = new QWidget();
    this->_right = new QVBoxLayout(this->_rightWidget);
    this->_layout->addWidget(this->_rightWidget);

    this->_name = new QLabel(
            QString::fromStdString(this->_project->getName())
            );
    this->_name->setStyleSheet("font-weight:bold;");
    this->_right->addWidget(this->_name);

    this->_description = new QLabel(
            QString::fromStdString(this->_project->getDescription())
            );
    this->_right->addWidget(this->_description);

    this->setGeometry(0,0,300,100);
    this->setMaximumHeight(100);

    this->setStyleSheet("background-color:white;");

    this->_layout->addStretch(0);
}
void ProjectListItemWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
ProjectListItemWidget::~ProjectListItemWidget()
{
    delete this->_project;
}
