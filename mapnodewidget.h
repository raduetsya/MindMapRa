#ifndef MAPNODEWIDGET_H
#define MAPNODEWIDGET_H

#include <QObject>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
class QMouseEvent;
QT_END_NAMESPACE

class MapNodeWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MapNodeWidget(QWidget* parent = NULL);

    void SetText(const QString& text);

    void mousePressEvent(QMouseEvent* ev) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* ev) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent* ev) Q_DECL_OVERRIDE;
    bool focusNextPrevChild(bool) Q_DECL_OVERRIDE;

signals:
    void OnChangeFocusUserRequest(MapNodeWidget*);
    void OnCursorMoveRequested(bool isUp, bool isDown, bool isLeft, bool isRight);
    void OnCursorCreateNodeRequested();
    void OnCursorRemoveNodeRequested();
    void OnKeypress(QKeyEvent* ev);

private slots:
    void OnTextChanged();

private:
    QPlainTextEdit* m_label;
    QSize m_size;
};

#endif // MAPNODEWIDGET_H
