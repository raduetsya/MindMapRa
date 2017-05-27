#include "mapcontextwidget.h"
#include "scrollareapan.h"
#include "mapnodewidget.h"

#include <QLabel>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

MapContextWidget::MapContextWidget(QWidget *parent)
    : QFrame(parent)
    , m_nodeScene(new QGraphicsScene)
{
    m_nodeView = new QGraphicsView(m_nodeScene);
    m_nodeView->setDragMode(QGraphicsView::ScrollHandDrag);
    m_nodeView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    m_nodeView->setInteractive(true);

    // Layout: maximize to parent window
    QGridLayout* layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_nodeView);
    setLayout(layout);

    AddNode();
}

void MapContextWidget::AddNode()
{
    MapNodeWidget* newWidget = new MapNodeWidget(NULL);
    m_nodeScene->addWidget(newWidget);
}

