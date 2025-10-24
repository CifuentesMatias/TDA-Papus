#include "Desarrollo.h"

void decodificarFecha(char *periodo) //leo el contenido de cada posicion que troce para "periodo" y segun su valor le asigno otro
{
    char *aux=periodo;//auxiliar con el contenido de las posiciones en "periodo"
    while(*aux!='\0'){
        switch(*aux){
            case '7': *aux='0'; break;
            case '4': *aux='1'; break;
            case '9': *aux='2'; break;
            case '8': *aux='3'; break;
            case '0': *aux='4'; break;
            case '6': *aux='5'; break;
            case '1': *aux='6'; break;
            case '3': *aux='7'; break;
            case '2': *aux='8'; break;
            default: break;
        }
        aux++;
    }
}

int mi_atoi(char *cadena){
    int num = 0;
    while (*cadena) {
        if (*cadena >= '0' && *cadena <= '9') {
            num = num * 10 + (*cadena - '0');
        }
        cadena++;
    }
    return num;
}


void reescribirFecha(char *fechaNum)
{
    char *aux;
    int fecha = mi_atoi(fechaNum);
    int anio = fecha / 100;
    int mes = fecha % 100;
    int i = 0,j=0, auxi=1000;

    switch(mes)
    {
        case 1: aux = "Enero"; break;
        case 2: aux = "Febrero"; break;
        case 3: aux = "Marzo"; break;
        case 4: aux = "Abril"; break;
        case 5: aux = "Mayo"; break;
        case 6: aux = "Junio"; break;
        case 7: aux = "Julio"; break;
        case 8: aux = "Agosto"; break;
        case 9: aux = "Septiembre"; break;
        case 10: aux = "Octubre"; break;
        case 11: aux = "Noviembre"; break;
        case 12: aux = "Diciembre"; break;
        default: printf("Mes no valido"); break;
    }


    while (*(aux+j) != '\0')
    {
        *(fechaNum+i) = *(aux+j);
        i++;
        j++;
    }
    *(fechaNum+i) = ' - ';
    i++;
    for(int j=0;j<4;j++)
    {
        *(fechaNum+i++)=(char*)(anio/auxi);
        anio-=(anio/auxi)*auxi;
        auxi=auxi/10;
    }
    *(fechaNum+i) = '\0';
}
