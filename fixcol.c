#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define PARAM_TAM 1
#define PARAM_NOM 2
#define CANT_PARAMS_ENTRADA_STD 2
#define CANT_PARAMS_ARCHIVO 3

FILE* abrir_archivo(char* nom_archivo) {
	FILE* archivo = fopen(nom_archivo, "r");
	if (!archivo) {
		fprintf(stderr, "%s", "Error: archivo fuente inaccesible\n");
	}
	return archivo;
}

void procesar_texto(const int tam_buffer, FILE* stream) {
	char* linea = malloc((size_t)tam_buffer * sizeof(char) + 1); // le sumo 1 byte mas para el '\0'
	while ((fgets(linea, tam_buffer + 1, stream)) != NULL) {
		if (strlen(linea) == tam_buffer && linea[strlen(linea) - 1] == '\n') {
			fprintf(stdout, "%s", linea);
		}
		else if (strlen(linea) < tam_buffer) {
			if (strcmp(linea, "\n")) {
				fprintf(stdout, "%s", linea);
			}
		}
		else {
			fprintf(stdout, "%s\n", linea);
		}
	}
	free(linea);
}

bool es_numero(char* string) {
	size_t pos = 0;
	while (string[pos] != '\0') {
		if (!isdigit(string[pos])) {
			return false;
		}
		pos++;
	}
	return true;
}

bool validar_params(int argc, char* argv[]) {
	if ((argc != CANT_PARAMS_ENTRADA_STD && argc != CANT_PARAMS_ARCHIVO) || (!es_numero(argv[PARAM_TAM]))) {
		fprintf(stderr, "%s", "Error: Cantidad erronea de parametros\n");
		return false;
	}
	else {
		return true;
	}
}

int main(int argc, char* argv[]) {
	if (!validar_params(argc, argv)) {
		return -1;
	}
	const int tam_buffer = atoi(argv[PARAM_TAM]);
	if (argc == CANT_PARAMS_ENTRADA_STD) {
		procesar_texto(tam_buffer, stdin);
	}
	else {
		FILE* archivo = abrir_archivo(argv[PARAM_NOM]);
		if (!archivo) { return -1; }
		procesar_texto(tam_buffer, archivo);
		fclose(archivo);
	}
	
	return 0;
}
