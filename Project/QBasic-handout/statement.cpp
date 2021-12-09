#include "statement.h"

statement::statement()
{
}

statement::statement(QString contxt)
{
    GetContxt(contxt);
}

statement::~statement()
{
}

void statement::GetContxt(QString contxt)
{

    QStringList Qlist = contxt.split(' ',QString::SkipEmptyParts);
    QString exp = "";
    for(int i = 2;i<contxt.length();++i){
        exp += Qlist[i];
    }
    ConText = exp;
    return;
}


int GoToStmt::return2Program()
{
    bool isDigital=QString(ConText).contains(QRegExp("^\\d+$"));
    if(isDigital){
        int Go2Line = ConText.toInt();
        if(Go2Line < 0 || Go2Line> 100000){
            return -1;
        }
        return Go2Line;
    }
    else{
        return -1;
    }
}

void ENDStmt::run()
{
    return;
}
