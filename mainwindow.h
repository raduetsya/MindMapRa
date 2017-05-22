#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>

class ScrollAreaPan;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QFrame* m_backWidget;
    ScrollAreaPan* m_scrollArea;
};

#endif // MAINWINDOW_H
