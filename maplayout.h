#ifndef MAPLAYOUT_H
#define MAPLAYOUT_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QPointF>
#include <QRectF>

class ILayoutElement
{
public:
    virtual QSizeF ElementSize() = 0;

    virtual ~ILayoutElement() {};
};

class MapLayout : public QObject
{
    Q_OBJECT
public:

    explicit MapLayout(QObject *parent = 0);

    void FixAllPositions();

    void Add(ILayoutElement* node, ILayoutElement* parent);
    void Remove(ILayoutElement* node);

    QRectF GetPos(ILayoutElement* node);

signals:
    void OnElementPosition(ILayoutElement* node, QPointF newPos);

private:
    int UpdateAndGetNodeSize(ILayoutElement* node, int topPos, int parentLeftPos);

    struct Block {
        ILayoutElement* parent;
        QVector<ILayoutElement*> nodes;
        QVector<int> nodeVertPos;
        QPointF pos;
    };

    QMap<ILayoutElement*, Block> m_blocks;
    QMap<ILayoutElement*, QRectF> m_posCache;
};

#endif // MAPLAYOUT_H
