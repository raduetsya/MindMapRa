#include "mainwindow.h"
#include "mapcontextwidget.h"

#include <QGridLayout>

const QString APP_NAME = "MindMapRa";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(APP_NAME);

    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );
    QGridLayout* layout = new QGridLayout( centralWidget );
    layout->setMargin(0);

    m_mainWidget = new MapContextWidget(centralWidget);
    layout->addWidget(m_mainWidget, 0, 0);

    resize(800, 800);
}

MainWindow::~MainWindow()
{
}
