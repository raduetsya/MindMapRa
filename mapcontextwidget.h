#ifndef MAPCONTEXTWIDGET_H
#define MAPCONTEXTWIDGET_H

#include <QObject>
#include <QSet>
#include <QFrame>
#include <QMap>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsView;
class QGraphicsPathItem;
QT_END_NAMESPACE

class MapNodeWidget;
class MapLayout;

#include "maplayout.h"

namespace MindMapRa {
class MapContext;
class MapCursor;
class MapNode;
}

class MapContextWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MapContextWidget(QWidget* parent = NULL, MindMapRa::MapContext* model = NULL);

    void keyPressEvent(QKeyEvent* ev) Q_DECL_OVERRIDE;

public slots:
    void OnNodePosition(QWidget* node, QPointF pos);
    void OnNodeAdded(MindMapRa::MapNode* node, MindMapRa::MapContext* caller);
    void OnNodeDeleted(MindMapRa::MapNode* node, MindMapRa::MapContext* caller);
    void OnChangeFocusUserRequest(MapNodeWidget* widget);
    void OnNodeKeypress(QKeyEvent* ev);

private:
    QPainterPath GenPath(MindMapRa::MapNode* parent, MindMapRa::MapNode* child);
    void CreateNodeAtCursor();
    void DeleteNodeAtCursor();
    void MoveCursor(bool isUp, bool isDown, bool isLeft, bool isRight);

    QGraphicsScene* m_nodeScene;
    MindMapRa::MapContext* m_context;
    MindMapRa::MapCursor* m_cursor;
    MapLayout* m_layout;

    QGraphicsView* m_nodeView;

    QMap<MindMapRa::MapNode*, MapNodeWidget*> m_nodeWidgets;
    QMap<MapNodeWidget*, QGraphicsPathItem*> m_pathWidgets;
};

#endif // MAPCONTEXTWIDGET_H
