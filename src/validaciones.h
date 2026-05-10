#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#ifdef __cplusplus
extern "C" {
#endif

int validar_nombre(const char *nombre);
int validar_peso(float peso);
int validar_entero_positivo(int n);
int validar_resultado(const char *res);
void pedir_nombre(char *buf, int tam);
float pedir_peso();
int pedir_entero_positivo(const char *msg);
void pedir_resultado(char *buf, int tam);

#ifdef __cplusplus
}
#endif
#endif
