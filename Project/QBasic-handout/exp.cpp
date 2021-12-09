#include "exp.h"

exp::exp()
{

}

int ConstantExp::eval(evalstate &context)
{
    return value;
}

int IdentifierExp::eval(evalstate &context)
{
    if (!context.isDefined(name))
        throw(name + " is undefined");
    return context.getValue(name);

}
