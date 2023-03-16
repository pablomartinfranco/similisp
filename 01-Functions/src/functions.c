#include <ctype.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "library.h"

void mostrar_ayuda()
{
	puts("");
	puts("Forma de utilizacion:");
	puts("$ ./functions <comando>");
	puts("\n");
	puts("Comandos disponibles:");
	puts("> cadmayus	Cadena a mayuscula.");
	puts("> cadaint		Cadena a integer.");
	puts("> cadcont		Contar caracteres de cadena.");
	puts("> concat		Concatenar dos cadenas.");
	puts("> carmodif	Modificar caracter en cadena.");
	puts("> carelim		Eliminar caracter en cadena.");
	puts("");
}

char* leer_consola(char* mensaje)
{
	char* pcad;
	printf("%s", mensaje);
	scanf("%ms", &pcad);
	return pcad;
}

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		if(!strcmp("cadmayus", argv[1]))
		{
			printf("%s\n", cadmayus(leer_consola("Ingresar cadena: ")));
		}
		else if(!strcmp("cadaint", argv[1]))
		{
			int error;
			int numero = cadaint(leer_consola("Ingresar cadena: "), &error);
			if(!error)
				printf("%d\n", numero);
			else
				printf("Cadena invalida.\n");
		}
		else if(!strcmp("cadcont", argv[1]))
		{
			printf("%d\n", cadcont(leer_consola("Ingresar cadena: ")));
		}
		else if(!strcmp("concat", argv[1]))
		{
			char* cada = leer_consola("Ingresar cadena: ");
			char* cadb = leer_consola("Ingresar otra cadena: ");
			printf("%s\n", concat(cada, cadb));
		}
		else if(!strcmp("carmodif", argv[1]))
		{
			int error;
			char* cada = leer_consola("Ingresar cadena: ");
			char* caracter = leer_consola("Ingresar caracter: ");
			char* indice = leer_consola("Ingresar indice: ");
			char* cadb = carmodif(cada, caracter[0], cadaint(indice, &error), &error);
			if(!error)
				printf("%s\n", cadb);
			else
				printf("Indice invalido.\n");
		}
		else if(!strcmp("carelim", argv[1]))
		{
			char* cadena = leer_consola("Ingresar cadena: ");
			char* caracter = leer_consola("Ingresar caracter: ");
			printf("%s\n", carelim(cadena, caracter[0]));
		}
		else
		{
			mostrar_ayuda();
		}
	}
	else
	{
		mostrar_ayuda();
	}

    return EXIT_SUCCESS;
}
