#ifndef EXP_H
#define EXP_H

#include<QString>
#include"evalstate.h"
using namespace std;

enum ExpressionType { CONSTANT, IDENTIFIER, COMPOUND };
//分为三个子类，CONSTANT，IDENTIFIER，COMPUND
class exp{
public:
    exp();
    virtual ~exp();
    virtual int eval(evalstate & context) = 0;
    virtual ExpressionType type() = 0;
    virtual QString getIdentifierName() = 0;

    QString op;
    exp *lhs, *rhs;

};

class ConstantExp: public exp {

public:

   ConstantExp(int val);
   ~ConstantExp();
   virtual int eval(evalstate & context);
   virtual ExpressionType type(){return CONSTANT;}
   virtual QString getIdentifierName();
private:
   int value;

};

class IdentifierExp: public exp {

public:

   IdentifierExp(QString name);
   ~IdentifierExp();
   virtual int eval(evalstate & context);
   virtual ExpressionType type(){return IDENTIFIER;}
   virtual QString getIdentifierName();

private:

   QString name;

};

class CompoundExp: public exp {

public:

   CompoundExp(QString op, exp *lhs, exp *rhs);
   ~CompoundExp();
   virtual int eval(evalstate & context);
   virtual ExpressionType type(){return COMPOUND;}
   virtual QString getIdentifierName();
};


#endif // EXP_H
