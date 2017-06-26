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
    void SetFocusNode(bool isFocus);
    void EnableTextEdit(bool isEnable);

    void mousePressEvent(QMouseEvent* ev) Q_DECL_OVERRIDE;

signals:
    void OnChangeFocusUserRequest(MapNodeWidget*);

private slots:
    void OnTextChanged();

private:
    QPlainTextEdit* m_label;
};

#endif // MAPNODEWIDGET_H
