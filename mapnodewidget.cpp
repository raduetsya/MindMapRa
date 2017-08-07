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
    {
    }

    MapNodeWidget* m_parent;

    void mousePressEvent(QMouseEvent* ev) Q_DECL_OVERRIDE
    {
        if (isReadOnly())
        {
            ev->ignore();
            return;
        }

        QPlainTextEdit::mousePressEvent(ev);
    }

    void keyPressEvent(QKeyEvent* ev) Q_DECL_OVERRIDE
    {
        if (isReadOnly() && ev->key() == Qt::Key_Space) {
            setReadOnly(false);
            selectAll();
        }
        else if (!isReadOnly() && ev->key() == Qt::Key_Escape) {
            setReadOnly(true);
            moveCursor(QTextCursor::Start);
        }
        else if (!isReadOnly() && ev->key() == Qt::Key_Tab) {
            setReadOnly(true);
            m_parent->keyPressEvent(ev);
        }
        else if (ev->key() == Qt::Key_Return) {
            m_parent->keyPressEvent(ev);
        }
        else if (!isReadOnly()) {
            QPlainTextEdit::keyPressEvent(ev);
        }
        else {
            m_parent->keyPressEvent(ev);
        }
    }

    bool focusNextPrevChild(bool)
    {
        // prevent internal qt logic with tab focus change
        return false;
    }

    void focusInEvent(QFocusEvent*)
    {
        setStyleSheet("QPlainTextEdit { background-color : #D6B0FF; color : #1D1624; }");
        // setReadOnly(true);
    }

    void focusOutEvent(QFocusEvent *)
    {
        setStyleSheet("QPlainTextEdit { background-color : #FCFFFF; color : #1D1624; }");
        setReadOnly(true);
    }
};

MapNodeWidget::MapNodeWidget(QWidget* parent)
    : QFrame(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setSizeIncrement(10, 10);

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

    clearFocus();
    OnTextChanged();
}

void MapNodeWidget::SetText(const QString &text)
{
    m_label->document()->setPlainText(text);
}

void MapNodeWidget::mousePressEvent(QMouseEvent *)
{
    emit OnChangeFocusUserRequest(this);
}

void MapNodeWidget::keyPressEvent(QKeyEvent *ev)
{
    // input keys are processed in label
    // control keys are processed in parent
    emit OnKeypress(ev);
}

void MapNodeWidget::focusInEvent(QFocusEvent*)
{
    // focus should be on label
    m_label->setFocus();
}

bool MapNodeWidget::focusNextPrevChild(bool)
{
    // prevent internal qt logic with tab focus change
    return false;
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
    emit OnResize(this);
}

