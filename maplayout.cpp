#include "maplayout.h"

MapLayout::MapLayout(QObject *parent) : QObject(parent)
{
    m_blocks[NULL] = Block();
}

void MapLayout::Add(ILayoutElement* node, ILayoutElement* parent)
{
    Block& blockFrom = m_blocks[parent];
    blockFrom.nodes.append(node);
}

void MapLayout::Remove(ILayoutElement* node)
{
    Q_ASSERT(m_blocks.contains(node) == false);

    QMapIterator<ILayoutElement*, Block> it(m_blocks);
    while (it.hasNext()) {
        it.next();
        if (it.value().nodes.contains(node))
        {
            m_blocks[it.key()].nodes.removeAll(node);
        }
    }
}

QRectF MapLayout::GetPos(ILayoutElement *node)
{
    if (m_posCache.contains(node))
        return m_posCache[node];
    return QRectF();
}

void MapLayout::FixAllPositions()
{
    Q_ASSERT(m_blocks[NULL].nodes.empty() == false);
    ILayoutElement*& rootNode = m_blocks[NULL].nodes.first();
    QMap<ILayoutElement*, QPointF> res;
    UpdateAndGetNodeSize(rootNode, 0, 0, res);
    EmitPositionCallbacks(rootNode, res);
}

void MapLayout::EmitPositionCallbacks(ILayoutElement* node, const QMap<ILayoutElement*, QPointF>& res)
{
    QMap<ILayoutElement*, Block>::iterator blockIt = m_blocks.find(node);

    if (res.contains(node))
        emit OnElementPosition(node, res[node]);

    if (blockIt != m_blocks.end()) {
        Block& block = blockIt.value();
        for(int childIdx = 0; childIdx < block.nodes.size(); ++childIdx) {
            EmitPositionCallbacks(block.nodes[childIdx], res);
        }
    }
}

int MapLayout::UpdateAndGetNodeSize(ILayoutElement* node, int topPos, int parentLeftPos, QMap<ILayoutElement*, QPointF>& res)
{
    QMap<ILayoutElement*, Block>::iterator blockIt = m_blocks.find(node);
    int size = 0;
    QPointF newPos(parentLeftPos, topPos);

    if (blockIt != m_blocks.end()) {

        Block& block = blockIt.value();
        const int childLeftPos = parentLeftPos + node->ElementSize().width() + 50;
        int childrenSize = 0;

        for(int childIdx = 0; childIdx < block.nodes.size(); ++childIdx) {
            const int childTop = topPos + childrenSize;
            const int childSize = UpdateAndGetNodeSize(block.nodes[childIdx], childTop, childLeftPos, res);
            childrenSize += childSize;
        }

        newPos = QPointF(parentLeftPos, topPos + childrenSize/2);
        block.pos = QPointF(childLeftPos, topPos);

        size = childrenSize;
    }
    else
    {
        size = node->ElementSize().height();
        newPos = QPointF(parentLeftPos, topPos + size/2);
    }

    const int minimumBlockSize = 20;
    // if it hasnt children
    if (size < minimumBlockSize)
        size = minimumBlockSize;

    m_posCache[node] = QRectF(newPos, node->ElementSize());
    res[node] = newPos;

    return size;
}
