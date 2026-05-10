#include "boxeadores.h"
#include "emparejamientos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float calcular_compatibilidad(Boxeador b1, Boxeador b2) {
    float compatibilidad = 0.0f;
    if (strcmp(b1.categoria, b2.categoria) == 0) {
        compatibilidad += 50.0f; // Misma categoria
    }
    float diferencia = fabs(b1.record.indiceVictorias - b2.record.indiceVictorias);
    compatibilidad += (1.0f - diferencia) * 50.0f; // Similar record
    return compatibilidad;
}

void mejor_rival() {
    printf("Ingrese el nombre del boxeador para encontrar su mejor rival: ");
    char nombre[50];
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = 0;  // Remover salto de línea

    Boxeador b_seleccionado;
    long posicion = boxeador_existe(nombre, &b_seleccionado);
    if (posicion < 0) {
        printf("Boxeador '%s' no encontrado.\n", nombre);
        return;
    }
    // Usamos arreglos paralelos para almacenar los boxeadores y sus compatibilidades
    char rivales[100][50];
    float compatibilidades[100];
    int cont = 0;
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b_rival;
        while (fread(&b_rival, sizeof(Boxeador), 1, f) == 1) {
            if (b_rival.activo && strcmp(b_rival.nombre, b_seleccionado.nombre) != 0) {
                // Calcular compatibilidad
                float compatibilidad = calcular_compatibilidad(b_seleccionado, b_rival);
                // Guardar rival y compatibilidad
                strncpy(rivales[cont], b_rival.nombre, 50);
                compatibilidades[cont] = compatibilidad;
                cont++;
            }
        }
        fclose(f);
    } else {
        printf("Error al abrir el archivo.\n");
        return;
    }
    // Encontrar el rival con mayor compatibilidad (recorremos el arreglo )
    int mejor_index = 0;
    for (int i = 1; i < cont; i++) {
        if (compatibilidades[i] > compatibilidades[mejor_index]) {
            mejor_index = i;
        }
    }
    if (cont > 0) {
        printf("Boxeador seleccionado: %s\n", b_seleccionado.nombre);
        printf("Mejor rival: %s (Compatibilidad: %.2f%%)\n", rivales[mejor_index], compatibilidades[mejor_index]);
        // Guardar emparejamiento?
        printf("¿Desea guardar este emparejamiento? (s/n): ");
        char opcion;
        scanf(" %c", &opcion);
        if (opcion == 's' || opcion == 'S') {
            Emparejamiento e;
            strncpy(e.boxeador1, b_seleccionado.nombre, 50);
            strncpy(e.boxeador2, rivales[mejor_index], 50);
            e.compatibilidad = compatibilidades[mejor_index];
            // Guardar en archivo
            FILE *fe = fopen("emparejamientos.dat", "ab");
            if (fe != NULL) {
                fwrite(&e, sizeof(Emparejamiento), 1, fe);
                fclose(fe);
                printf("Emparejamiento guardado correctamente.\n");
            } else {
                printf("Error al guardar el emparejamiento.\n");
            }
        } else {
            printf("Emparejamiento no guardado.\n");
        }
    } else {
        printf("No hay otros boxeadores activos para comparar.\n");
    }
}

void ver_emparejamientos() {
    FILE *f = fopen("emparejamientos.dat", "rb");
    if (f != NULL) {
        Emparejamiento e;
        printf("\n===== EMPAREJAMIENTOS GUARDADOS =====\n");
        while (fread(&e, sizeof(Emparejamiento), 1, f) == 1) {
            printf("%s vs %s - Compatibilidad: %.2f%%\n", e.boxeador1, e.boxeador2, e.compatibilidad);
        }
        fclose(f);
    } else {
        printf("No hay emparejamientos guardados o error al abrir el archivo.\n");
    }
}

void mostrar_matriz() {
    float matrizComp[100][100];
    char nombres[100][50];
    int cont = 0;
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b1, b2;
        while (fread(&b1, sizeof(Boxeador), 1, f) == 1) {
            if (b1.activo) {
                strncpy(nombres[cont], b1.nombre, 50);
                cont++;
            }
        }
        fclose(f);
        // Calcular matriz de compatibilidad
        for (int i = 0; i < cont; i++) {
            for (int j = 0; j < cont; j++) {
                if (i == j) {
                    matrizComp[i][j] = 100.0f; // Compatibilidad perfecta consigo mismo
                } else {
                    Boxeador b_i, b_j;
                    boxeador_existe(nombres[i], &b_i);
                    boxeador_existe(nombres[j], &b_j);
                    matrizComp[i][j] = calcular_compatibilidad(b_i, b_j);
                }
            }
        }
        // Mostrar matriz
        printf("\n===== MATRIZ DE COMPATIBILIDAD =====\n");
        printf("%20s", "");
        for (int i = 0; i < cont; i++) {
            printf("%20s", nombres[i]);
        }
        printf("\n");
        for (int i = 0; i < cont; i++) {
            printf("%20s", nombres[i]);
            for (int j = 0; j < cont; j++) {
                printf("%20.2f", matrizComp[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Error al abrir el archivo.\n");
    }
}
