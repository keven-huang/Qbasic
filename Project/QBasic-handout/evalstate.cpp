#include "evalstate.h"

using namespace std;
evalstate::evalstate()
{

}

bool evalstate::isDefined(QString sym)
{
    map<QString,int>::iterator it = SymTable.find(sym);
    if(it != SymTable.end())
        return true;
    else return false;
}

int evalstate::getValue(QString name)
{
    return SymTable[name];
}

void evalstate::inputValue(QString name, int val)
{
    SymTable[name] = val;
    return;
}

void evalstate::clear()
{
    SymTable.clear();
}

