#ifndef NODESTORAGE_H
#define NODESTORAGE_H

#include <QObject>
#include <QVector>
#include <QSet>
#include <QPair>

namespace MindMapRa {

class MapNode;

class NodeStorage : public QObject
{
    Q_OBJECT

public:
    explicit NodeStorage(QObject *parent = 0);

    QVectorIterator<MapNode*> IterNodes() const;
    QVectorIterator<MapNode*> IterConnections(MapNode* nodeFrom) const;


signals:
    void OnNodeAdded(MapNode* node);
    void OnNodeDeleted(MapNode* node);
    void OnConnected(MapNode* from, MapNode* to);
    void OnDisconnected(MapNode* from, MapNode* to);

public slots:
    void AddNode(MapNode* node);
    void DeleteNode(MapNode* node);
    void SetConnection(MapNode* from, MapNode* to, bool isDoConnect);

private:
    QVector<MapNode*> m_nodes;
    QSet< QPair<MapNode*, MapNode*> > m_conns;
};

}

#endif // NODESTORAGE_H
