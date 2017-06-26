#include "mapcontext.h"
#include "nodestorage.h"
#include "mapnode.h"
#include "maplayout.h"

#include <QMap>
#include <QPointF>

namespace MindMapRa {

MapContext::MapContext(QObject *parent)
: QObject(parent)
, m_nodeStorage(new NodeStorage(this))
, m_layout(new MapLayout)
, m_curNode(NULL)
{
    connect(m_nodeStorage, SIGNAL(OnNodeAdded(MapNode*,MapNode*)),
            m_layout,      SLOT(OnNodeAdded(MapNode*,MapNode*)));
    connect(m_nodeStorage, SIGNAL(OnNodeDeleted(MapNode*)),
            m_layout,      SLOT(OnNodeDeleted(MapNode*)));
    connect(m_layout, SIGNAL(OnNodePosition(MapNode*,QPointF,QPointF)),
            this,     SLOT(InternalOnNodePosition(MapNode*,QPointF,QPointF)));

    m_curNode = new MapNode(tr("Press Space to edit"), QPointF(0, 0));
    m_nodeStorage->AddNode(m_curNode, NULL);
}

MapNode* MapContext::AddChildAtCursor() {
    if (!m_curNode)
        return NULL;

    MapNode* oldNode = m_curNode;
    m_curNode = new MapNode("", QPointF(0, 0));
    m_nodeStorage->AddNode(m_curNode, oldNode);

    Q_FOREACH(IMapContextClientEventListener* evListener, m_eventListeners)
    {
        evListener->OnNodeAdded(m_curNode, oldNode);
        evListener->OnNodeFocus(oldNode, false);
        evListener->OnNodeFocus(m_curNode, true);
    }

    m_layout->FixAllPositions();

    return m_curNode;
}

void MapContext::MoveCursor(int hor, int ver) {
    if (!m_curNode)
        return;

    Q_UNUSED(hor);
    Q_UNUSED(ver);
}

void MapContext::DeleteNodeAtCursor() {
    if (!m_curNode)
        return;
}

void MapContext::SelectNode(MapNode *node) {
    Q_ASSERT(node != NULL);

    MapNode* oldNode = node;
    m_curNode = node;

    Q_FOREACH(IMapContextClientEventListener* evListener, m_eventListeners)
    {
        if (oldNode) evListener->OnNodeFocus(oldNode, false);
        evListener->OnNodeFocus(node, true);
    }
}

void MapContext::ChangeTextAtCursor(const QString &text)
{
    // todo: impl
}

void MapContext::InternalOnNodePosition(MapNode *node, QPointF oldPos, QPointF newPos)
{
    Q_FOREACH(IMapContextClientEventListener* evListener, m_eventListeners)
    {
        evListener->OnNodePosition(node, oldPos, newPos);
    }
}

void MapContext::AddEventListener(IMapContextClientEventListener* listener) {
    m_eventListeners.push_back(listener);
}

void MapContext::PresentEntireMapAsEvents(IMapContextClientEventListener* listener) {
    const QMap<MapNode*, MapNode*>& allNodes = m_nodeStorage->AllNodes();
    {
        QMapIterator<MapNode*, MapNode*> it(allNodes);
        while(it.hasNext()) {
            it.next();
            listener->OnNodeAdded(it.key(), it.value());
        }
    }
}

void MapContext::RemoveEventListener(IMapContextClientEventListener* listener) {
    const int index = m_eventListeners.indexOf(listener);
    if (index >= 0)
        m_eventListeners.erase(m_eventListeners.begin() + index);
}

MapNode *MapContext::GetCurrenNode()
{
    return m_curNode;
}

}

