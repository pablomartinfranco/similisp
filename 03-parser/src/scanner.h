#include <stdio.h>
#include <string.h>

#define	_ (-1)

#define	RECHAZO (-1)

typedef int Q;

typedef Q QF[10];

typedef Q TT[10][100];

typedef enum {ERROR, NUMERO, SIMBOLO, CADENA, PARIZQ, PARDER, SOT, EOT} Token;

typedef struct AFD {TT tt; QF qf; Q q; char* centinelas; char* blancos; int offset; Token token;} AFD;

extern AFD afd;

Q next_state(char c) {

	int input = (int)c - afd.offset;

	int columns = sizeof(afd.tt[0])/sizeof(afd.tt[0][0]);

	if (input < 0 || input >= columns) afd.q = RECHAZO;

	else afd.q = afd.tt[afd.q][input];

	return afd.q;
}

Token token() {

	if (afd.q == RECHAZO) afd.token = ERROR;

	else afd.token = afd.qf[afd.q];

	afd.q = 0;

	return afd.token;
}

Token scan_next(FILE *stream) {

	char c;

	while ((c = getc(stream)) != EOF && strchr(afd.blancos, c));

	if (c == EOF) return EOT;

	next_state(c);

	if (strchr(afd.centinelas, c)) return token();

	while ((c = getc(stream)) != EOF) {

		if (strchr(afd.centinelas, c) || strchr(afd.blancos, c)) {

			//ungetc(c, stream);
			fseek(stream, -1, SEEK_CUR);

			return token();
		}

		next_state(c);
	}

	return token();
}

Token scan_ahead(FILE *stream) {

	char c;

	int x = ftell(stream);

	while ((c = getc(stream)) != EOF && strchr(afd.blancos, c));

	if (c == EOF) {
		fseek(stream, x, SEEK_SET);
		return EOT;
	}

	next_state(c);

	if (strchr(afd.centinelas, c)) {
		fseek(stream, x, SEEK_SET);
		return token();
	}

	while ((c = getc(stream)) != EOF) {

		if (strchr(afd.centinelas, c) || strchr(afd.blancos, c)) {

			fseek(stream, x, SEEK_SET);
			return token();
		}

		next_state(c);
	}

	fseek(stream, x, SEEK_SET);

	return token();
}

void scanner_help() { puts("\n$ ./scanner <file>\n"); }

void scanner_error(char *msg) { printf("\nscanner_error: %s \n", msg); }

void scanner_print(Token token) {
	switch (token) {
		case ERROR:	printf("<ERROR>");	break;
		case NUMERO:	printf("<NUMERO>");		break;
		case SIMBOLO:	printf("<SIMBOLO>");	break;
		case CADENA:	printf("<CADENA>");		break;
		case PARIZQ:	printf("<PARIZQ>");		break;
		case PARDER:	printf("<PARDER>");		break;
		case SOT:		printf("<SOT>");		break;
		case EOT:		printf("<EOT>");		break;
		default: 		printf("<ERROR>");		break;
	}
}
