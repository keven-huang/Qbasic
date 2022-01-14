#ifndef STATEMENT_H
#define STATEMENT_H

#include<QString>
#include<QStringList>
#include"tokenizer.h"
#include"parser.h"
#include"exp.h"
using namespace std;

enum StmtType{REM,LET,PRINT,INPUT,GOTO,IF,END};
class statement
{
    friend class program;
public:
    statement();
    statement(QString contxt);
    StmtType type();
    void GetContxt(QString contxt);
    int LineNum;
    QString input;
    QString ConText;
    StmtType _type;
};


#endif // STATEMENT_H
