#ifndef PROGRAM_H
#define PROGRAM_H

#include<QStringList>
#include <QString>
#include<map>
#include "statement.h"

using namespace std;

class program
{
public:
    program();
    void clear();
    void load();
    void run();
    void deleteStatement(int LineNum);
    void ProcessState(QString statement);
    void insertState(int LineNum,statement *);
private:
    int curLine;
    map<int,statement>::iterator cur_it;
    map<int,statement> ProGramList;
};

#endif // PROGRAM_H
