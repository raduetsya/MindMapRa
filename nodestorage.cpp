#include "nodestorage.h"

namespace MindMapRa {

NodeStorage::NodeStorage(QObject *parent)
: QObject(parent)
{

}


void NodeStorage::AddNode(MapNode *node) {
    if (m_nodes.contains(node))
        return;

    m_nodes.append(node);
    emit OnNodeAdded(node);
}

void NodeStorage::DeleteNode(MapNode* node) {
    const int delCount = m_nodes.removeAll(node);
    Q_ASSERT(delCount == 0 || delCount == 1);
    if (delCount == 1)
        emit OnNodeDeleted(node);
}

void NodeStorage::SetConnection(MapNode *from, MapNode *to, bool isDoConnect) {
    if (!m_nodes.contains(from) || !m_nodes.contains(to))
        return;

    const QPair<MapNode*, MapNode*> pair = QPair<MapNode*, MapNode*>(from, to);
    const bool found = m_conns.contains( pair );

    if (!found && isDoConnect) {
        m_conns.insert(pair);
        emit OnConnected(from, to);
    }
    else if (found && isDoConnect) {
        m_conns.remove(pair);
        emit OnDisconnected(from, to);
    }
}

}
