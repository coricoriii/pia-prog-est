#ifndef EMPAREJAMIENTOS_H
#define EMPAREJAMIENTOS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char boxeador1[50];
    char boxeador2[50];
    float compatibilidad;
} Emparejamiento;

void mejor_rival();
void mostrar_matriz();
void ver_emparejamientos();

#ifdef __cplusplus
}
#endif
#endif 