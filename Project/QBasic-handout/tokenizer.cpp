#include "tokenizer.h"

tokenizer::tokenizer()
{

}

QStringList tokenizer::ToTokens(QString contxt)
{
    contxt.remove(QChar(' '), Qt::CaseInsensitive);
}
