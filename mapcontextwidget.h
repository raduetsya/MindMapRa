#ifndef MAPCONTEXTWIDGET_H
#define MAPCONTEXTWIDGET_H

#include <QObject>
#include <QFrame>

class ScrollAreaPan;

class MapContextWidget : public QFrame
{
public:
    MapContextWidget(QWidget* parent);

signals:

public slots:

private:
    QFrame* m_contentFrame;
    ScrollAreaPan* m_scrollArea;
};

#endif // MAPCONTEXTWIDGET_H
