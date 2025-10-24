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

typedef struct  // partecica del punto 6
{
    char Fecha[11];           
    char Descripcion[31];     
    char Periodo[7];          
    double Indice_IPC;        
    char Region[10];          
    char Grupo[11];     // Bienes: Alimentos y bebidas no alcohólicas, Bebidas alcohólicas y tabaco, Prendas de vestir y calzado, Bienes y servicios varios, Equipamiento y mantenimiento del hogar. 
} Tanalisis_IPC;        //Servicios: Recreación y cultura, Restaurantes y hoteles, Salud, Transporte, Educación, Comunicación, Vivienda, agua, electricidad, gas y otros combustibles.


//declaro mis funciones

void decodificarFecha(char *periodo);
void reescribirFecha(char *fechaNum);
int mi_atoi(char *cadena);

void leoTxtDivisiones(FILE *pt, Tdivisiones *divi);
void nomralizardesc(char *v); //3
void comaApunto(char *v); //4y8
double calcularMontoAjustado(Tdivisiones *divi);//5
void leoTxtAperturas(FILE *pt, Taperturas *ap);
void mi_strncpy(char *dest, const char *src, int n) //por las dudas

#endif // DESARROLLO_H_INCLUDED

