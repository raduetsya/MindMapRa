#ifndef MAPCONTEXT_H
#define MAPCONTEXT_H

#include <QObject>

namespace MindMapRa {

class MapNode;
class MapContextImpl;
class NodeStorage;

/*
 * Facade for all node storage/interaction
 * Works with visible nodes
 */
class MapContext : public QObject
{
    Q_OBJECT
public:
    explicit MapContext(QObject *parent = 0);

    QMap<MapNode*, QVector<MapNode*> > AllNodes();

signals:
    void OnNodeAdded(MapNode* node);
    void OnNodeDeleted(MapNode* node);
    void OnNodeFocus(MapNode* node, bool isSetFocus);

public slots:
    void AddChildAtCursor();
    void MoveCursor(int hor, int ver);
    void DeleteNodeAtCursor();
    void SelectNode(MapNode* node);

private:
    void InternalOnNodeAdded(MapNode* node);

private:
    NodeStorage* m_nodeStorage;
    MapNode* m_curNode;
};

}

#endif // MAPCONTEXT_H
