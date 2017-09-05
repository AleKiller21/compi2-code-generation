%option noyywrap
%option yylineno

%{
    #include <string>
    #include <stdlib.h>
    #include "tokens.h"

    using namespace std;
%}

ID      [a-zA-Z_][a-zA-Z0-9_]*
NUM     [0-9]+

%%

[ \t]               { /* NOTHING */ }
"\n"                { return '\n';}
{ID}                { yylval.str_t = new string(yytext); return TK_ID; }
{NUM}               { yylval.num_t = atoi(yytext); return TK_NUM; }
"("                 { return '('; /*)*/}
")"                 { return ')'; }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
.                   { fprintf(stderr, "Unrecognized token"); }
