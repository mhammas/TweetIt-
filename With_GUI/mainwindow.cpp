#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_QByUoMap = new Map();
    m_QByUoMap->moveToThread(&workThread);


    connect(this,SIGNAL(sendSearchChar(QString)),m_QByUoMap,SLOT(acceptSearchChar(QString)));
    connect(this,SIGNAL(sendFilePath(QString)),m_QByUoMap,SLOT(acceptFilePath(QString)));
    connect(m_QByUoMap,SIGNAL(sendSearchResult(QStringList)),this,SLOT(acceptSerachResult(QStringList)));
    connect(m_QByUoMap,SIGNAL(readFileOk(bool)),this,SLOT(acceptReadFile(bool)));
    connect(m_QByUoMap,SIGNAL(searchOk(bool)),this,SLOT(acceptSearch(bool)));
    connect(m_QByUoMap,SIGNAL(sendClock(double)),this,SLOT(acceptTime(double)));

    workThread.start();
}

MainWindow::~MainWindow()
{
    workThread.quit();
    workThread.wait();
    delete ui;
}

void MainWindow::on_pushButton_open_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, "Load .txt file", QString(), "*.txt");

    if (!filename.isNull())
    {
        emit sendFilePath(filename);
    }
    ui->pushButton_open->setEnabled(false);
    ui->pushButton_search->setEnabled(false);
    ui->lineEdit_2->setText(filename);
}

void MainWindow::acceptSerachResult(QStringList retlist)
{
    ui->textEdit_2->setText("");
    for(int i = 0;i < retlist.size();i++){
        ui->textEdit_2->append(retlist.at(i));
    }
}

void MainWindow::on_pushButton_search_clicked()
{
    emit sendSearchChar(ui->lineEdit->text());
    ui->pushButton_open->setEnabled(false);
    ui->pushButton_search->setEnabled(false);
}

void MainWindow::acceptReadFile(bool)
{
    ui->pushButton_open->setEnabled(true);
    ui->pushButton_search->setEnabled(true);
}

void MainWindow::acceptSearch(bool)
{
    ui->pushButton_open->setEnabled(true);
    ui->pushButton_search->setEnabled(true);
}

void MainWindow::acceptTime(double value)
{
    ui->label_time->setText("Operation Executed in " + QString("%1/s").arg(value));
}
