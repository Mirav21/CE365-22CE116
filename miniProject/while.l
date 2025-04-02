%{
#include "y.tab.h"
%}
%%

[0-9]+        { yylval.num = atoi(yytext); return NUM; }
"while"       { return WHILE; }
"("           { return LPAREN; }
")"           { return RPAREN; }
"{"           { return LBRACE; }
"}"           { return RBRACE; }
">"           { return GT; }
"<"           { return LT; }
">="          { return GE; }
"<="          { return LE; }
"=="          { return EQ; }
"!="          { return NE; }

[ \t\n]       { /* Skip whitespace */ }

.             { return yytext[0]; } // Catch other characters
%%

int yywrap() {
    return 1;
}
