#include "scrollareapan.h"
#include <QScrollBar>

ScrollAreaPan::ScrollAreaPan(QWidget* parent)
    : QScrollArea(parent)
{

}

void ScrollAreaPan::mousePressEvent(QMouseEvent* e) {
    m_mousePos = e->pos();
}

void ScrollAreaPan::mouseMoveEvent(QMouseEvent* e) {
    QPoint diff = e->pos() - m_mousePos;
    m_mousePos = e->pos();

    verticalScrollBar()->setValue(verticalScrollBar()->value() - diff.y());
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - diff.x());
}

