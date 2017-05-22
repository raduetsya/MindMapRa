#ifndef SCROLLAREAPAN_H
#define SCROLLAREAPAN_H

#include <QScrollArea>
#include <QMouseEvent>

class ScrollAreaPan : public QScrollArea
{
public:
    ScrollAreaPan(QWidget* parent);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);

private:
    QPoint m_mousePos;
};

#endif // SCROLLAREAPAN_H
