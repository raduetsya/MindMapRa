#include "mapcontext.h"
#include "nodestorage.h"
#include "mapnode.h"

#include <QMap>

namespace MindMapRa {

MapContext::MapContext(QObject *parent)
: QObject(parent)
, m_nodeStorage(new NodeStorage(this))
, m_curNode(NULL)
{
    m_curNode = new MapNode("New document", QPointF(0, 0));
    m_nodeStorage->AddNode(m_curNode);

    // connect(nodeStorage, layout, added)
}

QMap<MapNode*, QVector<MapNode*> > MapContext::AllNodes()
{
    QMap<MapNode*, QVector<MapNode*> > resAll = m_nodeStorage->AllNodes();
    return resAll;
}

void MapContext::AddChildAtCursor() {
    if (!m_curNode)
        return;

    MapNode* oldNode = m_curNode;
    m_curNode = new MapNode("", QPointF(0, 0));
    m_nodeStorage->AddNode(m_curNode);
    m_nodeStorage->SetConnection(oldNode, m_curNode, true);

    emit OnNodeAdded(m_curNode);
    emit OnNodeFocus(oldNode, false);
    emit OnNodeFocus(m_curNode, true);
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
    node = m_curNode;

    if (oldNode) emit OnNodeFocus(oldNode, false);
    emit OnNodeFocus(node, true);
}

}

