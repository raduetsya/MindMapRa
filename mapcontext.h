#ifndef MAPCONTEXT_H
#define MAPCONTEXT_H

#include <QObject>
#include <QVector>
#include <QPointF>

namespace MindMapRa {

class MapNode;
class MapContextImpl;
class NodeStorage;
class MapLayout;

class IMapContextClientEventListener {
public:
    virtual ~IMapContextClientEventListener() {};

    virtual void OnNodeAdded(MapNode* node, MapNode* parent) = 0;
    virtual void OnNodeDeleted(MapNode* node) = 0;
    virtual void OnNodeFocus(MapNode* node, bool isSetFocus) = 0;
    virtual void OnNodePosition(MapNode *node, QPointF oldPos, QPointF newPos) = 0;
};

/*
 * Facade for all node storage/interaction
 * Works with visible nodes
 */
class MapContext : public QObject
{
    Q_OBJECT
public:
    explicit MapContext(QObject *parent = 0);

    void AddEventListener(IMapContextClientEventListener* listener);
    void PresentEntireMapAsEvents(IMapContextClientEventListener* listener);
    void RemoveEventListener(IMapContextClientEventListener* listener);

public slots:
    MapNode* GetCurrenNode();
    MapNode* AddChildAtCursor();
    void MoveCursor(int hor, int ver);
    void DeleteNodeAtCursor();
    void SelectNode(MapNode* node);
    void ChangeTextAtCursor(const QString& text);

private slots:
    void InternalOnNodePosition(MapNode* node, QPointF oldPos, QPointF newPos);

private:
    NodeStorage* m_nodeStorage;
    MapLayout* m_layout;
    MapNode* m_curNode;

    QVector<IMapContextClientEventListener*> m_eventListeners;
};

}

#endif // MAPCONTEXT_H
