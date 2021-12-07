#ifndef EVALSTATE_H
#define EVALSTATE_H
#include<map>
#include<cstring>
using namespace std;
class evalstate
{
public:
    evalstate();
    bool isDefine(string sym);
    int getValue(string name);
    void inputValue(string name,int val);
    void clear();
private:
    map<string,int> SymTable;
};

#endif // EVALSTATE_H
