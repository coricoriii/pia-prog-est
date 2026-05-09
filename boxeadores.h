#ifndef BOXEADORES_H
#define BOXEADORES_H

#ifdef __cplusplus
extern "C" {
#endif

// Arreglo de categorias 
extern const char* categorias[3];

typedef struct {
    int victorias;
    int derrotas;
    int totalPeleas;
    float indiceVictorias;
} Record;

typedef struct {
    char nombre[50];
    float peso;
    char categoria[20];
    Record record;
    int activo; // 1 para activo, 0 para inactivo
} Boxeador;

// Agregar un nuevo boxeador a la base de datos
void agregar_boxeador();
// Buscar un boxeador por nombre
void buscar_boxeador();
// Modificar los datos de un boxeador
void modificar_boxeador(const char* nombre, Boxeador b);
// Eliminar un boxeador (marcar como inactivo)
void eliminar_boxeador(const char* nombre);
// Registrar el resultado de una pelea
void registrar_resultado(const char* nombre_ganador, const char* nombre_perdedor);
// Listar todos los boxeadores activos
void listar_boxeadores_activos();

#ifdef __cplusplus
}
#endif
#endif 