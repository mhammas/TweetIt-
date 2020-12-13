#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAbstractButton>
#include <QLabel>
#include <QMainWindow>
#include "map.h"
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sendFilePath(QString);
    void sendSearchChar(QString);
private slots:
    void on_pushButton_open_clicked();

    void acceptSerachResult(QStringList);
    void on_pushButton_search_clicked();
    void acceptReadFile(bool);
    void acceptSearch(bool);
    void acceptTime(double);
private:
    Ui::MainWindow *ui;
    Map *m_QByUoMap;
    QThread workThread;
};
#endif // MAINWINDOW_H
