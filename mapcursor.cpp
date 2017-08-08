#include "mapcursor.h"
#include "mapcontext.h"
#include "mapnode.h"

namespace MindMapRa {

MapCursor::MapCursor(MapContext* context)
    : m_context(context)
    , m_node(m_context->GetRootNode())
{
    m_dirCache.resize(CD_Count);
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

MapNode* MapCursor::MoveVertical(MapNode* node, bool isUp)
{
    if (node)
    {
        MapNode* sibling = (isUp ? m_context->GetPrevSibling(node) : m_context->GetNextSibling(m_node));
        if (!sibling)
        {
            MapNode* parent = m_context->GetNodeParent(node);
            MapNode* parentSibl = (isUp ? m_context->GetPrevSibling(parent) : m_context->GetNextSibling(parent));
            if (parentSibl) {
                MapNode* parentSiblChild = (isUp ? m_context->GetNodeLastChild(parentSibl) : m_context->GetNodeFirstChild(parentSibl));
                if (parentSiblChild)
                    return parentSiblChild;
                else
                    return parentSibl;

            } else {
                return NULL;
            }
        }
        else {
            return sibling;
        }
    } else {
        MapNode* cached = (isUp ? m_dirCache[CD_Up] : m_dirCache[CD_Down]);
        if (cached) {
            m_dirCache[CD_Up] = m_dirCache[CD_Down] = m_dirCache[CD_Left] = m_dirCache[CD_Right] = NULL;
            return cached;
        }
    }

    return NULL;
}

void MindMapRa::MapCursor::MoveCursor(MindMapRa::MapCursor::CursorDirection dir)
{
    MapNode* oldNode = m_node;

    switch(dir) {
    case CD_Up:
        m_node = MoveVertical(m_node, true);
        break;
    case CD_Down:
        m_node = MoveVertical(m_node, false);
        break;
    case CD_Left:
        {
            if (m_node)
                m_node = m_context->GetNodeParent(m_node);
            else {
                m_node = m_dirCache[CD_Left];
                m_dirCache[CD_Up] = m_dirCache[CD_Down] = m_dirCache[CD_Left] = m_dirCache[CD_Right] = NULL;
            }
        }
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
    if (!m_node)
        return NULL;

    MapNode* newNode = m_context->AddNode(m_node);
    return newNode;
}

void MindMapRa::MapCursor::DeleteCurrentNode()
{
    MapNode* parentNode = m_context->GetNodeParent(m_node);
    if (parentNode == NULL)
        return;

    m_dirCache[CD_Up] = m_context->GetPrevSibling(m_node);
    m_dirCache[CD_Down] = m_context->GetNextSibling(m_node);
    m_dirCache[CD_Left] = m_context->GetNodeParent(m_node);

    m_context->RemoveNode(m_node);
    m_node = NULL;
}

}
