#ifndef BOXEADORES_H
#define BOXEADORES_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_BOXEADORES 100

extern const char* categorias[6];

typedef struct {
    int victorias;
    int derrotas;
    int totalPeleas;
    float indiceVictorias;
} Record;

typedef struct {
    int id;
    char nombre[50];
    float peso;
    char categoria[20];
    Record record;
    int activo;
} Boxeador;

typedef struct {
    int id;
    char ganador[50];
    char perdedor[50];
    char resultado[20];
} Resultado;

void agregar_boxeador();
long boxeador_existe_id(int id, Boxeador *encontrado);
long boxeador_existe(const char *nombre, Boxeador *encontrado);
void buscar_boxeador();
void modificar_boxeador();
void eliminar_boxeador();
void registrar_resultado();
void listar_boxeadores_activos();
int siguiente_id();
void asignar_categoria(Boxeador *b);

#ifdef __cplusplus
}
#endif
#endif
