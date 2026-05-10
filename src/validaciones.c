#include "validaciones.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int es_letra_utf8(const unsigned char *texto, size_t *avance) {
    unsigned char c = texto[0];

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        *avance = 1;
        return 1;
    }

    if (c == 0xC3) {
        switch (texto[1]) {
            case 0x81:
            case 0x89:
            case 0x8D:
            case 0x93:
            case 0x9A:
            case 0xA1:
            case 0xA9:
            case 0xAD:
            case 0xB1:
            case 0xB3:
            case 0xBA:
                *avance = 2;
                return 1;
        }
    }

    return 0;
}

int validar_nombre(const char *nombre) {
    if (strlen(nombre) < 2 || strlen(nombre) > 49) {
        return 0;
    }

    for (size_t i = 0; nombre[i] != '\0'; ) {
        if (nombre[i] == ' ') {
            i++;
            continue;
        }

        size_t avance = 0;
        if (!es_letra_utf8((const unsigned char *)&nombre[i], &avance)) {
            return 0;
        }
        i += avance;
    }

    return 1;
}

int validar_peso(float peso) {
    return peso > 0.0f && peso <= 200.0f;
}

int validar_entero_positivo(int n) {
    return n >= 0;
}

int validar_resultado(const char *res) {
    return strcmp(res, "KO") == 0 ||
           strcmp(res, "TKO") == 0 ||
           strcmp(res, "Decision") == 0;
}

void pedir_nombre(char *buf, int tam) {
    int valido;
    do {
        fgets(buf, tam, stdin);
        buf[strcspn(buf, "\n")] = 0;
        valido = validar_nombre(buf);
        if (!valido) {
            printf("Error: el nombre solo puede contener letras y espacios (2-49 caracteres).\n");
            printf("Intente de nuevo: ");
        }
    } while (!valido);
}

float pedir_peso() {
    float peso;
    int valido;
    do {
        int leidos = scanf("%f", &peso);
        getchar();
        valido = leidos == 1 && validar_peso(peso);
        if (!valido) {
            printf("Error: el peso debe ser un numero positivo entre 0 y 200 kg.\n");
            printf("Intente de nuevo: ");
        }
    } while (!valido);
    return peso;
}

int pedir_entero_positivo(const char *msg) {
    int n;
    int valido;
    do {
        int leidos = scanf("%d", &n);
        getchar();
        valido = leidos == 1 && validar_entero_positivo(n);
        if (!valido) {
            printf("Error: %s debe ser un numero entero mayor o igual a 0.\n", msg);
            printf("Intente de nuevo: ");
        }
    } while (!valido);
    return n;
}

void pedir_resultado(char *buf, int tam) {
    int valido;
    do {
        fgets(buf, tam, stdin);
        buf[strcspn(buf, "\n")] = 0;
        valido = validar_resultado(buf);
        if (!valido) {
            printf("Error: resultado invalido. Opciones validas: KO, TKO, Decision.\n");
            printf("Intente de nuevo: ");
        }
    } while (!valido);
}
