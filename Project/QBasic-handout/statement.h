#ifndef STATEMENT_H
#define STATEMENT_H

#include<QString>
#include<QStringList>
#include"tokenizer.h"
#include"exp.h"
using namespace std;

enum StmtType{REM,LET,PRINT,INPUT,GOTO,IF,END};
class statement
{
    friend class program;
public:
    statement();
    statement(QString contxt);
    virtual ~statement();
    virtual StmtType type();
    virtual void run();
    virtual int return2Program();
    void GetContxt(QString contxt);
    int LineNum;
    QString ConText;
};

class RemStmt:public statement{
    virtual StmtType type(){return REM;}
    virtual void run();

};

class LetStmt:public statement{
    virtual StmtType type(){return LET;}
    virtual void run();

};

class PrintStmt:public statement{
    virtual StmtType type(){return PRINT;}
    virtual void run();

};

class InputStmt:public statement{
    virtual StmtType type(){return INPUT;}
    virtual void run();

};

class GoToStmt:public statement{
    virtual StmtType type(){return GOTO;}
    virtual void run();
    virtual int return2Program();
};

class IFStmt:public statement{
    virtual StmtType type(){return IF;}
    virtual void run();

};

class ENDStmt:public statement{
    virtual StmtType type(){return END;}
    virtual void run();

};


#endif // STATEMENT_H
