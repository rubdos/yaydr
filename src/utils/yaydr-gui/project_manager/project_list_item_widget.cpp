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

    this->_layout->addStretch(0);

    this->_buttonWidget = new QWidget();
    this->_buttonLayout = new QVBoxLayout(this->_buttonWidget);
    this->_layout->addWidget(this->_buttonWidget);

    // Now add the buttons
    {
        this->_deleteButton = new QPushButton(
                QIcon::fromTheme("edit-delete"), tr("Delete")
                );
        this->_deleteButton->setAutoFillBackground(true);
        this->_buttonLayout->addWidget(this->_deleteButton);
        connect(this->_deleteButton, SIGNAL(clicked()),
                this, SLOT(onDeleteButtonClick()));

        this->_editButton = new QPushButton(
                QIcon::fromTheme("document-open"), tr("Edit")
                );
        this->_editButton->setAutoFillBackground(true);
        this->_buttonLayout->addWidget(this->_editButton);
    }

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
}
void ProjectListItemWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void ProjectListItemWidget::onDeleteButtonClick()
{
    // Call the signal
    emit onProjectDelete(this);
    // Delete from SQL
    this->_project->Remove();
    delete this->_project; 
}
ProjectListItemWidget::~ProjectListItemWidget()
{
    delete this->_project;
}
