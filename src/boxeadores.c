#include "boxeadores.h"
#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* categorias[6] = {
    "Mosca",
    "Pluma",
    "Ligero",
    "Welter",
    "Medio",
    "Pesado"
};

void asignar_categoria(Boxeador *b) {
    if (b->peso <= 52.0f) {
        strcpy(b->categoria, categorias[0]);
    } else if (b->peso <= 57.0f) {
        strcpy(b->categoria, categorias[1]);
    } else if (b->peso <= 63.5f) {
        strcpy(b->categoria, categorias[2]);
    } else if (b->peso <= 69.0f) {
        strcpy(b->categoria, categorias[3]);
    } else if (b->peso <= 75.0f) {
        strcpy(b->categoria, categorias[4]);
    } else {
        strcpy(b->categoria, categorias[5]);
    }
}

int siguiente_id() {
    FILE *f = fopen("boxeadores.dat", "rb");
    int max_id = 0;
    if (f != NULL) {
        Boxeador b;
        while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
            if (b.id > max_id) {
                max_id = b.id;
            }
        }
        fclose(f);
    }
    return max_id + 1;
}

long boxeador_existe_id(int id, Boxeador *encontrado) {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b;
        while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
            if (b.id == id && b.activo == 1) {
                long pos = ftell(f) - (long)sizeof(Boxeador);
                if (encontrado != NULL) {
                    *encontrado = b;
                }
                fclose(f);
                return pos;
            }
        }
        fclose(f);
    }
    return -1;
}

long boxeador_existe(const char *nombre, Boxeador *encontrado) {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f != NULL) {
        Boxeador b;
        while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
            if (strcmp(b.nombre, nombre) == 0 && b.activo == 1) {
                long pos = ftell(f) - (long)sizeof(Boxeador);
                if (encontrado != NULL) {
                    *encontrado = b;
                }
                fclose(f);
                return pos;
            }
        }
        fclose(f);
    }
    return -1;
}

void agregar_boxeador() {
    Boxeador b;

    b.id = siguiente_id();

    // hice un loop para evitar duplicados
    do {
        printf("Ingrese nombre: ");
        pedir_nombre(b.nombre, sizeof(b.nombre));
        if (boxeador_existe(b.nombre, NULL) >= 0) {
            printf("  Error: ya existe un boxeador activo con ese nombre. Intente otro.\n");
        } else {
            break;
        }
    } while (1);

    printf("Ingrese peso (kg): ");
    b.peso = pedir_peso();

    printf("Ingrese victorias: ");
    b.record.victorias = pedir_entero_positivo("victorias");

    printf("Ingrese derrotas: ");
    b.record.derrotas = pedir_entero_positivo("derrotas");

    b.record.totalPeleas = b.record.victorias + b.record.derrotas;
    if (b.record.totalPeleas > 0) {
        b.record.indiceVictorias = (float)b.record.victorias / b.record.totalPeleas * 100.0f;
    } else {
        b.record.indiceVictorias = 0.0f;
    }
    b.activo = 1;
    asignar_categoria(&b);

    FILE *f = fopen("boxeadores.dat", "ab");
    if (f != NULL) {
        fwrite(&b, sizeof(Boxeador), 1, f);
        fclose(f);
        printf("Boxeador '%s' agregado con ID %d.\n\n", b.nombre, b.id);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

//lo de id
void buscar_boxeador() {
    printf("Ingrese el ID del boxeador: ");
    int id = pedir_id("ID"); 
 
    Boxeador b;
    long pos = boxeador_existe_id(id, &b);
    if (pos >= 0) {
        printf("\n%-5s %-20s %-8s %-12s %-5s %-7s %-10s\n",
               "ID", "Nombre", "Peso", "Categoria", "Vic", "Der", "Ind.Vic%");
        printf("------------------------------------------------------------------\n"); // no se si dejarla esta madre
        printf("%-5d %-20s %-8.2f %-12s %-5d %-7d %-10.2f\n",
               b.id, b.nombre, b.peso, b.categoria,
               b.record.victorias, b.record.derrotas, b.record.indiceVictorias);
    } else {
        printf("Boxeador con ID %d no encontrado o inactivo.\n", id);
    }
}
 
// solo hice que usara la funcion de ID
void modificar_boxeador() {
    printf("Ingrese el ID del boxeador a modificar: ");
    int id = pedir_id("ID"); // te ahorre el scanf y el getchar enn pocas palabras
 
    Boxeador b;
    long pos = boxeador_existe_id(id, &b);
    if (pos < 0) { 
        printf("Boxeador con ID %d no encontrado o inactivo.\n", id);
        return;
    }
 
    FILE *f = fopen("boxeadores.dat", "r+b");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
 
   // solo busca si el nombre esta duplicado
    char tmp[50];
    do {
        printf("Nuevo nombre (%s): ", b.nombre);
        pedir_nombre(tmp, sizeof(tmp));
        if (strcmp(tmp, b.nombre) != 0) {
            Boxeador existente;
            long pos_dup = boxeador_existe(tmp, &existente);
            if (pos_dup >= 0 && existente.id != b.id) {
                printf("  Error: ya existe un boxeador activo con ese nombre. Intente otro.\n");
                continue;
            }
        }
        break;
    } while (1);
    strcpy(b.nombre, tmp);
 

    printf("Nuevo peso (actual %.2f kg): ", b.peso);
    b.peso = pedir_peso();
 
    printf("Nuevas victorias (actual %d): ", b.record.victorias);
    b.record.victorias = pedir_entero_positivo("victorias");
 
    printf("Nuevas derrotas (actual %d): ", b.record.derrotas);
    b.record.derrotas = pedir_entero_positivo("derrotas");
 
    b.record.totalPeleas = b.record.victorias + b.record.derrotas;
    b.record.indiceVictorias = (b.record.totalPeleas > 0)
        ? (float)b.record.victorias / b.record.totalPeleas * 100.0f
        : 0.0f;
    asignar_categoria(&b);
 
    fseek(f, pos, SEEK_SET);
    fwrite(&b, sizeof(Boxeador), 1, f);
    fclose(f);
    printf("Boxeador modificado correctamente.\n\n");
}
 
//  lo del id
void eliminar_boxeador() {
    printf("Ingrese el ID del boxeador a eliminar: ");
    int id = pedir_id("ID"); 
 
    Boxeador b;
    long pos = boxeador_existe_id(id, &b);
    if (pos < 0) {
        printf("Boxeador con ID %d no encontrado o ya inactivo.\n", id);
        return;
    }
 
    // solo una confirmacion que pues no cuesta nada 
    char op[4];
    printf("Seguro que desea eliminar a '%s'? (s/n): ", b.nombre);
    fgets(op, sizeof(op), stdin);
    if (op[0] != 's' && op[0] != 'S') {
        printf("Operacion cancelada.\n\n");
        return;
    }
 
    FILE *f = fopen("boxeadores.dat", "r+b");
    if (f != NULL) {
        b.activo = 0;
        fseek(f, pos, SEEK_SET);
        fwrite(&b, sizeof(Boxeador), 1, f);
        fclose(f);
        printf("Boxeador '%s' eliminado.\n\n", b.nombre);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}
 
// los scanf de ID los reemplace por la funcion que te dije que haria
void registrar_resultado() {
    printf("Ingrese ID del ganador: ");
    int id_ganador = pedir_id("ID ganador");   
 
    printf("Ingrese ID del perdedor: ");
    int id_perdedor = pedir_id("ID perdedor"); 
 
    if (id_ganador == id_perdedor) {
        printf("Error: el ganador y el perdedor no pueden ser el mismo boxeador.\n");
        return;
    }
 
    Boxeador bg, bp;
    long pos_g = boxeador_existe_id(id_ganador, &bg);
    long pos_p = boxeador_existe_id(id_perdedor, &bp);
 
    if (pos_g < 0 || pos_p < 0) {
        printf("Error: uno o ambos boxeadores no existen o estan inactivos.\n");
        return;
    }
 
   //solo una advertencia just in case bby asi si falla el codigo parece que esta built in esta madre ;D
    if (strcmp(bg.categoria, bp.categoria) != 0) {
        printf("Advertencia: los boxeadores son de distinta categoria (%s vs %s).\n",
               bg.categoria, bp.categoria);
        char op[4];
        printf("Desea continuar de todas formas? (s/n): ");
        fgets(op, sizeof(op), stdin);
        if (op[0] != 's' && op[0] != 'S') {
            printf("Operacion cancelada.\n\n");
            return;
        }
    }
 
    char res[20];
    printf("Ingrese resultado (KO, TKO, Decision): ");
    pedir_resultado(res, sizeof(res));
 
    FILE *f = fopen("boxeadores.dat", "r+b");
    if (f != NULL) {
        bg.record.victorias++;
        bg.record.totalPeleas++;
        bg.record.indiceVictorias = (float)bg.record.victorias / bg.record.totalPeleas * 100.0f;
        fseek(f, pos_g, SEEK_SET);
        fwrite(&bg, sizeof(Boxeador), 1, f);
 
        bp.record.derrotas++;
        bp.record.totalPeleas++;
        bp.record.indiceVictorias = (float)bp.record.victorias / bp.record.totalPeleas * 100.0f;
        fseek(f, pos_p, SEEK_SET);
        fwrite(&bp, sizeof(Boxeador), 1, f);
 
        fclose(f);
 
        Resultado r;
        r.id = id_ganador * 100 + id_perdedor;
        strncpy(r.ganador,   bg.nombre, sizeof(r.ganador)   - 1);
        strncpy(r.perdedor,  bp.nombre, sizeof(r.perdedor)  - 1);
        strncpy(r.resultado, res,       sizeof(r.resultado) - 1);
        r.ganador[sizeof(r.ganador)     - 1] = '\0';
        r.perdedor[sizeof(r.perdedor)   - 1] = '\0';
        r.resultado[sizeof(r.resultado) - 1] = '\0';
 
        FILE *fr = fopen("resultados.dat", "ab");
        if (fr != NULL) {
            fwrite(&r, sizeof(Resultado), 1, fr);
            fclose(fr);
        }
        printf("Resultado registrado: %s gano a %s por %s.\n\n",
               bg.nombre, bp.nombre, res);
    } else {
        printf("Error al abrir archivo.\n");
    }
}
 

void listar_boxeadores_activos() {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f == NULL) { 
        printf("Error al abrir el archivo.\n");
        return;
    }
 
    Boxeador b;
    int cont = 0;
    printf("\n%-5s %-20s %-8s %-12s %-5s %-7s %-10s\n",
           "ID", "Nombre", "Peso", "Categoria", "Vic", "Der", "Ind.Vic%");
    printf("------------------------------------------------------------------\n");
    while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
        if (b.activo == 1) {
            cont++;
            printf("%-5d %-20s %-8.2f %-12s %-5d %-7d %-10.2f\n",
                   b.id, b.nombre, b.peso, b.categoria,
                   b.record.victorias, b.record.derrotas, b.record.indiceVictorias);
        }
    }
    fclose(f);
 
    if (cont == 0) {
        printf("No hay boxeadores activos.\n");
    } else {
        printf("------------------------------------------------------------------\n");
        printf("Total: %d boxeadores activos.\n\n", cont);
    }
}
 