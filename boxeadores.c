#include "boxeadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* categorias[3] = {
    "Peso Ligero",
    "Peso Mediano",
    "Peso Pesado"
};

void agregar_boxeador() {
    Boxeador b;
    memset(&b, 0, sizeof(Boxeador));  // Inicializar la estructura a ceros
    
    // Creando el boxeador
    printf("Ingrese nombre: ");
    fgets(b.nombre, sizeof(b.nombre), stdin);
    b.nombre[strcspn(b.nombre, "\n")] = 0;  // Remover salto de línea
    
    printf("Ingrese peso: ");
    scanf("%f", &b.peso);
    printf("Ingrese cantidad de victorias: ");
    scanf("%d", &b.record.victorias);
    printf("Ingrese cantidad de derrotas: ");
    scanf("%d", &b.record.derrotas);
    getchar();  // Consumir salto de línea después de scanf
    
    b.record.totalPeleas = b.record.victorias + b.record.derrotas;
    if (b.record.totalPeleas > 0) {
        b.record.indiceVictorias = (float)b.record.victorias / b.record.totalPeleas;
    } else {
        b.record.indiceVictorias = 0.0f;
    }
    b.activo = 1;
    
    // Guardar el boxeador en la base de datos
    FILE *f = fopen("boxeadores.dat", "ab");
    if (f != NULL) {
        fwrite(&b, sizeof(Boxeador), 1, f);
        fclose(f);
        printf("Boxeador '%s' agregado correctamente.\n\n", b.nombre);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

void buscar_boxeador() {
    printf("Ingrese nombre del boxeador a buscar: ");
    char nombre[50];
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = 0;  // Remover salto de línea
    
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b;
        int encontrado = 0;
        while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
            // Debug: mostrar qué estamos comparando
            // printf("[Debug] Comparando '%s' con '%s'\n", nombre, b.nombre);
            if (strcmp(b.nombre, nombre) == 0 && b.activo) {
                printf("\n===== BOXEADOR ENCONTRADO =====");
                printf("\nNombre: %s\n", b.nombre);
                printf("Peso: %.2f kg\n", b.peso);
                printf("Categoria: %s\n", b.categoria);
                printf("Record: %d victorias, %d derrotas\n", b.record.victorias, b.record.derrotas);
                printf("Indice de victorias: %.2f\n", b.record.indiceVictorias);
                printf("============================\n\n");
                encontrado = 1;
                break;
            }
        }
        fclose(f);
        if (!encontrado) {
            printf("\nBoxeador '%s' no encontrado.\n\n", nombre);
        }
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

void listar_boxeadores_activos() {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b;
        int contador = 0;
        printf("\n===== BOXEADORES ACTIVOS =====");
        while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
            if (b.activo) {
                contador++;
                printf("\n%d. Nombre: %s\n", contador, b.nombre);
                printf("   Peso: %.2f kg\n", b.peso);
                printf("   Categoria: %s\n", b.categoria);
                printf("   Record: %d-%d (%.2f%% victorias)\n", 
                    b.record.victorias, b.record.derrotas, b.record.indiceVictorias * 100);
            }
        }
        fclose(f);
        if (contador == 0) {
            printf("\nNo hay boxeadores activos registrados.\n");
        } else {
            printf("\nTotal: %d boxeadores activos.\n", contador);
        }
        printf("==============================\n\n");
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

