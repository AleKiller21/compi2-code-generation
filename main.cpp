#include "ast/ast.h"
#include "register_manager/register_manager.h"
#include <iostream>

int yyparse();

using namespace std;

list_expression exprs;
register_manager reg_manager;

int main()
{
    yyparse();
    cout << exprs.generate_code() << endl;
}