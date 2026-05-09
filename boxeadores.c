#include "boxeadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* categorias[3] = {
    "Peso Ligero",
    "Peso Mediano",
    "Peso Pesado"
};

long boxeador_existe(const char* nombre, Boxeador* encontrado) {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b;
        while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
            if (strcmp(b.nombre, nombre) == 0 && b.activo) {
                long posicion = ftell(f) - (long)sizeof(Boxeador);
                if (encontrado != NULL) {
                    *encontrado = b;
                }
                fclose(f);
                return posicion;
            }
        }
        fclose(f);
    }
    return -1; // Boxeador no existe
}

void modificar_boxeador() {
    // Ingresar el nombre del boxeador a modificar
    char nombre[50];
    printf("Ingrese el nombre del boxeador a modificar: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = 0;  // Remover
    Boxeador b;
    long posicion = boxeador_existe(nombre, &b);
    if (posicion >= 0) {
        FILE *f = fopen("boxeadores.dat", "r+b");
        if (f != NULL) {
            printf("Ingrese nuevo peso: ");
            scanf("%f", &b.peso);
            getchar(); // Consumir salto de línea
            printf("Ingrese nueva cantidad de victorias: ");
            scanf("%d", &b.record.victorias);
            printf("Ingrese nueva cantidad de derrotas: ");
            scanf("%d", &b.record.derrotas);
            getchar(); // Consumir salto de línea
            
            b.record.totalPeleas = b.record.victorias + b.record.derrotas;
            if (b.record.totalPeleas > 0) {
                b.record.indiceVictorias = (float)b.record.victorias / b.record.totalPeleas;
            } else {
                b.record.indiceVictorias = 0.0f;
            }
            
            if (b.peso < 60.0f) {
                strcpy(b.categoria, categorias[0]);
            } else if (b.peso < 80.0f) {
                strcpy(b.categoria, categorias[1]);
            } else {
                strcpy(b.categoria, categorias[2]);
            }
            
            if (fseek(f, posicion, SEEK_SET) == 0) {
                fwrite(&b, sizeof(Boxeador), 1, f);
                printf("Boxeador '%s' modificado correctamente.\n\n", b.nombre);
            } else {
                printf("Error al posicionar el archivo.\n");
            }
            fclose(f);
        } else {
            printf("Error al abrir el archivo.\n");
        }
    } else {
        printf("Boxeador '%s' no encontrado.\n", nombre);
    }
}

void agregar_boxeador() {
    Boxeador b;    
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
    if (b.peso < 60.0f) {
        strcpy(b.categoria, categorias[0]);
    } else if (b.peso < 80.0f) {
        strcpy(b.categoria, categorias[1]);
    } else {
        strcpy(b.categoria, categorias[2]);
    }
    
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
    
    Boxeador b;
    long posicion = boxeador_existe(nombre, &b);
    if (posicion >= 0) {
        printf("\nNombre: %s\n", b.nombre);
        printf("Peso: %.2f kg\n", b.peso);
        printf("Categoria: %s\n", b.categoria);
        printf("Record: %d-%d (%.2f%% victorias)\n", 
            b.record.victorias, b.record.derrotas, b.record.indiceVictorias * 100);
    } else {
        printf("Boxeador '%s' no encontrado.\n", nombre);
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

