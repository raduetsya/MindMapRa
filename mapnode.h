#ifndef MAPNODE_H
#define MAPNODE_H

#include <QString>
#include <QPointF>

namespace MindMapRa {

class MapNode
{
public:
    MapNode(const QString& text, const QPointF& pos)
        : m_text(text)
        , m_pos(pos)
    {}

    QString GetText() const { return m_text; }
    QPointF GetPos() const { return m_pos; }
    float GetWidth() const { return 100.0f; }
    // float GetHeight() const { return 20.0f; }

    void SetPos(QPointF pos) { m_pos = pos; }

private:
    QString m_text;
    QPointF m_pos;
};

}

#endif // MAPNODE_H
