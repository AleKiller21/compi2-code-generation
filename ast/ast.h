#ifndef AST
#define AST

#include <string>
#include <list>
#include "../register_manager/register_manager.h"

using namespace std;

extern register_manager reg_manager;

struct asm_code
{
    string code;
    string place;
};

class expression
{
public:
    virtual asm_code generate_code() = 0;
};

class list_expression
{
public:
    list<expression*> exprs;
    void add_expression(expression *expr);
    string generate_code();
};

class binary_expression : public expression
{
public:
    expression *expr1, *expr2;

    binary_expression(expression *expr1, expression *expr2)
    {
        this->expr1 = expr1;
        this->expr2 = expr2;
    }
};

class mult_expression : public binary_expression
{
public:
    mult_expression(expression *expr1, expression *expr2) : binary_expression(expr1, expr2) {}
    asm_code generate_code();
};

class div_expression : public binary_expression
{
public:
    div_expression(expression *expr1, expression *expr2) : binary_expression(expr1, expr2) {}
    asm_code generate_code();
};

class sum_expression : public binary_expression
{
public:
    sum_expression(expression *expr1, expression *expr2) : binary_expression(expr1, expr2) {}
    asm_code generate_code();
};

class sub_expression : public binary_expression
{
public:
    sub_expression(expression *expr1, expression *expr2) : binary_expression(expr1, expr2) {}
    asm_code generate_code();
};

class id_expression : public expression
{
public:
    string id;
    id_expression(string *id) { this->id = *id; delete id; }
    asm_code generate_code();
};

class num_expression : public expression
{
public:
    int value;
    num_expression(int value) { this->value = value; }
    asm_code generate_code();
};

#endif