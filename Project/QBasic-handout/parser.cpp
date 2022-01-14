#include "parser.h"

parser::parser()
{

}

exp *parser::ToTree(QStringList tokens)
{

    for(int i = 0;i<tokens.length();++i)
    {
        if(tokens[i] == "")
        {
            tokens.removeAt(i);
        }
    }
    //-处理
    if(tokens[0] == "-")
    {
            tokens.insert(0,"0");
    }
    //-处理
    for(int i = 0;i<tokens.length();++i)
    {
        int j = i+1;
        if(tokens[i] == "(" && tokens[j] == "-")
            tokens.insert(j,"0");
    }

    QString tokensstr = "";
    for(int i = 0;i<tokens.length();++i)
    {
        if(tokens[i] == "+"||tokens[i] == "-"||tokens[i] == "*"||tokens[i] == "/"||tokens[i] == "**"||tokens[i] == "=")
        {
            tokensstr += "+";
        }
        else {
            tokensstr += tokens[i];
        }
    }

    if(tokensstr.contains("++"))
    {
        throw ("illegal");
    }
    exp* root = nullptr;
    QString tmp;
    for(int i = 0;i < tokens.length();i++){
        tmp = tokens[i];
        if(isConstantExp(tmp)){
            ConstantExp * cons = new ConstantExp(tmp.toInt());
            Operands.push(cons);
        }
        if(isIdentifierExp(tmp)){
            IdentifierExp * iden = new IdentifierExp(tmp);
            Operands.push(iden);
        }
        if(isCompundExp(tmp)){
            if(IsLeftpar(tmp)){
                Operators.push(tmp);
            }
            else if(IsRightpar(tmp)){
                while(Operators.top() != "("){
                    QString top = Operators.top();
                    Operators.pop();
                    exp* left;
                    exp* right;
                    if(!Operands.empty()){
                        right = Operands.top();
                        Operands.pop();
                    }
                    else
                        right = nullptr;
                    if(!Operands.empty()){
                        left = Operands.top();
                        Operands.pop();
                    }
                    else
                        left = nullptr;
                    CompoundExp* comp = new CompoundExp(top,left,right);
                    Operands.push(comp);
                }
                Operators.pop();                  //去掉前括号"("
            }
            else{
                if(Operators.empty())
                    Operators.push(tmp);
                else{
                    while(true){
                        int curprior = GetPriority(tmp);
                        int topprior = Operators.empty()?-1:GetPriority(Operators.top());
                        if(curprior > topprior){
                            Operators.push(tmp);
                            break;
                        }
                        else if(curprior == topprior && curprior == 4){
                                exp* left;
                                exp* right;
                                if(!Operands.empty()){
                                    right = Operands.top();
                                    Operands.pop();
                                }
                                else
                                    right = nullptr;
                                if(!Operands.empty()){
                                    left = Operands.top();
                                    Operands.pop();
                                }
                                else
                                    left = nullptr;
                                CompoundExp *comp = new CompoundExp(tmp,left,right);
                                Operands.push(comp);
                        }
                        else {
                            QString top = Operators.top();
                            Operators.pop();
                            exp* left;
                            exp* right;
                            if(!Operands.empty()){
                                right = Operands.top();
                                Operands.pop();
                            }
                            else
                                right = nullptr;
                            if(!Operands.empty()){
                                left = Operands.top();
                                Operands.pop();
                            }
                            else
                                left = nullptr;
                            CompoundExp *comp = new CompoundExp(top,left,right);
                            Operands.push(comp);
                        }
                    }
                }
            }
        }
    }
    while(!Operators.empty()){
        QString top = Operators.top();
        Operators.pop();
        exp* left;
        exp* right;
        if(!Operands.empty()){
            right = Operands.top();
            Operands.pop();
        }
        else
            right = nullptr;
        if(!Operands.empty()){
            left = Operands.top();
            Operands.pop();
        }
        else
            left = nullptr;
        CompoundExp* comp = new CompoundExp(top,left,right);
        Operands.push(comp);
    }
    root = Operands.top();
    return root;
}

int parser::GetPriority(QString ope)
{
    if (ope =="="||ope == "(")
        return 1;
    else if (ope == "+"||ope =="-") {
        return 2;
    }
    else if (ope == "*" || ope =="/") {
        return 3;
    }
    else if(ope == "**")
        return 4;
    return 0;
}

bool parser::isConstantExp(QString var)
{
    bool ok;
    var.toInt(&ok);
    return ok;
}

bool parser::isIdentifierExp(QString var)
{
    if(var[0]>="A" && var[0]<="Z")
        return true;
    if(var[0]>="a" && var[0]<="z")
        return true;
    if(var[0] == "_")
        return true;
    return false;
}

bool parser::isCompundExp(QString exp)
{
    if(exp == "+" || exp == "-" || exp == "*" || exp == "/" || exp == "(" || exp == ")" || exp == "="||exp == "**"){
        return true;
    }
    else return false;
}

bool parser::IsMulDiv(QString exp)
{
    if(exp == "*" || exp == "/")
           return true;
    return false;
}

bool parser::IsAddSub(QString exp)
{
    if(exp == "+" || exp == "-")
        return true;
    return false;
}

bool parser::IsEqu(QString exp)
{
    if (exp =="=")
        return true;
    return false;
}

bool parser::IsLeftpar(QString exp)
{
    if(exp == "(")
        return  true;
    else return false;
}

bool parser::IsRightpar(QString exp)
{
    if(exp == ")")
        return true;
    return false;
}


