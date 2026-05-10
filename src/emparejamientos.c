#include "boxeadores.h"
#include "emparejamientos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static float calcular_compatibilidad(Boxeador *b1, Boxeador *b2) {
    float difPeso = fabsf(b1->peso - b2->peso);
    float difIndice = fabsf(b1->record.indiceVictorias - b2->record.indiceVictorias);
    float comp = 100.0f - (difPeso * 2.0f + difIndice * 0.5f);
    if (comp < 0.0f) {
        comp = 0.0f;
    }
    return comp;
}

static int siguiente_id_emparejamiento() {
    FILE *f = fopen("emparejamientos.dat", "rb");
    int max = 0;
    if (f != NULL) {
        Emparejamiento e;
        while (fread(&e, sizeof(Emparejamiento), 1, f) == 1) {
            if (e.idEmparejamiento > max) {
                max = e.idEmparejamiento;
            }
        }
        fclose(f);
    }
    return max + 1;
}

void guardar_emparejamiento(int id1, int id2, float comp) {
    Emparejamiento e;
    e.idEmparejamiento = siguiente_id_emparejamiento();
    e.idBoxeador1 = id1;
    e.idBoxeador2 = id2;
    e.compatibilidad = comp;

    FILE *f = fopen("emparejamientos.dat", "ab");
    if (f != NULL) {
        fwrite(&e, sizeof(Emparejamiento), 1, f);
        fclose(f);
        printf("Emparejamiento guardado con ID %d.\n", e.idEmparejamiento);
    } else {
        printf("Error al guardar el emparejamiento.\n");
    }
}

void mejor_rival() {
    int id;
    printf("Ingrese el ID del boxeador: ");
    scanf("%d", &id);
    getchar();

    Boxeador seleccionado;
    long pos = boxeador_existe_id(id, &seleccionado);
    if (pos < 0) {
        printf("Boxeador con ID %d no encontrado o inactivo.\n", id);
        return;
    }

    Boxeador lista[MAX_BOXEADORES];
    int cont = 0;

    FILE *f = fopen("boxeadores.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir archivo.\n");
        return;
    }

    Boxeador b;
    while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
        if (b.activo == 1 && b.id != seleccionado.id) {
            lista[cont] = b;
            cont++;
        }
    }
    fclose(f);

    if (cont == 0) {
        printf("No hay otros boxeadores activos para comparar.\n");
        return;
    }

    int mejor = 0;
    float mejorComp = calcular_compatibilidad(&seleccionado, &lista[0]);

    for (int i = 1; i < cont; i++) {
        float c = calcular_compatibilidad(&seleccionado, &lista[i]);
        if (c > mejorComp) {
            mejorComp = c;
            mejor = i;
        }
    }

    printf("\nBoxeador seleccionado: %s (ID %d)\n", seleccionado.nombre, seleccionado.id);
    printf("Mejor rival sugerido: %s (ID %d)\n", lista[mejor].nombre, lista[mejor].id);
    printf("Compatibilidad: %.2f%%\n\n", mejorComp);

    char op;
    printf("¿Desea guardar este emparejamiento? (s/n): ");
    scanf(" %c", &op);
    getchar();
    if (op == 's' || op == 'S') {
        guardar_emparejamiento(seleccionado.id, lista[mejor].id, mejorComp);
    }
}

void mostrar_matriz() {
    Boxeador lista[MAX_BOXEADORES];
    int cont = 0;
    float matrizComp[MAX_BOXEADORES][MAX_BOXEADORES];

    FILE *f = fopen("boxeadores.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir archivo.\n");
        return;
    }

    Boxeador b;
    while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
        if (b.activo == 1) {
            lista[cont] = b;
            cont++;
        }
    }
    fclose(f);

    if (cont < 2) {
        printf("Se necesitan al menos 2 boxeadores activos para mostrar la matriz.\n");
        return;
    }

    for (int i = 0; i < cont; i++) {
        for (int j = 0; j < cont; j++) {
            if (i == j) {
                matrizComp[i][j] = 0.0f;
            } else {
                matrizComp[i][j] = calcular_compatibilidad(&lista[i], &lista[j]);
            }
        }
    }

    printf("\n===== MATRIZ DE COMPATIBILIDAD =====\n");
    printf("%15s", "");
    for (int i = 0; i < cont; i++) {
        printf("%15s", lista[i].nombre);
    }
    printf("\n");

    for (int i = 0; i < cont; i++) {
        printf("%15s", lista[i].nombre);
        for (int j = 0; j < cont; j++) {
            if (i == j) {
                printf("%15s", "--");
            } else {
                printf("%14.2f%%", matrizComp[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void ver_emparejamientos() {
    FILE *f = fopen("emparejamientos.dat", "rb");
    if (f == NULL) {
        printf("No hay emparejamientos guardados.\n");
        return;
    }

    Emparejamiento e;
    printf("\n%-6s %-6s %-6s %-15s\n", "ID", "Box1", "Box2", "Compatibilidad");
    printf("------------------------------------------\n");

    int cont = 0;
    while (fread(&e, sizeof(Emparejamiento), 1, f) == 1) {
        Boxeador b1, b2;
        char nom1[50] = "?";
        char nom2[50] = "?";
        if (boxeador_existe_id(e.idBoxeador1, &b1) >= 0) {
            strcpy(nom1, b1.nombre);
        }
        if (boxeador_existe_id(e.idBoxeador2, &b2) >= 0) {
            strcpy(nom2, b2.nombre);
        }
        printf("%-6d %-20s %-20s %.2f%%\n",
               e.idEmparejamiento, nom1, nom2, e.compatibilidad);
        cont++;
    }
    fclose(f);

    if (cont == 0) {
        printf("No hay emparejamientos registrados.\n");
    }
    printf("\n");
}
