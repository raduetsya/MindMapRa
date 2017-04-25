#ifndef NODESTORAGE_H
#define NODESTORAGE_H

#include <QObject>

namespace MindMapRa {

class MapNode;

class NodeStorage : public QObject
{
    Q_OBJECT

public:
    explicit NodeStorage(QObject *parent = 0);

    void AddNode(MapNode* node);
    void DeleteNode(MapNode* node);
    void SetConnection(MapNode* node, bool isDoConnect);

signals:
    void OnNodeAdded(MapNode* ptr);
    void OnNodeDeleted(MapNode* ptr);
    void OnConnected(MapNode* from, MapNode* to);
    void OnDisconnected(MapNode* from, MapNode* to);

public slots:
};

}

#endif // NODESTORAGE_H
