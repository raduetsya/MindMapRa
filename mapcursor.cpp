#include "mapcursor.h"
#include "mapcontext.h"
#include "mapnode.h"

namespace MindMapRa {

MapCursor::MapCursor(MapContext* context)
    : m_context(context)
    , m_node(m_context->GetRootNode())
{

}


void MindMapRa::MapCursor::SetNode(MindMapRa::MapNode *node)
{
    m_node = node;
    emit OnNodeFocusChanged(m_node);
}

MapNode *MapCursor::GetNode()
{
    return m_node;
}

void MindMapRa::MapCursor::MoveCursor(MindMapRa::MapCursor::CursorDirection dir)
{
    switch(dir) {
    case CD_Up:
        m_node = m_context->GetPrevSibling(m_node);
        break;
    case CD_Down:
        m_node = m_context->GetNextSibling(m_node);
        break;
    case CD_Left:
        m_node = m_context->GetNodeParent(m_node);
        break;
    case CD_Right:
        m_node = m_context->GetNodeFirstChild(m_node);
        break;
    default:
        return;
    }

    emit OnNodeFocusChanged(m_node);
}

MindMapRa::MapNode *MindMapRa::MapCursor::CreateChildNode()
{
    MapNode* newNode = m_context->AddNode(m_node);
    return newNode;
}

void MindMapRa::MapCursor::DeleteCurrentNode()
{
    MapNode* parentNode = m_context->GetNodeParent(m_node);
    m_context->RemoveNode(m_node);
    m_node = parentNode;
}

}
