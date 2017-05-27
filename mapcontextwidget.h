#ifndef MAPCONTEXTWIDGET_H
#define MAPCONTEXTWIDGET_H

#include <QObject>
#include <QSet>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsView;
QT_END_NAMESPACE

class ScrollAreaPan;
class MapNodeWidget;

class MapContextWidget : public QFrame
{
public:
    MapContextWidget(QWidget* parent);

signals:

public slots:

private:
    void AddNode();

    QGraphicsScene* m_nodeScene;
    QGraphicsView* m_nodeView;
    ScrollAreaPan* m_scrollArea;
    QSet<MapNodeWidget*> m_nodeWidgets;
};

#endif // MAPCONTEXTWIDGET_H
