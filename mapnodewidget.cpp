#include "mapnodewidget.h"

#include <QTextEdit>
#include <QGridLayout>
#include <QPlainTextEdit>

MapNodeWidget::MapNodeWidget(QWidget* parent)
    : QFrame(parent)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setSizeIncrement(10, 10);

    QGridLayout* layout = new QGridLayout(this);

    m_label = new QPlainTextEdit(this);
    m_label->setPlaceholderText("Press SPACE to edit");
    m_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_label->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_label->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_label->setReadOnly(true);
    layout->addWidget(m_label);

    connect(m_label, SIGNAL(textChanged()),
            this, SLOT(OnTextChanged()));

    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

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
    // m_label->setText(text);
}

void MapNodeWidget::SetFocusNode(bool isFocus)
{
    if (isFocus)
        setBackgroundRole(QPalette::Light);
    else
        setBackgroundRole(QPalette::Dark);
}

void MapNodeWidget::EnableTextEdit(bool isEnable)
{
    m_label->setReadOnly(!isEnable);
    m_label->setFocus();
}

void MapNodeWidget::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit OnChangeFocusUserRequest(this);
}

void MapNodeWidget::OnTextChanged()
{
    const QFontMetrics fm(m_label->font());
    const QSize addSize(40, 40);
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
