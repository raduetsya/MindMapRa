#ifndef MAPCONTEXT_H
#define MAPCONTEXT_H

#include <QVector>
#include <QMap>

namespace MindMapRa {

class MapNode;
class MapContext;

class IMapContextClientEventListener {
public:
    virtual ~IMapContextClientEventListener() {};

    virtual void OnNodeAdded(MapNode* node, MapContext* caller) = 0;
    virtual void OnNodeDeleted(MapNode* node, MapContext* caller) = 0;
};

/*
 * Facade for all node storage/interaction
 * Works with visible nodes
 */
class MapContext
{
public:
    explicit MapContext();

    void AddEventListener(IMapContextClientEventListener* listener);
    void PresentEntireMapAsEvents(IMapContextClientEventListener* listener);
    void RemoveEventListener(IMapContextClientEventListener* listener);

    MapNode* AddNode(MapNode* parent);
    void RemoveNode(MapNode* node);

    MapNode* GetRootNode();
    MapNode* GetNodeParent(MapNode* node);
    MapNode* GetNodeFirstChild(MapNode* parent);
    MapNode* GetNextSibling(MapNode* node);
    MapNode* GetPrevSibling(MapNode* node);

private:
    QVector<MapNode*> m_nodes;
    QMap<MapNode*, MapNode*> m_parents;
    QMap<MapNode*, QVector<MapNode*> > m_childs;

    QVector<IMapContextClientEventListener*> m_eventListeners;
};

}

#endif // MAPCONTEXT_H
