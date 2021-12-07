#ifndef PROGRAM_H
#define PROGRAM_H

#include<QStringList>
#include <QString>
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
    statement* move(int LineNum);
    void ProcessState(QString statement);
    void insertState(int LineNum,statement *);
private:
    int curLine;
    statement* head;
};

#endif // PROGRAM_H
