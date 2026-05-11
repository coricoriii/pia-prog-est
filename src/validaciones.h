#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#ifdef __cplusplus
extern "C" {
#endif

//hola cori solo para decir que aqui las validaciones regresan valores como0 de invalido y 1 de valido
int validar_nombre(const char *nombre);
int validar_peso(float peso);
int validar_entero_positivo(int n);
int validar_resultado(const char *res);
int validar_id(int id);

// aca son solo los loops hasta que se ponga algo valido 
void  pedir_nombre(char *buf, int tam);
float pedir_peso(void);
int   pedir_entero_positivo(const char *msg);
void  pedir_resultado(char *buf, int tam);
int   pedir_id(const char *msg);

#ifdef __cplusplus
}
#endif

#endif 