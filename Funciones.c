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
