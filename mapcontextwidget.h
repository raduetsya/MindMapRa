#ifndef MAPCONTEXTWIDGET_H
#define MAPCONTEXTWIDGET_H

#include <QObject>
#include <QSet>
#include <QFrame>
#include <QMap>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsView;
QT_END_NAMESPACE

class ScrollAreaPan;
class MapNodeWidget;

namespace MindMapRa {
    class MapContext;
}

#include "mapcontext.h" // todo: move IMapContextClientEventListener impl to another file, and rename

class MapContextWidget : public QFrame, public MindMapRa::IMapContextClientEventListener
{
public:
    MapContextWidget(QWidget* parent, MindMapRa::MapContext* model = NULL);

    void mousePressEvent(QMouseEvent * event);

    // IMapContextClientEventListener impl
    void OnNodeAdded(MindMapRa::MapNode* node, MindMapRa::MapNode* parent);
    void OnNodeDeleted(MindMapRa::MapNode* node);
    void OnNodeFocus(MindMapRa::MapNode* node, bool isSetFocus);
    void OnNodePosition(MindMapRa::MapNode* node, QPointF oldPos, QPointF newPos);

signals:

public slots:

private:
    QGraphicsScene* m_nodeScene;
    QGraphicsView* m_nodeView;
    ScrollAreaPan* m_scrollArea;

    QMap<MindMapRa::MapNode*, MapNodeWidget*> m_nodeWidgets;
    // QMap<MindMapRa::MapNode*, > m_pathWidgets;
    MindMapRa::MapContext* m_model;
};

#endif // MAPCONTEXTWIDGET_H
