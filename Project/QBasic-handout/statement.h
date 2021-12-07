#ifndef STATEMENT_H
#define STATEMENT_H

#include<QString>

using namespace std;

enum StmtType{REM,LET,PRINT,INPUT,GOTO,IF,END};
class statement
{
    friend class program;
public:
    statement();
    virtual ~statement();
    virtual StmtType type();
    virtual void run();
private:
    int LineNum;
    QString ConText;
    statement* next;
};

class RemStmt:public statement{
    virtual StmtType type(){return REM;}
    virtual void run();

};

class LetStmt:public statement{
    virtual StmtType type(){return LET;}
    virtual void run();

};
#endif // STATEMENT_H
