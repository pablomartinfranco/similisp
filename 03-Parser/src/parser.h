#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "scanner.h"

void expresion();
void lista();
void _lista();
void atomo();
void vacio();
void match(Token token);

FILE *_file;

void parser_help() { puts("\n$ ./scanner <file>\n"); }

void parser_error(char *msg) { printf("\nparser_error: %s \n", msg); }

bool parse(FILE *file)
{
	_file = file;

	lista();

    return EXIT_SUCCESS;
}

void lista() {

	Token token = scan_next(_file);

	if (token == PARIZQ) {

		match(PARIZQ);

		if (scan_ahead(_file) == PARDER)

			scan_next(_file);

		else _lista();

		match(PARDER);
	}
	else parser_error("lista");
}

void _lista() {

	expresion();

	while (1) {

		Token token = scan_ahead(_file);

		switch (token) {
			case NUMERO: expresion(); break;
			case SIMBOLO: expresion(); break;
			case CADENA: expresion(); break;
			case PARIZQ: expresion(); break;
			default: return;
		}
	}
}

void expresion() {

	Token token = scan_ahead(_file);

	switch (token) {
		case NUMERO: atomo(); break;
		case SIMBOLO: atomo(); break;
		case CADENA: atomo(); break;
		case PARIZQ: lista(); break;
		default: parser_error("expresion"); break;
	}
}

void atomo() {

	Token token = scan_next(_file);

	switch (token) {
		case NUMERO: match(NUMERO); break;
		case SIMBOLO: match(SIMBOLO); break;
		case CADENA: match(CADENA); break;
		default: parser_error("atomo"); break;
	}
}

void match(Token token) {
	scanner_print(token);
}

