#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pro = new program;

    Parser = new parser;
    Tokenizer = new tokenizer;

    WaitInput = false;

    connect(ui->btnClearCode,SIGNAL(clicked()),this,SLOT(clearall()));
    connect(ui->cmdLineEdit,SIGNAL(returnPressed()),this,SLOT(codeLineEdit_return()));

    connect(ui->btnLoadCode,SIGNAL(clicked()),this,SLOT(load()));
    connect(ui->btnRunCode,SIGNAL(clicked()),this,SLOT(btnRunPro()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//处理QBasic操作语言
bool MainWindow::ProcessCmd(QString cmd)
{
    bool cmd_op = true;
    if(cmd.isEmpty()) return cmd_op;
    QStringList Qlist = cmd.split(' ',QString::SkipEmptyParts);
    if(Qlist[0] == "RUN"){
        btnRunPro();
        return cmd_op;
    }
    if(Qlist[0] == "LOAD"){
        load();
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
//处理不需要行号的程序语句
bool MainWindow::ProcessImdOp(QString cmd)
{
    bool cmd_op = true;
    if(cmd.isEmpty()) return cmd_op;
    QStringList Qlist = cmd.split(' ',QString::SkipEmptyParts);
    try {
        QStringList Qlist = cmd.split(' ',QString::SkipEmptyParts);
        QString contxt = "";
        for(int i = 1;i<Qlist.length();i++){
            contxt += Qlist[i];
        }
        if(Qlist[0] == "LET"){
            QStringList tokens;
            tokens.clear();
            tokens = Tokenizer->ToTokens(contxt);
            exp *val;
            val = Parser->ToTree(tokens);
            val->eval(Vartable);
            return true;
        }
        else if(Qlist[0] == "PRINT"){
            QStringList tokens;
            tokens.clear();
            tokens = Tokenizer->ToTokens(contxt);
            exp *val;
            val = Parser->ToTree(tokens);
            int _val = val->eval(Vartable);
            ui->textBrowser->append(QString::number(_val,10));
            return true;
        }
        else if(Qlist[0] == "INPUT"){
            ui->cmdLineEdit->insert("?");
            InputVar = contxt;
            WaitInputLine = pro->cur_it->first;
            WaitInput = true;
            return true;
        }
    } catch (char const *e) {
        QString t = "";
        t += " ";
        t += QString(e);
        ui->textBrowser->append(t);
        return true;
    }
    catch (QString e) {
        QString t = "";
        t += " ";
        t += e;
        ui->textBrowser->append(t);
        return true;
    }
    cmd_op = false;
    return cmd_op;
}

//运行程序
void MainWindow::RunPro(evalstate &Vartable,int beginLine)
{
    pro->cur_it = pro->ProGramList.begin();
    if(beginLine != -1){
        pro->cur_it = pro->ProGramList.find(beginLine);
        pro->cur_it++;
    }
    for(; pro->cur_it != pro->ProGramList.end();pro->cur_it++){
        try {
            if(pro->cur_it->second.type() == END){
                break;
            }
            else if(pro->cur_it->second.type() == REM){
                continue;
            }
            else if(pro->cur_it->second.type() == LET){
                QString contxt = pro->cur_it->second.ConText;
                QStringList tokens;
                tokens.clear();
                tokens = Tokenizer->ToTokens(contxt);
                exp *val;
                val = Parser->ToTree(tokens);
                val->eval(Vartable);
            }
            else if(pro->cur_it->second.type() == PRINT){
                QString contxt = pro->cur_it->second.ConText;
                QStringList tokens;
                tokens.clear();
                tokens = Tokenizer->ToTokens(contxt);
                exp *val;
                val = Parser->ToTree(tokens);
                int _val = val->eval(Vartable);
                ui->textBrowser->append(QString::number(_val,10));
            }
            else if(pro->cur_it->second.type() == INPUT){
                ui->cmdLineEdit->insert("?");
                InputVar = pro->cur_it->second.ConText;
                WaitInputLine = pro->cur_it->first;
                WaitInput = true;
                return;
            }
            else if(pro->cur_it->second.type() == IF){
                QString contxt = pro->cur_it->second.ConText;
                QStringList Iflist = contxt.split(' ',QString::SkipEmptyParts);
                QString if_op = "";
                for(int i = 2;i<Iflist.length();i++){
                    if(Iflist[i] == "THEN")
                        break;
                    else {
                        if_op += Iflist[i];
                    }
                }
                bool ok = ifCondition(if_op);
                if(ok){
                    int j = 0;
                    for(j = 0;j < Iflist.length();j++){
                        if(Iflist[j] == "THEN"){
                            break;
                        }
                    }
                    if(j == Iflist.length()-1)
                    {
                        QString t = "";
                        t += QString::number(pro->cur_it->first);
                        t += " ";
                        t += "No linenumber is input!";
                     }
                    int desnum = Iflist[j+1].toInt();
                    map<int,statement>::iterator it;
                    it = pro->ProGramList.find(desnum);
                    if(it != pro->ProGramList.end()){
                        it --;
                        pro->cur_it = it;
                    }
                    else {
                        throw("THEN Line error");
                    }
                }
            }
            else if(pro->cur_it->second.type() == GOTO){
                map<int,statement>::iterator it;
                QString contxt = pro->cur_it->second.ConText;
                it = pro->ProGramList.find(contxt.toInt());
                if(it != pro->ProGramList.end()){
                    it --;
                    pro->cur_it = it;
                }
                else {
                    throw("GOTO Line error");
                }
            }
            else {
                QString t = "";
                t += QString::number(pro->cur_it->first);
                t += " ";
                t += "The statemenr is invalid!";
                ui->textBrowser->append(t);
                return;
            }
        } catch (char const *e) {
            QString t = "";
            t += QString::number(pro->cur_it->first);
            t += " ";
            t += QString(e);
            ui->textBrowser->append(t);
            continue;
        }
        catch (QString e) {
            QString t = "";
            t += QString::number(pro->cur_it->first);
            t += " ";
            t += e;
            ui->textBrowser->append(t);
            continue;
        }
    }
    return;
}

void MainWindow::on_cmdLineEdit_editingFinished()
{
    QString cmd = ui->cmdLineEdit->text();
    ui->cmdLineEdit->setText("");
    ui->CodeDisplay->append(cmd);
}
//删除CLEAR功能
void MainWindow::clearall()
{
    pro->clear();
    delete pro;
    pro = new program();
    Vartable.clear();
    ui->CodeDisplay->clear();
    ui->treeDisplay->clear();
    ui->textBrowser->clear();
    pro->clear();

}

//命令行
void MainWindow::codeLineEdit_return()
{
    try {
        QString input = ui->cmdLineEdit->text();
        ui->cmdLineEdit->clear();
        if(WaitInput){
            QString inputs ="";
            WaitInput = false;
            ProcessInput(input,WaitInputLine,InputVar);
            return;
        }
        bool ok;
        input.toInt(&ok);
        if(ok){
            pro->deleteStatement(input.toInt());
            ui->CodeDisplay->clear();
            map<int,statement>::iterator it;
            for(it = pro->ProGramList.begin();it != pro->ProGramList.end();it++){
                ui->CodeDisplay->append(it->second.input);
            }
            return;
        }
        bool cmd_op = ProcessCmd(input);
        bool Imd_op = ProcessImdOp(input);
        if(!cmd_op&&!Imd_op){
            pro->ProcessState(input);
            ui->CodeDisplay->clear();
            map<int,statement>::iterator it;
            for(it = pro->ProGramList.begin();it != pro->ProGramList.end();it++){
                ui->CodeDisplay->append(it->second.input);
            }
        }
    } catch (QString error) {
        QString Tips = "";
        Tips += " ";
        Tips += error;
        ui->textBrowser->append(Tips);
    }catch(char const *e){
        QString Tips = "";
        Tips += " ";
        Tips += (QString)e;
        ui->textBrowser->append(Tips);
    }
}
//load按钮
void MainWindow::load()
{
    clearall();
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择日志文件"),"",tr("TXT(*.txt)"));
    if (fileName.isEmpty())     //如果未选择文件便确认，即返回
            return;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
        QTextStream in(&file);  //用文件构造流
        line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())//字符串有内容
        {
            ProcessLine(line);
            line=in.readLine();//循环读取下行
        }
    }
    file.close();
    map<int,statement>::iterator it;
    for(it = pro->ProGramList.begin();it != pro->ProGramList.end();it++){
        ui->CodeDisplay->append(it->second.input);
    }
}
//按下RUN后程序
void MainWindow::btnRunPro()
{
    ui->treeDisplay->clear();
    ui->textBrowser->clear();
    PrintTree();
    RunPro(Vartable);
}
//画出语法树
void MainWindow::PrintTree()
{
    map<int,statement>::iterator it;
    for(it = pro->ProGramList.begin(); it != pro->ProGramList.end();it++){
        try {
            if(it->second.type() == REM){
                QString t = "";
                t += QString::number(it->first,10);
                t += " ";
                t += "REM";
                ui->treeDisplay->append(t);
                ui->treeDisplay->append(it->second.ConText);
            }
            else if(it->second.type() == LET){
                QString contxt = it->second.ConText;
                QStringList tokens;
                tokens.clear();
                tokens = Tokenizer->ToTokens(contxt);
                exp *val;
                val = Parser->ToTree(tokens);
                val->eval(Vartable);
                floorPrint(LET,val,it->first);
            }
            else if(it->second.type() == PRINT){
                QString contxt = it->second.ConText;
                QStringList tokens;
                tokens.clear();
                tokens = Tokenizer->ToTokens(contxt);
                exp *val;
                val = Parser->ToTree(tokens);
                val->eval(Vartable);
                floorPrint(PRINT,val,it->first);
            }
            else if(it->second.type() == INPUT){
                QString t = "";
                t += QString::number(it->first,10);
                t += " ";
                t += "INPUT";
                ui->treeDisplay->append(t);
                QString contxt = it->second.ConText;
                ui->treeDisplay->append("     "+contxt);
            }
            else if(it->second.type() == IF){
                QString t = "";
                t += QString::number(it->first,10);
                t += " ";
                t += "IF THEN";
                ui->treeDisplay->append(t);
                QString contxt = it->second.ConText;
                QStringList Iflist = contxt.split(' ',QString::SkipEmptyParts);
                ui->treeDisplay->append("     "+Iflist[2]);
                ui->treeDisplay->append("     "+Iflist[3]);
                ui->treeDisplay->append("     "+Iflist[4]);
                ui->treeDisplay->append("     "+Iflist[6]);
            }
            else if(it->second.type() == GOTO){
                QString contxt = it->second.ConText;
                bool ok;
                contxt.toInt(&ok);
                if(ok){
                    QString t = "";
                    t += QString::number(it->first,10);
                    t += " ";
                    t += "GOTO";
                    ui->treeDisplay->append(t);
                    ui->treeDisplay->append("     "+contxt);
                }
                else throw "LineNum error";
            }
            else if(it->second.type() == END){
                QString t = "";
                t += QString::number(it->first,10);
                t += " ";
                t += "END";
                ui->treeDisplay->append(t);
            }
        } catch (char const *e) {
            QString t = "";
            t += QString::number(it->first);
            t += " ";
            t += QString(e);
            ui->treeDisplay->append(t);
            continue;
        } catch (QString e) {
                    QString t = "";
                    t += QString::number(it->first);
                    t += " ";
                    t += "Error";
                    ui->treeDisplay->append(t);
                    continue;
                }
    }
}
//通过层序遍历来画出语法图
void MainWindow::floorPrint(StmtType type, exp *val,int Line)
{
    bool first = true;
    std::queue<exp*> q;
    if(type == LET){
        QString t = "";
        t += QString::number(Line,10);
        t += " ";
        t += "LET =";
        ui->treeDisplay->append(t);
    }
    else if(type == PRINT){
        QString t = "";
        t += QString::number(Line,10);
        t += " ";
        t += "PRINT";
        ui->treeDisplay->append(t);
    }
    QString Treel = "      ";
    if(val->type() == COMPOUND){
        exp* p = val;
        q.push(p);
        q.push(NULL);
        while(!q.empty()){
            exp* node = q.front();
            q.pop();
            if(node == NULL){
                if(q.empty())
                    break;
                Treel += " ";
                q.push(NULL);
                continue;
            }
            if(type == LET &&first){
                first = false;
            }
            else {
                QString tip = Treel;
                tip+=node->op;
                ui->treeDisplay->append(tip);
            }
            if(node->lhs!=NULL){
                q.push(node->lhs);
            }
            if(node->rhs!=NULL){
                q.push(node->rhs);
            }
        }
    }
    else {
        QString tip = "    ";
        tip += val->op;
        ui->treeDisplay->append(tip);
    }
}

void MainWindow::ProcessLine(QString input)
{

    bool Imd_op = ProcessImdOp(input);
    if(!Imd_op){
        pro->ProcessState(input);
    }
}

void MainWindow::ProcessInput(QString input, int Line, QString InputVar)
{
    QString val = "";
    for(int i = 1;i < input.length();i++){
        val += input[i];
    }
    bool ok;
    val.toInt(&ok);
    if(ok){
        Vartable.inputValue(InputVar,val.toInt());
        RunPro(Vartable,Line);
    }
    else throw "input error";
}

bool MainWindow::ifCondition(QString str)
{
    if(str.contains("="))
       {
           QList<QString> ifstrs = str.split('=',QString::SkipEmptyParts);

           QList<QString>tokensleft;
           tokensleft.clear();
           tokensleft = Tokenizer->ToTokens(ifstrs[0]);
           exp* valleft;

           try {
               valleft = Parser->ToTree(tokensleft);                   //化成表达树
           } catch (QString errorTips) {
               QString Tips = "";
               Tips += " ";
               Tips += errorTips;
           }
           int numleft ;
           QString err;
           try {
               numleft = valleft->eval(Vartable);                                        //进行求值
           } catch (QString errorTips) {
               err = errorTips;
               throw err;
           }

           QList<QString>tokensright;
           tokensright.clear();
           tokensright = Tokenizer->ToTokens(ifstrs[1]);
           exp* valright;

           try {
               valright = Parser->ToTree(tokensright);                   //化成表达树
           } catch (QString errorTips) {
               QString Tips = "";
               Tips += " ";
               Tips += errorTips;
           }
           int numright ;                             //进行求值
           QString err2;
           try {
               numright = valright->eval(Vartable);                                        //进行求值
           } catch (QString errorTips) {
               err = errorTips;
               throw err;
           }

           if(numleft == numright)
           {
               return true;
           }
           else {
               return false;
           }
       }
       else if (str.contains(">")) {
           QList<QString> ifstrs = str.split('>',QString::SkipEmptyParts);
           QList<QString> tokensleft;
           tokensleft.clear();
           tokensleft = Tokenizer->ToTokens(ifstrs[0]);
           exp * valleft;

           try {
               valleft = Parser->ToTree(tokensleft);                   //化成表达树
           } catch (QString errorTips) {
               QString Tips = "";
               Tips += " ";
               Tips += errorTips;
               ui->textBrowser->append(Tips);
           }
           int numleft ;
           QString err;
           try {
               numleft = valleft->eval(Vartable);                                        //进行求值
           } catch (QString errorTips) {
               err = errorTips;
               throw err;
           }

           QList<QString>tokensright;
           tokensright.clear();
           tokensright = Tokenizer->ToTokens(ifstrs[1]);
           exp * valright;

           try {
               valright = Parser->ToTree(tokensright);                   //化成表达树
           } catch (QString errorTips) {
               QString Tips = "";
               Tips += " ";
               Tips += errorTips;
               ui->textBrowser->append(Tips);
           }
           int numright ;                             //进行求值
           QString err2;
           try {
               numright = valright->eval(Vartable);                                        //进行求值
           } catch (QString errorTips) {
               err = errorTips;
               throw err;
           }

           if(numleft > numright)
           {
               return true;
           }
           else {
               return false;
           }
       }
       else if (str.contains("<")) {
           QList<QString> ifstrs = str.split('<',QString::SkipEmptyParts);
           QList<QString>tokensleft;
           tokensleft.clear();
           tokensleft = Tokenizer->ToTokens(ifstrs[0]);
           exp *valleft;

           try {
               valleft = Parser->ToTree(tokensleft);                   //化成表达树
           } catch (QString errorTips) {
               QString Tips = "";
               Tips += " ";
               Tips += errorTips;
               ui->textBrowser->append(Tips);
           }
           int numleft ;
           QString err;
           try {
               numleft = valleft->eval(Vartable);                                        //进行求值
           } catch (QString errorTips) {
               err = errorTips;
               throw err;
           }

           QList<QString>tokensright;
           tokensright.clear();
           tokensright = Tokenizer->ToTokens(ifstrs[1]);
           exp *valright;

           try {
               valright = Parser->ToTree(tokensright);                   //化成表达树
           } catch (QString errorTips) {
               QString Tips = "";
               Tips += " ";
               Tips += errorTips;
               ui->textBrowser->append(Tips);
           }
           int numright ;                             //进行求值
           QString err2;
           try {
               numright = valright->eval(Vartable);                                        //进行求值
           } catch (QString errorTips) {
               err = errorTips;
               throw err;
           }

           if(numleft < numright)
           {
               return true;
           }
           else {
               return false;
           }


       }
       else {
           QList<QString> ifstrs;
       }
       return false;
}
