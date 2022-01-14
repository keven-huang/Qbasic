#include "program.h"

program::program()
{
    cur_it = ProGramList.begin();
    curLine = 0;
}

void program::clear()
{
    ProGramList.clear();
}


void program::deleteStatement(int LineNum)
{
    if(ProGramList.erase(LineNum)){
    }
    else throw "LineNum not exist";
}

//处理每一句话
void program::ProcessState(QString StmtOp)
{
    QStringList Qlist = StmtOp.split(' ',QString::SkipEmptyParts);
    bool isDigital=QString(Qlist[0]).contains(QRegExp("^\\d+$"));
    if(isDigital){
        int Line = Qlist[0].toInt();
        if(Line <= 0 || Line >= 1000000){
            throw "LineError";
        }
        statement *stmt;
        if(Qlist[1] == "REM"){
            stmt = new statement();
            stmt->_type = REM;
            stmt->GetContxt(StmtOp);
            stmt->LineNum = Line;
            insertState(Line,stmt);
        }
        else if(Qlist[1] == "LET"){
            stmt = new statement();
            stmt->_type = LET;
            stmt->GetContxt(StmtOp);
            stmt->LineNum = Line;
            insertState(Line,stmt);
        }
        else if(Qlist[1] == "PRINT"){
            stmt = new statement();
            stmt->_type = PRINT;
            stmt->GetContxt(StmtOp);
            stmt->LineNum = Line;
            insertState(Line,stmt);
        }
        else if(Qlist[1] == "INPUT"){
            stmt = new statement();
            stmt->_type = INPUT;
            stmt->GetContxt(StmtOp);
            stmt->LineNum = Line;
            insertState(Line,stmt);
        }
        else if(Qlist[1] == "GOTO"){
            stmt = new statement();
            stmt->_type = GOTO;
            stmt->GetContxt(StmtOp);
            stmt->LineNum = Line;
            insertState(Line,stmt);
        }
        else if(Qlist[1] == "IF"){
            stmt = new statement();
            stmt->_type = IF;
            stmt->GetContxt(StmtOp);
            stmt->LineNum = Line;
            insertState(Line,stmt);
        }
        else if(Qlist[1] == "END"){
            stmt = new statement();
            stmt->_type = END;
            stmt->GetContxt(StmtOp);
            stmt->LineNum = Line;
            insertState(Line,stmt);
        }
    }
    else{
        throw "input error!";
    }
}

void program::insertState(int LineNum, statement *a)
{
    ProGramList[LineNum] = *a;
    return;
//    if(ProGramList.find(LineNum) != ProGramList.end()){
//        ProGramList.insert(pair<int,statement>(LineNum,*a));
//        return;
//    }
//    else{
//        ProGramList[LineNum] = *a;
//        return;
//    }
}

