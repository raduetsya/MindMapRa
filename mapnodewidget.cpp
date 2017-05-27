#include "mapnodewidget.h"

#include <QLabel>
#include <QGridLayout>

MapNodeWidget::MapNodeWidget(QWidget* parent)
    : QFrame(parent)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setSizeIncrement(200, 100);

    QGridLayout* layout = new QGridLayout(this);

    QLabel* label = new QLabel;
    label->setText("Hello world!");
    layout->addWidget(label);

    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);
}

