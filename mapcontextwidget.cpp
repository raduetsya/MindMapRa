#include "mapcontextwidget.h"
#include "scrollareapan.h"
#include "mapnodewidget.h"
#include "mapnode.h"
#include "mapcontext.h"
#include "maplayout.h"

#include <QLabel>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPathItem>
#include <QDebug>

MapContextWidget::MapContextWidget(QWidget *parent, MindMapRa::MapContext* model)
    : QFrame(parent)
    , m_nodeScene(new QGraphicsScene)
    , m_model(model)
    , m_layout(new MapLayout)
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

    connect(m_layout, SIGNAL(OnElementPosition(ILayoutElement*,QPointF)),
            this,     SLOT(OnNodePosition(ILayoutElement*,QPointF)));

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
        // newWidget->move(  );

        connect(newWidget,  SIGNAL(OnChangeFocusUserRequest(MapNodeWidget*)),
                this,       SLOT(OnChangeFocusUserRequest(MapNodeWidget*)));

        m_nodeScene->addWidget(newWidget);
        m_nodeWidgets[node] = newWidget;
    }

    // create layout element
    {
        MapNodeWidget* parentWidget = (parent ? m_nodeWidgets[parent] : NULL);
        m_layout->Add(m_nodeWidgets[node], parentWidget);
        m_layout->FixAllPositions();
    }

    // connect to parent
    if (parent)
    {
        m_pathWidgets.insert(m_nodeWidgets[node], m_nodeScene->addPath(GenPath(parent, node)));
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
    m_nodeWidgets[node]->SetFocusNode(isSetFocus);
}

void MapContextWidget::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_F2)
    {
        MindMapRa::MapNode* newNode = m_model->AddChildAtCursor();
        m_nodeWidgets[ newNode ]->EnableTextEdit(true);
    }
    if (ev->key() == Qt::Key_F3)
        m_nodeWidgets[ m_model->GetCurrenNode() ]->EnableTextEdit(true);
}

void MapContextWidget::OnChangeFocusUserRequest(MapNodeWidget *widget)
{
    QMapIterator<MindMapRa::MapNode*, MapNodeWidget*> it(m_nodeWidgets);
    while(it.hasNext())
    {
        it.next();
        if (it.value() == widget)
        {
            m_model->SelectNode(it.key());
            break;
        }
    }
}

void MapContextWidget::OnNodePosition(ILayoutElement *node, QPointF pos)
{
    MapNodeWidget* widget = dynamic_cast<MapNodeWidget*>(node);
    widget->move(pos.x(), pos.y());
}

QPainterPath MapContextWidget::GenPath(MindMapRa::MapNode* parent, MindMapRa::MapNode* child)
{
    const float curvePointsOffset = 5.f;

    QRectF parentRect = m_layout->GetPos( m_nodeWidgets[parent] );
    QRectF childRect = m_layout->GetPos( m_nodeWidgets[child] );

    const QPointF from_1 = parentRect.topRight() + QPointF(0, parentRect.height() / 2);
    const QPointF from_2 = from_1 + QPointF(curvePointsOffset, 0.f);

    const QPointF to_1 = childRect.topLeft() + QPointF(0, childRect.height() / 2);
    const QPointF to_2 = to_1 - QPointF(curvePointsOffset, 0.f);

    qDebug() << from_1 << from_2 << to_1 << to_2;

    QPainterPath path;
    path.moveTo(from_1);
    path.cubicTo(from_2, to_2, to_1);
    return path;
}
