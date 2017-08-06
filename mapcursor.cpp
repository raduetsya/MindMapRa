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
    MapNode* oldNode = m_node;

    switch(dir) {
    case CD_Up:
        {
            MapNode* sibling = m_context->GetPrevSibling(m_node);
            if (!sibling)
            {
                MapNode* parent = m_context->GetNodeParent(m_node);
                MapNode* parentSibl = m_context->GetPrevSibling(parent);
                MapNode* parentSiblChild = (parentSibl ? m_context->GetNodeLastChild(parentSibl) : NULL);
                if (parentSiblChild)
                    m_node = parentSiblChild;
                else if (parentSibl)
                    m_node = parentSibl;
                else
                    m_node = NULL;
            }
            else
                m_node = sibling;
        }
        break;
    case CD_Down:
        {
            MapNode* sibling = m_context->GetNextSibling(m_node);
            if (!sibling)
            {
                MapNode* parent = m_context->GetNodeParent(m_node);
                MapNode* parentSibl = m_context->GetNextSibling(parent);
                MapNode* parentSiblChild = (parentSibl ? m_context->GetNodeFirstChild(parentSibl) : NULL);
                if (parentSiblChild)
                    m_node = parentSiblChild;
                else if (parentSibl)
                    m_node = parentSibl;
                else
                    m_node = NULL;
            }
            else
                m_node = sibling;
        }
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

    if (m_node == NULL)
        m_node = oldNode;

    if (oldNode != m_node)
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
    if (parentNode == NULL)
        return;

    m_context->RemoveNode(m_node);
    m_node = NULL;
}

}
