#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnClearCode,SIGNAL(clicked()),this,SLOT(clearall()));
    connect(ui->cmdLineEdit,SIGNAL(returnPressed()),this,SLOT(codeLineEdit_return()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdLineEdit_editingFinished()
{
    QString cmd = ui->cmdLineEdit->text();
    ui->cmdLineEdit->setText("");

    ui->CodeDisplay->append(cmd);
}

void MainWindow::clearall()
{
    ui->CodeDisplay->clear();
    ui->treeDisplay->clear();
    ui->textBrowser->clear();
}

void MainWindow::codeLineEdit_return()
{
    try {
        QString input = ui->cmdLineEdit->text();
        ui->cmdLineEdit->clear();
        ui->CodeDisplay->append(input);

    } catch (QString error) {

    }

}
