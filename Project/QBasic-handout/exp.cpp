#include "exp.h"
#include<math.h>
exp::exp()
{

}

exp::~exp()
{

}

ConstantExp::ConstantExp(int val)
{
    op = QString::number(val,10);
    rhs = nullptr;
    lhs = nullptr;
    value = val;
}

ConstantExp::~ConstantExp()
{

}

int ConstantExp::eval(evalstate &context)
{
    return value;
}

QString ConstantExp::getIdentifierName()
{
    return " ";
}


IdentifierExp::IdentifierExp(QString name)
{
    op = name;
    rhs = nullptr;
    lhs = nullptr;
    this->name = name;
}

IdentifierExp::~IdentifierExp()
{

}

int IdentifierExp::eval(evalstate &context)
{
    if (!context.isDefined(name))
        throw(name + " is undefined");
    return context.getValue(name);
}

QString IdentifierExp::getIdentifierName()
{
    return name;
}

CompoundExp::CompoundExp(QString op, exp *lhs, exp *rhs)
{
    this->op = op;
    this->lhs = lhs;
    this->rhs = rhs;
}

CompoundExp::~CompoundExp()
{
    delete rhs;
    delete lhs;
}

int CompoundExp::eval(evalstate & context) {
   int right = rhs->eval(context);
   if (op == "=") {
      context.inputValue(lhs->getIdentifierName(), right);
      return right;
   }
   int left = lhs->eval(context);
   if (op == "+") return left + right;
   if (op == "-") return left - right;
   if (op == "*") return left * right;
   if (op == "/") {
      if (right == 0) throw "Division by 0";
      return left / right;
   }
   if(op == "**") return pow(left,right);
   throw "Illegal operator in expression";
   return 0;
}

QString CompoundExp::getIdentifierName()
{
    return " ";
}


