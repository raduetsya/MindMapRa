#include "nodestorage.h"

namespace MindMapRa {

NodeStorage::NodeStorage(QObject *parent)
: QObject(parent)
{

}

const QMap<MapNode*, MapNode*>& NodeStorage::AllNodes() const
{
    return m_nodes;
}


void NodeStorage::AddNode(MapNode* node, MapNode* parent) {
    m_nodes[node] = parent;
    emit OnNodeAdded(node, parent);
}

void NodeStorage::DeleteNode(MapNode* node) {
    const int delCount = m_nodes.remove(node);
    Q_ASSERT( (delCount == 0 || delCount == 1) );
    if (delCount == 1)
        emit OnNodeDeleted(node);
}

}
