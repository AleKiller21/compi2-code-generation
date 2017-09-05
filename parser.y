%code requires
{
    #include "ast/ast.h"
}

%{
    #include <stdio.h>

    int yylex();
    void yyerror(const char* msg);
    extern int yylineno;
    extern char* yytext;

    #define YYERROR_VERBOSE 1
%}

%code
{
    extern list_expression exprs;
}

%union
{
    expression* expr_t;
    list_expression* expr_list;
    string* str_t;
    int num_t;
}

%token <str_t> TK_ID
%token <num_t> TK_NUM

%type <expr_t> expression additive_expression mult_expression primary_expression

%%

source: source '\n' expression { exprs.add_expression($3); }
      | expression { exprs.add_expression($1); }
;

expression: additive_expression { $$ = $1; }
;

additive_expression: additive_expression '+' mult_expression { $$ = new sum_expression($1, $3); }
                   | additive_expression '-' mult_expression { $$ = new sub_expression($1, $3); }
                   | mult_expression { $$ = $1; }
;

mult_expression: mult_expression '*' primary_expression { $$ = new mult_expression($1, $3); }
               | mult_expression '/' primary_expression { $$ = new div_expression($1, $3); }
               | primary_expression { $$ = $1; }
;

primary_expression: TK_ID { $$ = new id_expression($1); }
                  | TK_NUM { $$ = new num_expression($1); }
                  | '(' expression ')' { $$ = $2;}
;

%%

void yyerror(const char* msg)
{
    fprintf(stderr, "Line: %d, error: %s\n", yylineno, msg);
}