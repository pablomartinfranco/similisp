#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <inttypes.h>

#define	_ (-1)
#define	ESTADO_RECHAZO (-1)

typedef enum {
	LETRA, DIGITO, ESPECIAL,
	PARIZQ, PARDER, N, I, L,
	GUION, COMA,
} CARACTER;

int transicion(char c, int estado, int tt[5][10])
{
	if		(isalpha(c))	return tt[estado][LETRA];
	else if	(isdigit(c))	return tt[estado][DIGITO];
	else if	(strchr("+*/<>=_", c))	return tt[estado][ESPECIAL];
	else if	(c == '(')		return tt[estado][PARIZQ];
	else if	(c == ')')		return tt[estado][PARDER];
	else if	(c == 'n')		return tt[estado][N];
	else if	(c == 'i')		return tt[estado][I];
	else if	(c == 'l')		return tt[estado][L];
	else if	(c == '-')		return tt[estado][GUION];
	else if	(c == ',')		return tt[estado][COMA];
	else 					return ESTADO_RECHAZO;
}

bool scanner(char* cadena, int estadoInicial,
		bool estadosFinales[5], int tablaTransicion[5][10])
{
	int estado = estadoInicial;

	while (*cadena) {

        estado = transicion(*cadena++, estado, tablaTransicion);

        if(estado == ESTADO_RECHAZO) return false;
	}

	return estadosFinales[estado];
}

void mostrar_ayuda() {
	puts("");
	puts("Forma de utilizacion:");
	puts("$ ./scanner vacio|numero|simbolo");
	puts("");
}

int main(int argc, char **argv)
{
	if(argc != 2) {
		mostrar_ayuda();
		return EXIT_SUCCESS;
	}

	if(strcmp("vacio", argv[1]) == 0)
	{
		int tablaTransicion[5][10] =
		{
		//	  LE DI ES PI PD N  I  L  GU CO
			{ _, _,	_, 4, _, 3, _, _, _, _, }, // 0-
			{ _, _, _, _, _, _, _, _, _, _, }, // 1+
			{ _, _, _, _, _, _, _, 1, _, _, }, // 2
			{ _, _, _, _, _, _, 2, _, _, _, }, // 3
			{ _, _, _, _, 1, _, _, _, _, _, }, // 4
		};

		int estadoInicial = 0;

		bool estadosFinales[5] =
		{
			false, true, false, false, false,
		};

		char cadena[256];

		printf("Ingresar token vacio: ");
		scanf("%s", cadena);

		bool tokenValido = scanner(cadena, estadoInicial,
				estadosFinales, tablaTransicion);

		if(tokenValido)	puts("Token valido.");
		else			puts("Token invalido.");

	}
	else if(strcmp("numero", argv[1]) == 0)
	{
		int tablaTransicion[5][10] =
		{
		//	  LE DI ES PI PD N  I  L  GU CO
			{ _, 3,	_, _, _, _, _, _, 2, _, }, // 0-
			{ _, 1,	_, _, _, _, _, _, _, _, }, // 1+
			{ _, 3,	_, _, _, _, _, _, _, _, }, // 2
			{ _, 3,	_, _, _, _, _, _, _, 1, }, // 3+
			{ _, _,	_, _, _, _, _, _, _, _, }, // 4
		};

		int estadoInicial = 0;

		bool estadosFinales[5] =
		{
			false, true, false, true, false,
		};

		char cadena[256];

		printf("Ingresar token numero: ");
		scanf("%s", cadena);

		bool tokenValido = scanner(cadena, estadoInicial,
				estadosFinales, tablaTransicion);

		if(tokenValido)	puts("Token valido.");
		else			puts("Token invalido.");

	}
	else if(strcmp("simbolo", argv[1]) == 0)
	{
		int tablaTransicion[5][10] =
		{
		//	  LE DI ES PI PD N  I  L  GU CO
			{ 2, _,	2, _, _, _, _, _, _, _, }, // 0-
			{ 1, 1,	1, _, _, _, _, _, _, _, }, // 1+
			{ 1, 1,	1, _, _, _, _, _, _, _, }, // 2+
			{ _, _,	_, _, _, _, _, _, _, _, }, // 3
			{ _, _,	_, _, _, _, _, _, _, _, }, // 4
		};

		int estadoInicial = 0;

		bool estadosFinales[5] =
		{
			false, true, true, false, false,
		};

		char cadena[256];

		printf("Ingresar token simbolo: ");
		scanf( "%s", cadena);

		bool tokenValido = scanner(cadena, estadoInicial,
				estadosFinales, tablaTransicion);

		if(tokenValido)	puts("Token valido.");
		else			puts("Token invalido.");
	}
	else {
		mostrar_ayuda();
	}

    return EXIT_SUCCESS;
}
