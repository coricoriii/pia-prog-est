#include "boxeadores.h"
#include <stdio.h>
#include <stdlib.h>

int id_max = 1; // Inicializar el ID máximo
const char* categorias[3] = {
    "Peso Ligero",
    "Peso Mediano",
    "Peso Pesado"
};

void agregar_boxeador() {
    Boxeador b;
    // Creando el boxeador
    printf("Ingrese nombre: ");
    scanf("%s", b.nombre);
    printf("Ingrese peso: ");
    scanf("%f", &b.peso);
    printf("Ingrese cantidad de victorias: ");
    scanf("%d", &b.record.victorias);
    printf("Ingrese cantidad de derrotas: ");
    scanf("%d", &b.record.derrotas);
    b.id = id_max++; // Asignar un ID único
    b.record.totalPeleas = b.record.victorias + b.record.derrotas;
    b.record.indiceVictorias = (float)b.record.victorias / b.record.totalPeleas;
    b.activo = 1;
    // Aqui se guardaria el boxeador en la base de datos
    FILE *f = fopen("boxeadores.dat", "ab");
    if (f != NULL) {
        fwrite(&b, sizeof(Boxeador), 1, f);
        fclose(f);
        printf("Boxeador agregado con ID: %d\n", b.id);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

