#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<QStringList>
#include"evalstate.h"
using namespace std;
class tokenizer
{
public:
    tokenizer();
    QStringList ToTokens(QString contxt);
    bool isOp(QCharRef sym);
    bool isLegal(QString val);
private:
    QStringList Tokens;
};

#endif // TOKENIZER_H
