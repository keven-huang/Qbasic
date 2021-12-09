#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pro = new program;
    connect(ui->btnClearCode,SIGNAL(clicked()),this,SLOT(clearall()));
    connect(ui->cmdLineEdit,SIGNAL(returnPressed()),this,SLOT(codeLineEdit_return()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::ProcessCmd(QString cmd)
{
    bool cmd_op = true;
    if(cmd.isEmpty()) return cmd_op;
    QStringList Qlist = cmd.split(' ',QString::SkipEmptyParts);
    if(Qlist[0] == "RUN"){
        pro->run();
        return cmd_op;
    }
    if(Qlist[0] == "LOAD"){

        pro->load();
        return cmd_op;
    }
    if(Qlist[0] == "LIST"){
        return cmd_op;
    }
    if(Qlist[0] == "CLEAR"){
        clearall();
        return cmd_op;
    }
    if(Qlist[0] == "HELP"){
        return cmd_op;
    }
    if(Qlist[0] == "QUIT"){
        this->close();
        return cmd_op;
    }
    cmd_op = false;
    return cmd_op;
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
    pro->clear();

}

void MainWindow::codeLineEdit_return()
{
    try {
        QString input = ui->cmdLineEdit->text();
        ui->cmdLineEdit->clear();
        bool cmd_op = ProcessCmd(input);
        if(!cmd_op){
            pro->ProcessState(input);
            ui->CodeDisplay->append(input);
        }
    } catch (QString error) {
        qDebug()<<error;
    }

}
