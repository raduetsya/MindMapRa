#ifndef MAPCURSOR_H
#define MAPCURSOR_H

#include <QObject>
#include <QVector>

namespace MindMapRa {

class MapContext;
class MapNode;

class MapCursor : public QObject
{
    Q_OBJECT;
public:
    MapCursor(MapContext* context);

    enum CursorDirection {
        CD_Up,
        CD_Down,
        CD_Left,
        CD_Right,

        CD_Count
    };

    void SetNode(MapNode* node);
    MapNode* GetNode();
    void MoveCursor(CursorDirection dir);
    MapNode* CreateChildNode();
    void DeleteCurrentNode();

signals:
    void OnNodeFocusChanged(MapNode* node);

public slots:

private:
    MapNode* MoveVertical(MapNode* node, bool isUp);

    MapContext* m_context;
    MapNode* m_node;

    QVector<MapNode*> m_dirCache;
};

}

#endif // MAPCURSOR_H
