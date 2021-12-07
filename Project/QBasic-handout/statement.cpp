#include "statement.h"

statement::statement()
{
    next = nullptr;
}

statement::~statement()
{

}

void RemStmt::run()
{
    return;
}

void LetStmt::run()
{

}
