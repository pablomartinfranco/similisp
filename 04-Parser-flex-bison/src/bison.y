%{
#include <stdio.h>
#include <stdlib.h>

yyerror( char *str );
%}

%token NUMBER SYMBOL STRING

%%

entrada :
  | entrada programa
  ;

programa : '\n' 
  | exp '\n' { printf( "syntax ok\n" ); }
  ;

exp : atomo
  | lista
  ;

atomo : NUMBER
  | SYMBOL
  | STRING
  ;

lista : '(' ')'
  | '(' lista_exp ')'
  ;
  
lista_exp : exp
  | lista_exp exp
  ;
  
%%

yyerror( char * str )
{
  printf("%s\n", str );
}