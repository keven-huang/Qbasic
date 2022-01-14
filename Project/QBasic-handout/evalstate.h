#ifndef EVALSTATE_H
#define EVALSTATE_H
#include<map>
#include<cstring>
#include<QString>
using namespace std;
class evalstate
{
public:
    evalstate();
    bool isDefined(QString sym);
    int getValue(QString name);
    void inputValue(QString name,int val);
    void clear();
private:
    map<QString,int> SymTable;
};

#endif // EVALSTATE_H
