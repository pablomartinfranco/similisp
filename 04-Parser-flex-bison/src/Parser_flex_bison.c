#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

extern FILE *yyin;

int main( int argc, char **argv )
{
	++argv, --argc;

	if ( argc > 0 ) yyin = fopen( argv[0], "r" );

	else yyin = stdin;

	//printf("%d\n", yylex());

	yyparse();

	return EXIT_SUCCESS;
}
