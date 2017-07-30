#include "mapcontextwidget.h"
#include "mapnodewidget.h"
#include "mapnode.h"
#include "mapcontext.h"
#include "mapcursor.h"
#include "maplayout.h"

#include <QLabel>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPathItem>

MapContextWidget::MapContextWidget(QWidget *parent, MindMapRa::MapContext* model)
    : QFrame(parent)
    , m_nodeScene(new QGraphicsScene)
    , m_context(model)
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

    if (m_context == NULL)
        m_context = new MindMapRa::MapContext;

    connect(m_context, SIGNAL(OnNodeAdded(MindMapRa::MapNode*,MindMapRa::MapContext*)),
            this,      SLOT(OnNodeAdded(MindMapRa::MapNode*,MindMapRa::MapContext*)));
    connect(m_context, SIGNAL(OnNodeDeleted(MindMapRa::MapNode*,MindMapRa::MapContext*)),
            this,      SLOT(OnNodeDeleted(MindMapRa::MapNode*,MindMapRa::MapContext*)));

    const QVector<MindMapRa::MapNode*> nodes = m_context->GetNodes();
    Q_FOREACH(MindMapRa::MapNode* node, nodes)
        OnNodeAdded(node, m_context);

    m_cursor = new MindMapRa::MapCursor(m_context);
    m_nodeWidgets[ m_cursor->GetNode() ]->SetFocusNode(true);
}

void MapContextWidget::OnNodeAdded(MindMapRa::MapNode* node, MindMapRa::MapContext* caller)
{
    // create node
    {
        MapNodeWidget* newWidget = new MapNodeWidget(NULL);
        newWidget->SetText( node->GetText() );
        // newWidget->move(  );

        connect(newWidget,  SIGNAL(OnChangeFocusUserRequest(MapNodeWidget*)),
                this,       SLOT(OnChangeFocusUserRequest(MapNodeWidget*)));
        connect(newWidget,  SIGNAL(OnCursorMoveRequested(bool,bool,bool,bool)),
                this,       SLOT(OnCursorMoveRequested(bool,bool,bool,bool)));
        connect(newWidget,  SIGNAL(OnCursorCreateNodeRequested()),
                this,       SLOT(OnCursorCreateNodeRequested()));
        connect(newWidget,  SIGNAL(OnCursorRemoveNodeRequested()),
                this,       SLOT(OnCursorRemoveNodeRequested()));

        m_nodeScene->addWidget(newWidget);
        m_nodeWidgets[node] = newWidget;
    }

    // create layout element
    {
        MindMapRa::MapNode* parent = caller->GetNodeParent(node);
        MapNodeWidget* parentWidget = (parent ? m_nodeWidgets[parent] : NULL);
        m_layout->Add(m_nodeWidgets[node], parentWidget);
        m_layout->FixAllPositions();
    }

}

void MapContextWidget::OnNodeDeleted(MindMapRa::MapNode* node, MindMapRa::MapContext*)
{
    if (m_nodeWidgets.count(node) > 0)
    {
        MapNodeWidget* widget = m_nodeWidgets[node];

        m_layout->Remove( widget );

        if (m_pathWidgets.contains( widget ))
            delete m_pathWidgets[widget];
        m_pathWidgets.remove(widget);

        delete widget;
        m_nodeWidgets.remove(node);
    }

    m_layout->FixAllPositions();
}

void MapContextWidget::OnChangeFocusUserRequest(MapNodeWidget *widget)
{
    MindMapRa::MapNode* oldNode = m_cursor->GetNode();

    QMapIterator<MindMapRa::MapNode*, MapNodeWidget*> it(m_nodeWidgets);
    while(it.hasNext())
    {
        it.next();
        if (it.value() == widget)
        {
            MindMapRa::MapNode* newNode = it.key();
            m_cursor->SetNode(newNode);
            m_nodeWidgets[ oldNode ]->SetFocusNode(false);
            m_nodeWidgets[ newNode ]->SetFocusNode(true);
            break;
        }
    }
}

void MapContextWidget::OnCursorMoveRequested(bool isUp, bool isDown, bool isLeft, bool isRight)
{
    MindMapRa::MapNode* oldNode = m_cursor->GetNode();

    if (isUp)
        m_cursor->MoveCursor(MindMapRa::MapCursor::CD_Up);
    if (isDown)
        m_cursor->MoveCursor(MindMapRa::MapCursor::CD_Down);
    if (isLeft)
        m_cursor->MoveCursor(MindMapRa::MapCursor::CD_Left);
    if (isRight)
        m_cursor->MoveCursor(MindMapRa::MapCursor::CD_Right);

    MindMapRa::MapNode* newNode = m_cursor->GetNode();

    if (oldNode != newNode)
    {
        m_nodeWidgets[ oldNode ]->SetFocusNode(false);
        m_nodeWidgets[ newNode ]->SetFocusNode(true);
    }
}

void MapContextWidget::OnCursorCreateNodeRequested()
{
    MindMapRa::MapNode* oldNode = m_cursor->GetNode();
    MindMapRa::MapNode* newNode = m_cursor->CreateChildNode();
    m_nodeWidgets[ oldNode ]->SetFocusNode(false);
    m_nodeWidgets[ newNode ]->SetFocusNode(true);
    m_cursor->SetNode(newNode);
}

void MapContextWidget::OnCursorRemoveNodeRequested()
{
    m_cursor->DeleteCurrentNode();
    MindMapRa::MapNode* newNode = m_cursor->GetNode();
    m_nodeWidgets[ newNode ]->SetFocusNode(true);
}

void MapContextWidget::OnNodePosition(ILayoutElement *node, QPointF pos)
{
    MapNodeWidget* widget = dynamic_cast<MapNodeWidget*>(node);
    widget->move(pos.x(), pos.y());

    MindMapRa::MapNode* child = NULL;
    QMapIterator<MindMapRa::MapNode*, MapNodeWidget*> itChild(m_nodeWidgets);
    while (itChild.hasNext())
    {
        itChild.next();
        if (itChild.value() == widget)
            child = itChild.key();
    }

    MindMapRa::MapNode* parent = m_context->GetNodeParent(child);

    if (!parent)
        return;

    if (m_pathWidgets.contains(widget))
        m_pathWidgets[widget]->setPath(GenPath(parent, child));
    else
        m_pathWidgets.insert(m_nodeWidgets[child], m_nodeScene->addPath(GenPath(parent, child)));
}

QPainterPath MapContextWidget::GenPath(MindMapRa::MapNode* parent, MindMapRa::MapNode* child)
{
    const float curvePointsOffset = 20.f;

    QRectF parentRect = m_layout->GetPos( m_nodeWidgets[parent] );
    QRectF childRect = m_layout->GetPos( m_nodeWidgets[child] );

    const QPointF from_1 = parentRect.topRight() + QPointF(0, parentRect.height() / 2);
    const QPointF from_2 = from_1 + QPointF(curvePointsOffset, 0.f);

    const QPointF to_1 = childRect.topLeft() + QPointF(0, childRect.height() / 2);
    const QPointF to_2 = to_1 - QPointF(curvePointsOffset, 0.f);

    QPainterPath path;
    path.moveTo(from_1);
    path.cubicTo(from_2, to_2, to_1);
    return path;
}
