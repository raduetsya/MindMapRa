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
        m_model = new MindMapRa::MapContext;

    m_model->AddEventListener(this);
    m_model->PresentEntireMapAsEvents(this);
}

void MapContextWidget::OnNodeAdded(MindMapRa::MapNode* node, MindMapRa::MapNode* parent)
{
    // create node
    {
        MapNodeWidget* newWidget = new MapNodeWidget(NULL);
        newWidget->SetText( node->GetText() );
        newWidget->move( node->GetPos().toPoint() );
        m_nodeScene->addWidget(newWidget);
        m_nodeWidgets[node] = newWidget;
    }

    // connect to parent
    if (parent)
    {
        const float curvePointsOffset = 20.f;

        const QPointF from_1 = parent->GetPos() + QPointF(parent->GetWidth(), 0.f);
        const QPointF from_2 = from_1 + QPointF(curvePointsOffset, 0.f);

        const QPointF to_1 = node->GetPos();
        const QPointF to_2 = to_1 - QPointF(curvePointsOffset, 0.f);

        QPainterPath path;
        path.moveTo(from_1);
        path.cubicTo(from_2, to_2, to_1);
        m_nodeScene->addPath(path);
    }
}

void MapContextWidget::OnNodeDeleted(MindMapRa::MapNode *node)
{
    if (m_nodeWidgets.count(node) > 0)
    {
        delete m_nodeWidgets[node];
        m_nodeWidgets.remove(node);
    }
}

void MapContextWidget::OnNodeFocus(MindMapRa::MapNode *node, bool isSetFocus)
{
    // todo: impl
}

void MapContextWidget::OnNodePosition(MindMapRa::MapNode *node, QPointF oldPos, QPointF newPos)
{
    m_nodeWidgets[node]->move( newPos.toPoint() );
}

