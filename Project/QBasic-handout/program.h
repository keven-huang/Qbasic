#ifndef PROGRAM_H
#define PROGRAM_H

#include<QStringList>
#include <QString>
#include<map>
#include "statement.h"

using namespace std;

class program
{
    friend class mainwindow;
public:
    program();
    void clear();
    void deleteStatement(int LineNum);
    void ProcessState(QString statement);
    void insertState(int LineNum,statement *);
    int curLine;
    map<int,statement>::iterator cur_it;
    map<int,statement> ProGramList;
};

#endif // PROGRAM_H
