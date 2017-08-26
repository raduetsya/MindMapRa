#include "mainwindow.h"
#include "mapcontextwidget.h"
#include "mapcontext.h"
#include "mapnode.h"

#include <QGridLayout>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

const QString APP_NAME = "MindMapRa";

const QString TEST_MUPNAME = QDir::homePath() + "/mindmap.mup";

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
    MindMapRa::MapContext* m_context = m_mainWidget->GetMapContext();
    QJsonDocument doc;
    {
        QJsonObject dataJsonObj = m_context->GetJson();
        QJsonObject rootJsonObj;
        rootJsonObj["formatVersion"] = QJsonValue(3);
        rootJsonObj["id"] = QJsonValue("root");
        rootJsonObj["title"] = QJsonValue(dataJsonObj["title"].toString(""));
        rootJsonObj["ideas"] = QJsonObject();
        QJsonObject ideasRoot;
        ideasRoot["1"] = dataJsonObj;
        rootJsonObj["ideas"] = ideasRoot;
        doc.setObject(rootJsonObj);
    }

    QFile saveFile(TEST_MUPNAME);
    if (saveFile.open(QIODevice::WriteOnly)) {
        QByteArray dataBytes = doc.toJson();
        saveFile.write(dataBytes);
    } else {
        qWarning("cannot write to file");
    }
}
