%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
extern int yyparse();
void yyerror(char *msg);
%}

%union {
    int num;
    char *str;
}

%token <num> NUM
%token <str> WHILE LPAREN RPAREN LBRACE RBRACE GT LT GE LE EQ NE
%type <str> condition relop

%%

program:
    | program stmt
    ;

stmt:
      WHILE LPAREN condition RPAREN LBRACE RBRACE { printf("Parsed while-loop with condition: %s\n", $3); }
    ;

condition:
      NUM relop NUM { 
        asprintf(&$$, "%d %s %d", $1, $2, $3); // Construct the condition string 
      }
    ;

relop:
      GT   { $$ = ">"; }
    | LT   { $$ = "<"; }
    | GE   { $$ = ">="; }
    | LE   { $$ = "<="; }
    | EQ   { $$ = "=="; }
    | NE   { $$ = "!="; }
    ;

%%

int main() {
    printf("Enter a while loop: ");
    yyparse();
    return 0;
}

void yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
