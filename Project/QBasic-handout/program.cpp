#include "program.h"

program::program()
{
    head->next = nullptr;
    curLine = 0;
}

void program::clear()
{

}

statement* program::move(int LineNum)
{
    int i = LineNum;
    statement *tmp = head;
    while (tmp->next!=nullptr&&i-->=0)
        tmp = tmp->next;
    return tmp;
}

void program::ProcessState(QString StmtOp)
{
    QStringList Qlist = StmtOp.split(' ',QString::SkipEmptyParts);
    bool isDigital=QString(Qlist[0]).contains(QRegExp("^\\d+$"));
    if(isDigital){
        int Line = Qlist[0].toInt();
        if(Line <= 0 && Line >= 1000000){
            Line = -1;
        }
        statement *stmt;
        if(Qlist[1] == "REM"){
            stmt = new RemStmt;
            stmt->LineNum = Line;
            insertState(Line,stmt);
        }
        if(Qlist[1] == "LET"){

        }
        if(Qlist[1] == "PRINT"){

        }
        if(Qlist[1] == "INPUT"){

        }
        if(Qlist[1] == "GOTO"){

        }
        if(Qlist[1] == "IF"){

        }
        if(Qlist[1] == "END"){

        }
    }
}

void program::insertState(int LineNum, statement *)
{

}

