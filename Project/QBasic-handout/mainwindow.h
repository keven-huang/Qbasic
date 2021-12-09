#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include<QStringList>
#include<QFileDialog>
#include"program.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool ProcessCmd(QString cmd);
    program * pro;

private slots:
    void on_cmdLineEdit_editingFinished();
    void clearall();
    void codeLineEdit_return();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
