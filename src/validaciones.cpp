#include "validaciones.h"
#include <cstdio>
#include <cstring>
#include <regex>   
#include <string> 

using namespace std; 

static void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int validar_nombre(const char *nombre) {
    if (!nombre || strlen(nombre) < 2 || strlen(nombre) > 49)
        return 0;

    regex patron(u8"^[A-Za-záéíóúÁÉÍÓÚñÑ][A-Za-záéíóúÁÉÍÓÚñÑ ]{0,48}$");
    return regex_match(string(nombre), patron) ? 1 : 0;
}


int validar_peso(float peso) {
    return (peso > 0.0f && peso <= 200.0f) ? 1 : 0;
}


int validar_entero_positivo(int n) {
    return (n >= 0) ? 1 : 0;
}

int validar_resultado(const char *res) {
    if (!res) return 0;
    regex patron("^(KO|TKO|Decision)$");
    return regex_match(string(res), patron) ? 1 : 0;
}


int validar_id(int id) {
    return (id > 0) ? 1 : 0;
}


void pedir_nombre(char *buf, int tam) {
    int valido;
    do {
        fgets(buf, tam, stdin);
        buf[strcspn(buf, "\n")] = '\0';
        valido = validar_nombre(buf);
        if (!valido) {
            printf("  Error: solo letras (con acentos/n~) y espacios, entre 2 y 49 caracteres.\n");
            printf("  Intente de nuevo: ");
        }
    } while (!valido);
}


float pedir_peso() {
    float peso;
    int valido;
    do {
        int leidos = scanf("%f", &peso);
        if (leidos != 1) {         
            limpiar_buffer();
            valido = 0;
        } else {
            getchar();
            valido = validar_peso(peso);
        }
        if (!valido) {
            printf("  Error: ingrese un peso entre 0.1 y 200 kg.\n");
            printf("  Intente de nuevo: ");
        }
    } while (!valido);
    return peso;
}


int pedir_entero_positivo(const char *msg) {
    int n;
    int valido;
    do {
        int leidos = scanf("%d", &n);
        if (leidos != 1) {          
            limpiar_buffer();
            valido = 0;
        } else {
            getchar();
            valido = validar_entero_positivo(n);
        }
        if (!valido) {
            printf("  Error: %s debe ser un numero entero mayor o igual a 0.\n", msg);
            printf("  Intente de nuevo: ");
        }
    } while (!valido);
    return n;
}


void pedir_resultado(char *buf, int tam) {
    int valido;
    do {
        fgets(buf, tam, stdin);
        buf[strcspn(buf, "\n")] = '\0';
        valido = validar_resultado(buf);
        if (!valido) {
            printf("  Error: opciones validas: KO, TKO, Decision.\n");
            printf("  Intente de nuevo: ");
        }
    } while (!valido);
}

int pedir_id(const char *msg) {
    int id;
    int valido;
    do {
        int leidos = scanf("%d", &id);
        if (leidos != 1) { 
            limpiar_buffer();
            valido = 0; 
        } else {
            getchar();
            valido = validar_id(id);
        }
        if (!valido) {
            printf("  Error: %s debe ser un numero entero mayor a 0.\n", msg);
            printf("  Intente de nuevo: ");
        }
    } while (!valido);
    return id;
}