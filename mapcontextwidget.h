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
class MapLayout;

#include "maplayout.h"

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

    void keyPressEvent(QKeyEvent* ev);


signals:

public slots:
    void OnChangeFocusUserRequest(MapNodeWidget* widget);
    void OnNodePosition(ILayoutElement* node, QPointF pos);

private:
    QPainterPath GenPath(MindMapRa::MapNode* parent, MindMapRa::MapNode* child);

    QGraphicsScene* m_nodeScene;
    MindMapRa::MapContext* m_model;
    MapLayout* m_layout;

    QGraphicsView* m_nodeView;
    ScrollAreaPan* m_scrollArea;

    QMap<MindMapRa::MapNode*, MapNodeWidget*> m_nodeWidgets;
    QMap<MapNodeWidget*, QGraphicsPathItem*> m_pathWidgets;
};

#endif // MAPCONTEXTWIDGET_H
