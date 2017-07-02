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

class ScrollAreaPan;
class MapNodeWidget;

namespace MindMapRa {
    class MapContext;
}

#include "mapcontext.h" // todo: move IMapContextClientEventListener impl to another file, and rename

class MapContextWidget : public QFrame, public MindMapRa::IMapContextClientEventListener
{
    Q_OBJECT
public:
    explicit MapContextWidget(QWidget* parent = NULL, MindMapRa::MapContext* model = NULL);

    // IMapContextClientEventListener impl
    void OnNodeAdded(MindMapRa::MapNode* node, MindMapRa::MapNode* parent);
    void OnNodeDeleted(MindMapRa::MapNode* node);
    void OnNodeFocus(MindMapRa::MapNode* node, bool isSetFocus);
    void OnNodePosition(MindMapRa::MapNode* node, QPointF oldPos, QPointF newPos);

    void keyPressEvent(QKeyEvent* ev);

signals:

public slots:
    void OnChangeFocusUserRequest(MapNodeWidget* widget);

private:
    QPainterPath GenPath(MindMapRa::MapNode* parent, MindMapRa::MapNode* child);

    QGraphicsScene* m_nodeScene;
    QGraphicsView* m_nodeView;
    ScrollAreaPan* m_scrollArea;

    QMap<MindMapRa::MapNode*, MapNodeWidget*> m_nodeWidgets;
    MindMapRa::MapContext* m_model;
    QMap<MapNodeWidget*, QGraphicsPathItem*> m_pathWidgets;
};

#endif // MAPCONTEXTWIDGET_H
