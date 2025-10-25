#ifndef DESARROLLO_H_INCLUDED
#define DESARROLLO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONGFILE 150
#define ERROR 1
#define OK 0

//declaro mis estructuras para los archivos

typedef struct{
    char Codigo[21];
    char Descripcion[31];
    char Clasificador[31];
    double Indice_ipc;//accede con %lf
    double v_m_ipc;
    double v_i_a_IPC;
    char region[10];
    char Periodo_codificado[20];
}Tdivisiones;

typedef struct{
    char Codigo[21];
    char Descripcion_aperturas[31];
    char Clasificador[31];
    char Periodo[7];
    double Indice_ipc;//accede con %lf
    double v_m_ipc;
    double v_i_a_IPC;
    char region[10];
}Taperturas;

//bajar archivo a vectorgaming

typedef struct
{
    void *vec;
    size_t tamElem;
    int ce;
    int cap;
}Vector;

typedef int (*cmp)(const void*, const void*);
typedef void(*Accion)(const void *,const void *);

int cmpCod(const void*a, const void*b);
int  crearVector(Vector * vec, size_t tamElem , int cap);
int  insertarVecEnOrd(Vector *vec , const void *elem ,cmp cmp);
void recorrerVector(Vector *vec, Accion accion, void *datosAccion);
void destruirVector(Vector * vec);

int bajarArchivoAVector(char *nombre, Vector *vec, cmp Comparar);

//declaro mis funciones

int leoTxtDivisiones(FILE *pt, Tdivisiones *divi);
void decodificarFecha(char *periodo);
void reescribirFecha(char *fechaNum);
int mi_atoi(char *cadena);
void normalizarDescripcion(char *cadena);
void comaAPunto(char *cadena);
double calcularMontoAjustado(Vector *vec);
void eliminarComillas(char*linea);

#endif // DESARROLLO_H_INCLUDED
