#include "mapcontextwidget.h"
#include "scrollareapan.h"
#include "mapnodewidget.h"
#include "mapnode.h"
#include "mapcontext.h"

#include <QLabel>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

MapContextWidget::MapContextWidget(QWidget *parent, MindMapRa::MapContext* model)
    : QFrame(parent)
    , m_nodeScene(new QGraphicsScene)
    , m_model(model)
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

    if (m_model == NULL)
    {
        m_model = new MindMapRa::MapContext;
        m_model->AddChildAtCursor();
    }

    // fill nodes
    {
        QMap<MindMapRa::MapNode*, QVector<MindMapRa::MapNode*> > nodesMap = m_model->AllNodes();
        QMapIterator<MindMapRa::MapNode*, QVector<MindMapRa::MapNode*> > it(nodesMap);
        while(it.hasNext())
        {
            it.next();
            MapNodeWidget* newWidget = new MapNodeWidget(NULL);
            newWidget->SetText("123");
            m_nodeScene->addWidget(newWidget);
        }
    }
}

void MapContextWidget::AddNode()
{
}

