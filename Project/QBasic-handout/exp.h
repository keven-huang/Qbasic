#ifndef EXP_H
#define EXP_H

#include<string>
#include"evalstate.h"
using namespace std;

enum ExpressionType { CONSTANT, IDENTIFIER, COMPOUND };

class exp{
public:
    exp();
    virtual ~exp();
    virtual int eval(evalstate & context) = 0;
    virtual string toString() = 0;
    virtual ExpressionType type() = 0;

    virtual int getConstantValue();
    virtual string getIdentifierName();
    virtual string getOperator();
    virtual exp *getLHS();
    virtual exp *getRHS();

};

class ConstantExp: public exp {

public:

   ConstantExp(int val);

   virtual int eval(evalstate & context);
   virtual std::string toString();
   virtual ExpressionType type(){return CONSTANT;}

   virtual int getConstantValue();

private:
   int value;

};

class IdentifierExp: public exp {

public:

   IdentifierExp(string name);

   virtual int eval(evalstate & context);
   virtual std::string toString();
   virtual ExpressionType type(){return IDENTIFIER;}
   virtual string getIdentifierName();

private:

   std::string name;

};

class CompoundExp: public exp {

public:

   CompoundExp(string op, exp *lhs, exp *rhs);
   virtual ~CompoundExp();

   virtual int eval(evalstate & context);
   virtual std::string toString();
   virtual ExpressionType type(){return COMPOUND;}

   virtual std::string getOperator();
   virtual exp *getLHS();
   virtual exp *getRHS();

private:

   std::string op;
   exp *lhs, *rhs;

};


#endif // EXP_H
