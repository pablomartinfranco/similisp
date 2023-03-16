%{
#include <stdio.h>
#include "y.tab.h"
%}

%option noyywrap

%%
[ \t]+            		;
[0-9]+(\.[0-9]+)?		{return NUMBER;}
[_A-Za-z][0-9A-Za-z]*	{return SYMBOL;}
[-+*=_]					{return SYMBOL;}
\"[^\"]*\"				{return STRING;}
\(|\)|\n                {return yytext[0];}
<<EOF>>     			{return YYEOF;}
:q		     			{return YYEOF;}
.						{return YYUNDEF;}
%%