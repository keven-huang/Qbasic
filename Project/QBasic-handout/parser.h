#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "evalstate.h"
#include "exp.h"
#include "QStringList"
#include <stack>

using namespace std;

class parser
{
public:
    parser();
    exp* ToTree(QStringList tokens);

private:
    stack<QString> Operators;
    stack<exp*> Operands;
    int GetPriority(QString ope);
    bool isConstantExp(QString var);
    bool isIdentifierExp(QString var);
    bool isCompundExp(QString var);

    bool IsMulDiv(QString exp); //是不是*/
    bool IsAddSub(QString exp); //是不是+-
    bool IsEqu(QString exp);    //是不是=
    bool IsLeftpar(QString exp); //是不是 (
    bool IsRightpar(QString exp); //是不是 )
};

#endif // PARSER_H
