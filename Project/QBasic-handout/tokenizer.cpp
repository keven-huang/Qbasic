#include "tokenizer.h"

tokenizer::tokenizer()
{

}

QStringList tokenizer::ToTokens(QString contxt)
{   
    Tokens.clear();
    contxt.remove(QChar(' '), Qt::CaseInsensitive);
    int j = 0;
    for(int i = 0;i<contxt.length();i++){
        if(contxt[i].isLetterOrNumber()){
            continue;
        }
        if(isOp(contxt[i])){
           if( i > j ){
           QString val = contxt.mid(j,i - j);
           if(!isLegal(val))
               throw "NameError";
           Tokens.append(val);
           if(contxt[i] == '*' && contxt[i + 1] == '*'){
               Tokens.append("**");
               i = i + 1;
           }
           else
               Tokens.append(QString(contxt[i]));
               j = i + 1;
           }
           else if(i > 0 && i == j ){
               if(contxt[i -1] == ")"){
                   if(contxt[i] != "("&&contxt[i] != ")"){
                       Tokens.append(QString(contxt[i]));
                       j = j + 1;
                       continue;
                   }
                   else throw "synatax error";
               }
               if(contxt[i] == "-"||contxt[i] == "+"){
                   if(contxt[i-1] == "="||contxt[i - 1] == "("){
                       continue;
                   }
                   else throw "syntax error";
               }
               else if(contxt[i] == "("){
                   Tokens.append(QString(contxt[i]));
                   j = j + 1;
               }
               else throw "syntax error";
           }
           else if(i == 0 && contxt[i] == "("){
               Tokens.append(QString(contxt[i]));
               j = j + 1;
           }
           else throw "syntax error";
        }
    }
    QString lastStr = contxt.mid(j);
    Tokens.append(lastStr);
    return Tokens;
}

bool tokenizer::isOp(QCharRef sym)
{
    if(sym == '+'||sym == '-'||sym == '*'||sym == '/'||sym == '('||sym == ')'||sym == "="){
        return true;
    }
    else return false;
}

bool tokenizer::isLegal(QString val)
{
    if(val[0].isLetter()||val[0] == '_')
        return true;
    else{
        bool ok;
        val.toInt(&ok);
        return ok;
    }
}

