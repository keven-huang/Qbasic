#include "program.h"

program::program()
{
    curLine = 0;
}

void program::clear()
{
    ProGramList.clear();
}

void program::run()
{
    for(cur_it = ProGramList.begin(); cur_it != ProGramList.end();cur_it++){
        cur_it->second.run();
        if(cur_it->second.type() == GOTO){
            if(cur_it->second.return2Program()!=-1&&ProGramList.find(cur_it->second.return2Program())!=ProGramList.end()){
                cur_it = ProGramList.find(cur_it->second.return2Program());
            }
            else {
                throw("GOTO Line error");
            }
        }
    }
}

void program::deleteStatement(int LineNum)
{

}

void program::ProcessState(QString StmtOp)
{
    QStringList Qlist = StmtOp.split(' ',QString::SkipEmptyParts);
    bool isDigital=QString(Qlist[0]).contains(QRegExp("^\\d+$"));
    if(isDigital){
        int Line = Qlist[0].toInt();
        if(Line <= 0 || Line >= 1000000){
            Line = -1;
        }
        statement *stmt;
        if(Qlist[1] == "REM"){
            stmt = new RemStmt();
            stmt->GetContxt(StmtOp);
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

            insertState(Line,stmt);
        }
        if(Qlist[1] == "IF"){

        }
        if(Qlist[1] == "END"){

        }
    }
}

void program::insertState(int LineNum, statement *a)
{
    if(ProGramList.find(LineNum) != ProGramList.end()){
        ProGramList.insert(pair<int,statement>(LineNum,*a));
        return;
    }
    else{
        ProGramList[LineNum] = *a;
        return;
    }
}

