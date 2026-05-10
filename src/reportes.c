#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reportes.h"
#include "boxeadores.h"
#include "emparejamientos.h"

void reporte_boxeadores() {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir boxeadores.dat\n");
        return;
    }

    Boxeador lista[MAX_BOXEADORES];
    int cont = 0;
    Boxeador b;

    while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
        if (b.activo == 1) {
            lista[cont] = b;
            cont++;
        }
    }
    fclose(f);

    for (int i = 0; i < cont - 1; i++) {
        for (int j = i + 1; j < cont; j++) {
            if (lista[j].record.indiceVictorias > lista[i].record.indiceVictorias) {
                Boxeador tmp = lista[i];
                lista[i] = lista[j];
                lista[j] = tmp;
            }
        }
    }

    FILE *txt = fopen("ranking_boxeadores.txt", "w");
    if (txt == NULL) {
        printf("Error al crear ranking_boxeadores.txt\n");
        return;
    }

    fprintf(txt, "%-6s %-20s %-8s %-12s %-5s %-7s %-10s\n",
            "Rank", "Nombre", "Peso", "Categoria", "Vic", "Der", "Ind.Vic%");
    fprintf(txt, "--------------------------------------------------------------\n");

    for (int i = 0; i < cont; i++) {
        fprintf(txt, "%-6d %-20s %-8.2f %-12s %-5d %-7d %-10.2f\n",
                i + 1, lista[i].nombre, lista[i].peso, lista[i].categoria,
                lista[i].record.victorias, lista[i].record.derrotas,
                lista[i].record.indiceVictorias);
    }
    fclose(txt);
    printf("Ranking generado en 'ranking_boxeadores.txt'\n");

    printf("\n%-6s %-20s %-8s %-12s %-5s %-7s %-10s\n",
           "Rank", "Nombre", "Peso", "Categoria", "Vic", "Der", "Ind.Vic%");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < cont; i++) {
        printf("%-6d %-20s %-8.2f %-12s %-5d %-7d %-10.2f\n",
               i + 1, lista[i].nombre, lista[i].peso, lista[i].categoria,
               lista[i].record.victorias, lista[i].record.derrotas,
               lista[i].record.indiceVictorias);
    }
    printf("\n");
}

void reporte_emparejamientos() {
    FILE *f = fopen("emparejamientos.dat", "rb");
    if (f == NULL) {
        printf("No hay emparejamientos registrados.\n");
        return;
    }

    FILE *txt = fopen("reporte_emparejamientos.txt", "w");
    if (txt == NULL) {
        printf("Error al crear reporte_emparejamientos.txt\n");
        fclose(f);
        return;
    }

    fprintf(txt, "%-6s %-20s %-20s %-15s\n", "ID", "Boxeador 1", "Boxeador 2", "Compatibilidad");
    fprintf(txt, "------------------------------------------------------------\n");

    Emparejamiento e;
    int cont = 0;
    while (fread(&e, sizeof(Emparejamiento), 1, f) == 1) {
        Boxeador b1, b2;
        char nom1[50] = "Desconocido";
        char nom2[50] = "Desconocido";
        if (boxeador_existe_id(e.idBoxeador1, &b1) >= 0) {
            strcpy(nom1, b1.nombre);
        }
        if (boxeador_existe_id(e.idBoxeador2, &b2) >= 0) {
            strcpy(nom2, b2.nombre);
        }
        fprintf(txt, "%-6d %-20s %-20s %.2f%%\n",
                e.idEmparejamiento, nom1, nom2, e.compatibilidad);
        cont++;
    }
    fclose(f);
    fclose(txt);

    if (cont == 0) {
        printf("No hay emparejamientos para reportar.\n");
    } else {
        printf("Reporte generado en 'reporte_emparejamientos.txt'\n");
    }
}

void estadisticas_generales() {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir boxeadores.dat\n");
        return;
    }

    Boxeador b;
    int total = 0;
    float sumaIndice = 0.0f;
    float sumaPeso = 0.0f;
    float maxIndice = -1.0f;
    char mejorNombre[50] = "";
    int contCat[6] = {0, 0, 0, 0, 0, 0};

    while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
        if (b.activo == 1) {
            total++;
            sumaIndice += b.record.indiceVictorias;
            sumaPeso += b.peso;

            if (b.record.indiceVictorias > maxIndice) {
                maxIndice = b.record.indiceVictorias;
                strcpy(mejorNombre, b.nombre);
            }

            for (int i = 0; i < 6; i++) {
                if (strcmp(b.categoria, categorias[i]) == 0) {
                    contCat[i]++;
                }
            }
        }
    }
    fclose(f);

    if (total == 0) {
        printf("No hay boxeadores activos.\n");
        return;
    }

    int catMax = 0;
    for (int i = 1; i < 6; i++) {
        if (contCat[i] > contCat[catMax]) {
            catMax = i;
        }
    }

    printf("\n===== ESTADISTICAS GENERALES =====\n");
    printf("Total de boxeadores activos : %d\n", total);
    printf("Promedio de indice victoria : %.2f%%\n", sumaIndice / total);
    printf("Mejor boxeador              : %s (%.2f%%)\n", mejorNombre, maxIndice);
    printf("Categoria con mas boxeadores: %s (%d)\n", categorias[catMax], contCat[catMax]);
    printf("Promedio de peso            : %.2f kg\n\n", sumaPeso / total);
}
