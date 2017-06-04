#ifndef NODESTORAGE_H
#define NODESTORAGE_H

#include <QObject>
#include <QVector>
#include <QMap>

namespace MindMapRa {

class MapNode;

class NodeStorage : public QObject
{
    Q_OBJECT

public:
    explicit NodeStorage(QObject *parent = 0);

    const QMap<MapNode*, MapNode*>& AllNodes() const;

signals:
    void OnNodeAdded(MapNode* node, MapNode* parent);
    void OnNodeDeleted(MapNode* node);

public slots:
    void AddNode(MapNode* node, MapNode* parent);
    void DeleteNode(MapNode* node);

private:
    QMap<MapNode*, MapNode*> m_nodes;
};

}

#endif // NODESTORAGE_H
