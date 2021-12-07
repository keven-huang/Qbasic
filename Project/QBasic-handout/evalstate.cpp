#include "evalstate.h"

using namespace std;
evalstate::evalstate()
{

}

bool evalstate::isDefine(string sym)
{
    map<string,int>::iterator it = SymTable.find(sym);
    if(it != SymTable.end())
        return true;
    else return false;
}

int evalstate::getValue(string name)
{
    return SymTable[name];
}

void evalstate::inputValue(string name, int val)
{
    SymTable[name] = val;
    return;
}

