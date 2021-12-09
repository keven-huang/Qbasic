#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<QStringList>
using namespace std;
class tokenizer
{
public:
    tokenizer();
    QStringList ToTokens(QString contxt);
};

#endif // TOKENIZER_H
