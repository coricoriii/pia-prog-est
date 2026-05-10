#ifndef EMPAREJAMIENTOS_H
#define EMPAREJAMIENTOS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int idEmparejamiento;
    int idBoxeador1;
    int idBoxeador2;
    float compatibilidad;
} Emparejamiento;

void mejor_rival();
void mostrar_matriz();
void ver_emparejamientos();
void guardar_emparejamiento(int id1, int id2, float comp);

#ifdef __cplusplus
}
#endif
#endif
