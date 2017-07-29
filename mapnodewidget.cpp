#include "mapnodewidget.h"

#include <QTextEdit>
#include <QGridLayout>
#include <QPlainTextEdit>

class NodeTextEdit : public QPlainTextEdit
{
public:
    explicit NodeTextEdit(MapNodeWidget *parent = 0)
        : QPlainTextEdit(parent)
        , m_parent(parent)
    {}

    MapNodeWidget* m_parent;

    void mousePressEvent(QMouseEvent* ev) Q_DECL_OVERRIDE
    {
        if (!m_parent->IsInFocus())
            m_parent->mousePressEvent(ev);

        QPlainTextEdit::mousePressEvent(ev);
    }

    void keyPressEvent(QKeyEvent* ev) Q_DECL_OVERRIDE
    {
        m_parent->keyPressEvent(ev);
        if (!ev->isAccepted())
            QPlainTextEdit::keyPressEvent(ev);
    }
};

MapNodeWidget::MapNodeWidget(QWidget* parent)
    : QFrame(parent)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setSizeIncrement(10, 10);

    QGridLayout* layout = new QGridLayout(this);

    m_label = new NodeTextEdit(this);
    m_label->setPlaceholderText("Press SPACE to EDIT");
    m_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_label->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_label->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_label->setReadOnly(true);
    layout->addWidget(m_label);
    layout->setMargin(0);

    connect(m_label, SIGNAL(textChanged()),
            this, SLOT(OnTextChanged()));

    this->setFrameShape(QFrame::Box);
    //this->setFrameShadow(QFrame::Raised);

    SetFocusNode(false);
    OnTextChanged();
}

QSizeF MapNodeWidget::ElementSize()
{
    return QSizeF(m_size);
}

void MapNodeWidget::SetText(const QString &text)
{
    Q_UNUSED(text);
    m_label->document()->setPlainText(text);
}

void MapNodeWidget::SetFocusNode(bool isFocus)
{
    if (isFocus)
        setBackgroundRole(QPalette::Button);
    else
        setBackgroundRole(QPalette::Dark);

    m_label->setReadOnly(!isFocus);
    if (isFocus)
    {
        this->setFocus();
        m_label->setFocus();
    }
}


bool MapNodeWidget::IsInFocus()
{
    return !m_label->isReadOnly();
}

void MapNodeWidget::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit OnChangeFocusUserRequest(this);
}

void MapNodeWidget::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Tab)
        emit OnCursorCreateNodeRequested();
    else if (ev->key() == Qt::Key_Up || ev->key() == Qt::Key_Down || ev->key() == Qt::Key_Left || ev->key() == Qt::Key_Right)
        emit OnCursorMoveRequested(
                ev->key() == Qt::Key_Up,
                ev->key() == Qt::Key_Down,
                ev->key() == Qt::Key_Left,
                ev->key() == Qt::Key_Right
                );
    else
        QFrame::keyPressEvent(ev);
}

void MapNodeWidget::OnTextChanged()
{
    const QFontMetrics fm(m_label->font());
    const QSize addSize(15, 10);
    const QSize maxSize(300, 60);

    const QString dataText = m_label->document()->toPlainText();
    const QString placeholderText = m_label->placeholderText();
    const QString text = ((dataText.size() == 0) ? placeholderText : dataText);
    const QRect textRect = fm.boundingRect(
                QRect(QPoint(0,0), maxSize),
                Qt::TextWordWrap | Qt::TextWrapAnywhere,
                text);

    const QSize textSizeAdd(
                textRect.width() + addSize.width(),
                textRect.height() + addSize.height() );

    m_size = QSize( qMin(maxSize.width(), textSizeAdd.width()),
                    qMin(maxSize.height(), textSizeAdd.height()));

    resize(m_size);
}
