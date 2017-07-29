#ifndef MAPCURSOR_H
#define MAPCURSOR_H

#include <QObject>

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
    MapContext* m_context;
    MapNode* m_node;
};

}

#endif // MAPCURSOR_H
