#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

char* cadmayus(char* cadena)
{
	char* pcad = cadena;
	while(*pcad != '\0')
	{
		if(	*pcad >= 'a' && *pcad <= 'z')
			*pcad = *pcad - ('a' - 'A');
		pcad++;
	}

	return cadena;
}

int cadcont(char* cadena)
{
    int i = 0;
    while(cadena[i] != '\0') i++;
    return i;
}


char* concat(char* cada, char* cadb)
{
	int a = cadcont(cada);
	int b = cadcont(cadb);

	int size = a+b;
    char* cadena = malloc((size+1)*sizeof(char));
    cadena[size] = '\0';

    char* pcad = cadena;

    while (*cada != '\0') *pcad++ = *cada++;

    while (*cadb != '\0') *pcad++ = *cadb++;

    return cadena;
}


int cadaint(char* cadena, int* error)
{
    int resultado = 0;
    int signo = 1;
    int i = 0;

    *error = 0;

    if (cadena[0] == '-') {
    	signo = -1;
        i++;
    }

    for(; cadena[i] != '\0'; ++i)
    {
    	if(cadena[i] < '0' || cadena[i] > '9')
    	{
    		*error = 1;
    		return 0;
    	}
    	resultado = resultado * 10 + cadena[i] - '0';
    }

    return signo * resultado;
}

char* carmodif(char* cadena, char caracter, int indice, int* error) {

	*error = 0;

	if((indice+1) > cadcont(cadena) || indice < 0)
	{
		*error = 1;

		return cadena;
	}

	cadena[indice]=caracter;

	return cadena;
}

char* carelim(char* cadena, char letra) {
	int i = 0, j = 0;
	int s = cadcont(cadena);
	char* cadenafinal = malloc((s+1)*sizeof(char));
	cadenafinal[s] = '\0';

	while(i < s)
	{
		if (cadena[i] != letra)
		{
			cadenafinal[j] = cadena[i];
			j++;
		}
		i++;
	}
	cadenafinal[j] = '\0';

	return cadenafinal;
}




