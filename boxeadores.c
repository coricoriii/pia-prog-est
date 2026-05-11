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
    return -1; 
}

void modificar_boxeador() {
    
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

void eliminar_boxeador() {
    printf("Ingrese el nombre del boxeador a eliminar: ");
    char nombre[50];
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = 0;  // Remover salto de línea
    Boxeador b;
    long posicion = boxeador_existe(nombre, &b);
    if (posicion >= 0) {
        FILE *f = fopen("boxeadores.dat", "r+b");
        if (f != NULL) {
            b.activo = 0; // Marcar como inactivo
            if (fseek(f, posicion, SEEK_SET) == 0) {
                fwrite(&b, sizeof(Boxeador), 1, f);
                printf("Boxeador '%s' eliminado correctamente.\n\n", b.nombre);
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

void registrar_resultado() {
    printf("Ingrese el nombre del boxeador ganador: ");
    char ganador[50];
    fgets(ganador, sizeof(ganador), stdin);
    ganador[strcspn(ganador, "\n")] = 0;  // Remover salto de línea
    printf("Ingrese el nombre del boxeador perdedor: ");
    char perdedor[50];
    fgets(perdedor, sizeof(perdedor), stdin);
    perdedor[strcspn(perdedor, "\n")] = 0;  // Remover salto de línea
    printf("Ingrese el resultado (KO,TKO): ");
    char resultado[20];
    fgets(resultado, sizeof(resultado), stdin);
    resultado[strcspn(resultado, "\n")] = 0;  // Remover salto de línea
    Boxeador b_ganador, b_perdedor;
    long pos_ganador = boxeador_existe(ganador, &b_ganador);
    long pos_perdedor = boxeador_existe(perdedor, &b_perdedor);
    if (pos_ganador >= 0 && pos_perdedor >= 0) {
        FILE *f = fopen("boxeadores.dat", "r+b");
        if (f != NULL) {
            // Actualizar ganador
            b_ganador.record.victorias++;
            b_ganador.record.totalPeleas++;
            b_ganador.record.indiceVictorias = (float)b_ganador.record.victorias / b_ganador.record.totalPeleas;
            if (fseek(f, pos_ganador, SEEK_SET) == 0) {
                fwrite(&b_ganador, sizeof(Boxeador), 1, f);
            }
            // Actualizar perdedor
            b_perdedor.record.derrotas++;
            b_perdedor.record.totalPeleas++;
            b_perdedor.record.indiceVictorias = (float)b_perdedor.record.victorias / b_perdedor.record.totalPeleas;
            if (fseek(f, pos_perdedor, SEEK_SET) == 0) {
                fwrite(&b_perdedor, sizeof(Boxeador), 1, f);
            }
            fclose(f);
            printf("Resultado registrado: '%s' gano a '%s'.\n\n", ganador, perdedor);
        } else {
            printf("Error al abrir el archivo.\n");
        }
    } else {
        printf("Boxeador ganador o perdedor no encontrado.\n");
    }
    // resultados.dat guardar resultados
    Resultado r;
    // Guardar nombres como cadenas
    strncpy(r.ganador, ganador, sizeof(r.ganador) - 1);
    r.ganador[sizeof(r.ganador) - 1] = '\0';
    strncpy(r.perdedor, perdedor, sizeof(r.perdedor) - 1);
    r.perdedor[sizeof(r.perdedor) - 1] = '\0';
    // Resultado (KO, TKO, etc.)
    strncpy(r.resultado, resultado, sizeof(r.resultado) - 1);
    r.resultado[sizeof(r.resultado) - 1] = '\0';

    FILE *f_resultados = fopen("resultados.dat", "ab");
    if (f_resultados != NULL) {
        fwrite(&r, sizeof(Resultado), 1, f_resultados);
        fclose(f_resultados);
    } else {
        printf("Error al abrir el archivo de resultados.\n");
    }
}



