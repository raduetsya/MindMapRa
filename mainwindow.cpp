#include "mainwindow.h"
#include "scrollareapan.h"

const QString APP_NAME = "MindMapRa";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(APP_NAME);

    m_scrollArea = new ScrollAreaPan(this);

    m_backWidget = new QFrame(m_scrollArea);
    m_backWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_backWidget->setBackgroundRole(QPalette::Dark);

    m_scrollArea->setWidget(m_backWidget);

    setCentralWidget(m_scrollArea);
}

MainWindow::~MainWindow()
{

}
