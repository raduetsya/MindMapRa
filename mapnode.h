#ifndef MAPNODE_H
#define MAPNODE_H

#include <QString>

namespace MindMapRa {

class MapNode
{
public:
    MapNode(const QString& text)
        : m_text(text)
    {}

    QString GetText() const { return m_text; }

private:
    QString m_text;
};

}

#endif // MAPNODE_H
