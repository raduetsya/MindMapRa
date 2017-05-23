#include "mapcontextwidget.h"
#include "scrollareapan.h"

#include <QLabel>
#include <QGridLayout>

MapContextWidget::MapContextWidget(QWidget *parent)
    : QFrame(parent)
{
    // Scrollbars
    m_scrollArea = new ScrollAreaPan;
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Content window
    m_contentFrame = new QFrame(m_scrollArea);
    m_contentFrame->setBackgroundRole(QPalette::Dark);
    m_scrollArea->setWidget(m_contentFrame);

    // All windows to whole client area
    QGridLayout* layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_scrollArea);
    setLayout(layout);

    // Create test node
    QLabel* newNode = new QLabel(m_contentFrame);
    newNode->setText("Hello world! Hello world! Hello world! Hello world\nHello world! Hello world! Hello world! Hello world\nHello world! Hello world! Hello world! Hello world\n");
    newNode->move(0, 0);
    newNode->show();
    m_contentFrame->adjustSize();
}

