#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include<QStringList>
#include<QFileDialog>
#include<queue>
#include"program.h"
#include "exp.h"
#include "statement.h"
#include "parser.h"
#include "evalstate.h"
#include"tokenizer.h"
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
    bool ProcessImdOp(QString cmd);
    void RunPro(evalstate &Vartable,int beginLine = -1);
    void PrintTree();
    void floorPrint(StmtType type,exp* val,int Line);
    void ProcessLine(QString line);
    void ProcessInput(QString input,int Line,QString InputVar);
    program * pro;
    evalstate Vartable;
private slots:
    void on_cmdLineEdit_editingFinished();
    void clearall();
    void codeLineEdit_return();
    void load();
    void btnRunPro();
private:
    Ui::MainWindow *ui;
    bool WaitInput;
    int WaitInputLine;
    QString InputVar;
    tokenizer *Tokenizer;
    parser *Parser;
    bool ifCondition(QString exp);
};
#endif // MAINWINDOW_H
