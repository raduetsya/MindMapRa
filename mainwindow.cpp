#include "mainwindow.h"
#include "mapcontextwidget.h"
#include "mapcontext.h"
#include "mapnode.h"

#include <QGridLayout>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

const QString APP_NAME = "MindMapRa";

const QString TEST_MUPNAME = "/home/raduetsya/mindmap.mup";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(APP_NAME);

    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );
    QGridLayout* layout = new QGridLayout( centralWidget );
    layout->setMargin(0);

    MindMapRa::MapContext* m_context = NULL;
    {
        QFile loadFile(TEST_MUPNAME);
        if (loadFile.open(QIODevice::ReadOnly)) {
            QByteArray dataBytes = loadFile.readAll();
            QJsonDocument loadDoc = QJsonDocument::fromJson(dataBytes);
            m_context = new MindMapRa::MapContext(loadDoc.object()["ideas"].toObject()["1"].toObject());
        } else {
            qWarning("cannot open input file");
        }
    }
    if (m_context == NULL)
        m_context = new MindMapRa::MapContext;

    m_mainWidget = new MapContextWidget(centralWidget, m_context);
    layout->addWidget(m_mainWidget, 0, 0);

    resize(800, 800);
}

MainWindow::~MainWindow()
{
}
