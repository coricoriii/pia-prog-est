#include "boxeadores.h"
#include "emparejamientos.h"
#include "validaciones.h"  //por lo de la funciond id
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Sin cambios */
static float calcular_compatibilidad(Boxeador *b1, Boxeador *b2) {
    float difPeso   = fabsf(b1->peso - b2->peso);
    float difIndice = fabsf(b1->record.indiceVictorias - b2->record.indiceVictorias);
    float comp = 100.0f - (difPeso * 2.0f + difIndice * 0.5f);
    if (comp < 0.0f) comp = 0.0f;
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

// si alcancé a hacer el antiduplicados 
static int emparejamiento_duplicado(int id1, int id2) {
    FILE *f = fopen("emparejamientos.dat", "rb");
    if (f == NULL) return 0;
    Emparejamiento e;
    while (fread(&e, sizeof(Emparejamiento), 1, f) == 1) {
        if ((e.idBoxeador1 == id1 && e.idBoxeador2 == id2) ||
            (e.idBoxeador1 == id2 && e.idBoxeador2 == id1)) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

// este solo guarda los emparejamientos para no tener duplicados, lo demas es igual al original
void guardar_emparejamiento(int id1, int id2, float comp) {
    if (emparejamiento_duplicado(id1, id2)) {
        char op[4];
        printf("Advertencia: este par de boxeadores ya tiene un emparejamiento guardado.\n");
        printf("Desea guardarlo de todas formas? (s/n): ");
        fgets(op, sizeof(op), stdin);
        if (op[0] != 's' && op[0] != 'S') {
            printf("Emparejamiento no guardado.\n");
            return;
        }
    }

    Emparejamiento e;
    e.idEmparejamiento = siguiente_id_emparejamiento();
    e.idBoxeador1      = id1;
    e.idBoxeador2      = id2;
    e.compatibilidad   = comp;

    FILE *f = fopen("emparejamientos.dat", "ab");
    if (f != NULL) {
        fwrite(&e, sizeof(Emparejamiento), 1, f);
        fclose(f);
        printf("Emparejamiento guardado con ID %d.\n", e.idEmparejamiento);
    } else {
        printf("Error al guardar el emparejamiento.\n");
    }
}

// los scanf de ID los reemplaze por la funcion que te dije que haria
void mejor_rival() {
    printf("Ingrese el ID del boxeador: ");
    int id = pedir_id("ID"); 

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
            lista[cont++] = b;
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
    printf("Mejor rival sugerido : %s (ID %d)\n", lista[mejor].nombre, lista[mejor].id);
    printf("Compatibilidad       : %.2f%%\n\n", mejorComp);

    // vi un tutorial indio y parece que fgets evita problemas del buffer si lo quieres cambiar a scan otra vez no hay pedo
    char op[4];
    printf("Desea guardar este emparejamiento? (s/n): ");
    fgets(op, sizeof(op), stdin);
    if (op[0] == 's' || op[0] == 'S') {
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
            lista[cont++] = b;
        }
    }
    fclose(f);

    if (cont < 2) {
        printf("Se necesitan al menos 2 boxeadores activos para mostrar la matriz.\n");
        return;
    }

    for (int i = 0; i < cont; i++) {
        for (int j = 0; j < cont; j++) {
            matrizComp[i][j] = (i == j) ? 0.0f
                                         : calcular_compatibilidad(&lista[i], &lista[j]);
        }
    }

    printf("\n===== MATRIZ DE COMPATIBILIDAD =====\n");
    printf("%15s", "");
    for (int i = 0; i < cont; i++) printf("%15s", lista[i].nombre);
    printf("\n");

    for (int i = 0; i < cont; i++) {
        printf("%15s", lista[i].nombre);
        for (int j = 0; j < cont; j++) {
            if (i == j) printf("%15s", "--");
            else        printf("%14.2f%%", matrizComp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//pibble
void ver_emparejamientos() {
    FILE *f = fopen("emparejamientos.dat", "rb");
    if (f == NULL) {
        printf("No hay emparejamientos guardados.\n");
        return;
    }

    Emparejamiento e;
    int cont = 0;
    printf("\n%-6s %-20s %-20s %-15s\n", "ID", "Boxeador 1", "Boxeador 2", "Compatibilidad");
    printf("------------------------------------------------------------------\n"); //mas estetik

    while (fread(&e, sizeof(Emparejamiento), 1, f) == 1) {
        Boxeador b1, b2;
        char nom1[50] = "?";
        char nom2[50] = "?";
        if (boxeador_existe_id(e.idBoxeador1, &b1) >= 0) strcpy(nom1, b1.nombre);
        if (boxeador_existe_id(e.idBoxeador2, &b2) >= 0) strcpy(nom2, b2.nombre);
        printf("%-6d %-20s %-20s %.2f%%\n",
               e.idEmparejamiento, nom1, nom2, e.compatibilidad);
        cont++;
    }
    fclose(f);

    if (cont == 0) printf("No hay emparejamientos registrados.\n");
    printf("\n");
}