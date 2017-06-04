#include "maplayout.h"

namespace MindMapRa {

MapLayout::MapLayout(QObject *parent) : QObject(parent)
{
    m_blocks[NULL] = Block();
}

void MapLayout::OnNodeAdded(MapNode* node, MapNode* parent)
{
    Block& blockFrom = m_blocks[parent];
    blockFrom.nodes.append(node);
}

void MapLayout::OnNodeDeleted(MapNode* node)
{
    Q_ASSERT(m_blocks.contains(node) == false);

    QMapIterator<MapNode*, Block> it(m_blocks);
    while (it.hasNext()) {
        it.next();
        if (it.value().nodes.contains(node))
        {
            m_blocks[it.key()].nodes.removeAll(node);
        }
    }
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
    QPointF newPos(parentLeftPos, topPos);

    if (blockIt != m_blocks.end()) {

        Block& block = blockIt.value();
        const int childLeftPos = parentLeftPos + 200;
        int childrenSize = 0;

        for(int childIdx = 0; childIdx < block.nodes.size(); ++childIdx) {
            const int childTop = topPos + childrenSize;
            const int childSize = UpdateAndGetNodeSize(block.nodes[childIdx], childTop, childLeftPos);
            childrenSize += childSize;
        }

        newPos = QPointF(parentLeftPos, topPos + childrenSize/2);
        block.pos = QPointF(parentLeftPos + 200, topPos);

        size = childrenSize;
    }

    const int minimumBlockSize = 50;
    // if it hasnt children
    if (size < minimumBlockSize)
        size = minimumBlockSize;

    QPointF prevPos = newPos;
    emit OnNodePosition(node, prevPos, newPos);

    return size;
}

}
