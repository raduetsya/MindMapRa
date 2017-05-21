#include "maplayout.h"

namespace MindMapRa {

MapLayout::MapLayout(QObject *parent) : QObject(parent)
{

}

void MapLayout::OnNodeAdded(MapNode* node)
{
    Q_ASSERT(!m_orphans.nodes.contains(node));
    m_orphans.nodes.append(node);
}

void MapLayout::OnNodeDeleted(MapNode* node)
{
    Q_ASSERT(m_orphans.nodes.contains(node));
    m_orphans.nodes.removeAll(node);
}

void MapLayout::OnConnected(MapNode *from, MapNode *to)
{
    Q_ASSERT(m_blocks.contains(from));
    Q_ASSERT(m_orphans.nodes.contains(to));

    Block& blockFrom = *m_blocks.find(from);
    m_orphans.nodes.removeAll(to);
    blockFrom.nodes.append(to);
}

void MapLayout::OnDisconnected(MapNode *from, MapNode *to)
{
    Q_ASSERT(m_blocks.contains(from));
    Q_ASSERT(m_blocks[from].nodes.contains(to));

    Block& blockFrom = *m_blocks.find(from);
    blockFrom.nodes.removeAll(to);
    m_orphans.nodes.append(to);
}

void MapLayout::FixAllPositions()
{
    Q_ASSERT(m_blocks[NULL].nodes.empty() == false);
    MapNode*& rootNode = m_blocks[NULL].nodes.first();
    UpdateAndGetNodeSize(rootNode, 0, 0);
}

int MapLayout::UpdateAndGetNodeSize(MapNode *node, int topPos, int parentLeftPos)
{
    QMap<MapNode*, Block>::iterator blockIt = m_blocks.find(node);
    int size = 0;
    QPointF newPos(topPos, parentLeftPos);

    if (blockIt != m_blocks.end()) {

        Block& block = blockIt.value();
        const int childLeftPos = parentLeftPos + 200;
        int childrenSize = 0;

        for(int childIdx = 0; childIdx < block.nodes.size(); ++childIdx) {
            const int childTop = topPos + size;
            const int childSize = UpdateAndGetNodeSize(block.nodes[childIdx], childTop, childLeftPos);
            childrenSize += childSize;
        }

        block.pos.setY(topPos + childrenSize/2);
        block.pos.setX(parentLeftPos + 200);

        newPos = QPointF(block.pos);

        size = childrenSize;
    }

    const int minimumBlockSize = 20;
    // if it hasnt children
    if (size < minimumBlockSize)
        size = minimumBlockSize;

    QPointF prevPos = newPos;
    emit OnNodePosition(node, prevPos, newPos);

    return size;
}

}
