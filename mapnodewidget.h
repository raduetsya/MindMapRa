#ifndef MAPNODEWIDGET_H
#define MAPNODEWIDGET_H

#include <QObject>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
class QMouseEvent;
QT_END_NAMESPACE

#include "maplayout.h"

class MapNodeWidget : public QFrame, public ILayoutElement
{
    Q_OBJECT
public:
    explicit MapNodeWidget(QWidget* parent = NULL);

    // ILayoutElement impl
    QSizeF ElementSize() Q_DECL_OVERRIDE;

    void SetText(const QString& text);
    void SetFocusNode(bool isFocus);
    bool IsInFocus();

    void mousePressEvent(QMouseEvent* ev) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* ev) Q_DECL_OVERRIDE;

signals:
    void OnChangeFocusUserRequest(MapNodeWidget*);
    void OnCursorMoveRequested(bool isUp, bool isDown, bool isLeft, bool isRight);
    void OnCursorCreateNodeRequested();

private slots:
    void OnTextChanged();

private:
    QPlainTextEdit* m_label;
    QSize m_size;
};

#endif // MAPNODEWIDGET_H
