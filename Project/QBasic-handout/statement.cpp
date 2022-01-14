#include "statement.h"

statement::statement()
{
}

statement::statement(QString contxt)
{
    GetContxt(contxt);
}

StmtType statement::type()
{
    return _type;
}

//处理input数据
void statement::GetContxt(QString contxt)
{
    input = contxt;
    if(_type==IF||_type == REM){
        ConText = contxt;
        return;
    }
    QStringList Qlist = contxt.split(' ',QString::SkipEmptyParts);
    QString exp = "";
    for(int i = 2;i<Qlist.length();i++){
        exp += Qlist[i];
    }
    ConText = exp;
    return;
}


