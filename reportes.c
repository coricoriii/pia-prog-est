#include <stdio.h>
#include <stdlib.h>
#include "reportes.h"
#include "boxeadores.h"
#include "emparejamientos.h"

void reporte_boxeadores() {
    // Convertir archivo binario en txt
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b;
        FILE *txt = fopen("boxeadores.txt", "w");
        if (txt != NULL) {
            fprintf(txt, "Nombre\tPeso\tCategoria\tVictorias\tDerrotas\tIndice de Victorias\n");
            while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
                if (b.activo) {
                    fprintf(txt, "%s\t%.2f\t%s\t%d\t%d\t%.2f%%\n", 
                        b.nombre, b.peso, b.categoria, 
                        b.record.victorias, b.record.derrotas, 
                        b.record.indiceVictorias * 100);
                }
            }
            fclose(txt);
            printf("Reporte generado en 'boxeadores.txt'\n");
        } else {
            printf("Error al crear el archivo de texto.\n");
        }
        fclose(f);
    } else {
        printf("Error al abrir el archivo de boxeadores.\n");
    }
}

void reporte_emparejamientos() {
    // Convertir archivo binario en txt
    FILE *f = fopen("emparejamientos.dat", "rb");
    if (f != NULL) {
        Emparejamiento e;
        FILE *txt = fopen("emparejamientos.txt", "w");
        if (txt != NULL) {
            fprintf(txt, "Boxeador 1\tBoxeador 2\tCompatibilidad\n");
            while (fread(&e, sizeof(Emparejamiento), 1, f) == 1) {
                fprintf(txt, "%s\t%s\t%.2f%%\n", e.boxeador1, e.boxeador2, e.compatibilidad);
            }
            fclose(txt);
            printf("Reporte generado en 'emparejamientos.txt'\n");
        } else {
            printf("Error al crear el archivo de texto.\n");
        }
        fclose(f);
    } else {
        printf("Error al abrir el archivo de emparejamientos.\n");
    }
}

void estadisticas_generales() {
    // Calcular estadisticas generales como total de boxeadores, victorias totales, etc
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b;
        int totalBoxeadores = 0;
        int totalVictorias = 0;
        int totalDerrotas = 0;
        while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
            if (b.activo) {
                totalBoxeadores++;
                totalVictorias += b.record.victorias;
                totalDerrotas += b.record.derrotas;
            }
        }
        fclose(f);
        printf("\n===== ESTADISTICAS GENERALES =====\n");
        printf("Total de boxeadores activos: %d\n", totalBoxeadores);
        printf("Total de victorias: %d\n", totalVictorias);
        printf("Total de derrotas: %d\n", totalDerrotas);
        printf("Indice de victorias general: %.2f%%\n", 
            (totalVictorias + totalDerrotas) > 0 ? 
            ((float)totalVictorias / (totalVictorias + totalDerrotas)) * 100 : 0);
    } else {
        printf("Error al abrir el archivo de boxeadores.\n");
    }
}