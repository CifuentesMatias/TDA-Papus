#ifndef DESARROLLO_H_INCLUDED
#define DESARROLLO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//declaro mis estructuras para los archivos

typedef struct{
    char Codigo[21];
    char Descripcion[31];
    char Clasificador[31];
    double Indice_ipc;//accede con %lf
    double v_m_ipc;
    double v_i_a_IPC;
    char region[10];
    char Periodo_codificado[7];
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

//declaro mis funciones

void decodificarFecha(char *periodo);

#endif // DESARROLLO_H_INCLUDED
