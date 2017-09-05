#include "ast.h"

string list_expression::generate_code()
{
    asm_code cde;
    string result;

    for(list<expression*>::iterator it = exprs.begin(); it != exprs.end(); it++)
    {
        cde = (*it)->generate_code();
        reg_manager.free_register(cde.place);
        result += cde.code + "\n";
    }

    return result;
}

asm_code mult_expression::generate_code()
{
    asm_code cde1 = expr1->generate_code();
    asm_code cde2 = expr2->generate_code();

    string cde = cde1.code + cde2.code;
    reg_manager.free_register(cde1.place);
    reg_manager.free_register(cde2.place);
    string reg = reg_manager.get_free_register();

    cde += "mult " + cde1.place + ", " + cde2.place + "\n";
    cde += "mflo " + reg + "\n";
    return asm_code { cde, reg };
}

asm_code div_expression::generate_code()
{
    asm_code cde1 = expr1->generate_code();
    asm_code cde2 = expr2->generate_code();

    string cde = cde1.code + cde2.code;
    reg_manager.free_register(cde1.place);
    reg_manager.free_register(cde2.place);
    string reg = reg_manager.get_free_register();

    cde += "div " + cde1.place + ", " + cde2.place + "\n";
    cde += "mflo " + reg + "\n";
    return asm_code { cde, reg };
}

asm_code sum_expression::generate_code()
{
    asm_code cde1 = expr1->generate_code();
    asm_code cde2 = expr2->generate_code();

    string cde = cde1.code + cde2.code;
    reg_manager.free_register(cde1.place);
    reg_manager.free_register(cde2.place);

    string reg = reg_manager.get_free_register();
    cde += "add " + reg + ", " + cde1.place + ", " + cde2.place + "\n";
    return asm_code { cde, reg };
}

asm_code sub_expression::generate_code()
{
    asm_code cde1 = expr1->generate_code();
    asm_code cde2 = expr2->generate_code();

    string cde = cde1.code + cde2.code;
    reg_manager.free_register(cde1.place);
    reg_manager.free_register(cde2.place);

    string reg = reg_manager.get_free_register();
    cde += "sub " + reg + ", " + cde1.place + ", " + cde2.place + "\n";
    return asm_code { cde, reg };
}

asm_code id_expression::generate_code()
{
    string reg = reg_manager.get_free_register();
    string cde = "lw " + reg + ", " + id + "\n";
    return asm_code { cde, reg };
}

asm_code num_expression::generate_code()
{
    string reg = reg_manager.get_free_register();
    string cde = "li " + reg + ", " + to_string(value) + "\n";
    return asm_code { cde, reg };
}

void list_expression::add_expression(expression *expr)
{
    exprs.push_back(expr);
}
