#ifndef MAPCONTEXT_H
#define MAPCONTEXT_H

#include <QObject>

namespace MindMapRa {

class MapNode;

class MapContext : public QObject
{
    Q_OBJECT
public:
    explicit MapContext(QObject *parent = 0);

signals:
    void OnNodeAdded(MapNode* node);
    void OnNodeDeleted(MapNode* node);
    void OnNodeFocus(MapNode* node, bool isSetFocus);

public slots:
    void AddChildAtCursor();
    void MoveCursor(int hor, int ver);
    void DeleteNodeAtCursor();

};

}

#endif // MAPCONTEXT_H
