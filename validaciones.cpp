#include "validaciones.h"
#include <stdio.h>
#include <string.h>
#include <regex>
#include <string>

int validar_nombre(const char *nombre) {
    if (strlen(nombre) < 2 || strlen(nombre) > 49) {
        return 0;
    }
    std::regex patron("^[a-zA-Z\xc3\xa1\xc3\xa9\xc3\xad\xc3\xb3\xc3\xba\xc3\x81\xc3\x89\xc3\x8d\xc3\x93\xc3\x9a\xc3\xb1\xc3\x91 ]+$");
    return std::regex_match(nombre, patron) ? 1 : 0;
}

int validar_peso(float peso) {
    return (peso > 0.0f && peso <= 200.0f) ? 1 : 0;
}

int validar_entero_positivo(int n) {
    return (n >= 0) ? 1 : 0;
}

int validar_resultado(const char *res) {
    std::regex patron("^(KO|TKO|Decision)$");
    return std::regex_match(res, patron) ? 1 : 0;
}

int validar_id(int id) {
    return (id > 0) ? 1 : 0;
}

int validar_opcion_menu(int op, int min, int max) {
    return (op >= min && op <= max) ? 1 : 0;
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
// hola cori solo queria ver si encuentras este comentario saludos desde el futuro :D
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

int pedir_id(const char *msg) {
    int id;
    int valido;
    do {
        printf("%s", msg);
        int leidos = scanf("%d", &id);
        getchar();
        valido = leidos == 1 && validar_id(id);
        if (!valido) {
            printf("Error: el ID debe ser un numero entero positivo mayor a 0.\n");
        }
    } while (!valido);
    return id;
}

int pedir_opcion_menu(int min, int max) {
    int op;
    int valido;
    do {
        int leidos = scanf("%d", &op);
        getchar();
        valido = leidos == 1 && validar_opcion_menu(op, min, max);
        if (!valido) {
            printf("Error: opcion invalida. Ingrese un numero entre %d y %d.\n", min, max);
            printf("Seleccione una opcion: ");
        }
    } while (!valido);
    return op;
}