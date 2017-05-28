#ifndef MAPNODEWIDGET_H
#define MAPNODEWIDGET_H

#include <QObject>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class MapNodeWidget : public QFrame
{
public:
    MapNodeWidget(QWidget* parent = NULL);
    void SetText(const QString& text);

signals:

public slots:

private:
    QLabel* m_label;
};

#endif // MAPNODEWIDGET_H
