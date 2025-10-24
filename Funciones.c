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

void leoTxtDivisiones(FILE *pt, Tdivisiones *divi) //lactura primer archivo
{
    char linea[LONGFILE];
    fgets(linea, LONGFILE, pt);
    char *act = strchr(linea, '\n');
    if(!act)
        act = strchr(linea, '\0');
    *act = '\0';

    act -= 6;
    strncpy(divi->Periodo_codificado, act, 6);
    divi->Periodo_codificado[6] = '\0';
    *act = '\0';

    act -= 9;
    strncpy(divi->region, act, 9);
    divi->region[9] = '\0';
    *act = '\0';

    act -= 16;
    sscanf(act, "%lf", &divi->v_i_a_IPC);
    *act = '\0';

    act -= 16;
    sscanf(act, "%lf", &divi->v_m_ipc);
    *act = '\0';
    
    act -= 16;
    /*
    strncpy(aux, act, 16);      PARA EL PUNTO 4 YO LO HARIA ASI
    aux[16] = '\0';
    comaApunto(aux);
    */
    sscanf(act, "%lf", &divi->Indice_ipc);
    *act = '\0';

    act -= 30;
    strncpy(divi->Clasificador, act, 30);
    divi->Clasificador[30] = '\0';
    *act = '\0';

    act -= 30;
    strncpy(divi->Descripcion, act, 30);
    divi->Descripcion[30] = '\0';
    *act = '\0';

    act -= 20;
    strncpy(divi->Codigo, act, 20);
    divi->Codigo[20] = '\0';
}

void nomralizardesc(char * v) //punto 3
{
    char *aux=v;
    int pri=0; //control primera letra
    while(*aux!='\0')
    {
        if(*aux>='A' && *aux<='Z' && pri!=0)
            *aux=*aux-'A'+'a';
        else if(pri==0 && *aux >= 'a' && *aux <= 'z')
            *aux=*aux-'a'+'A';
        aux++;
        pri=1;
    }
}

void comaApunto(char *v) //punto 4 y 8
{
    char *aux = v;
    while(*aux != '\0')
    {
        if(*aux == ',')
            *aux = '.';
        aux++;
    }
}

void mi_strncpy(char *dest, const char *src, int n)
{
    int i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
}


double calcularMontoAjustado(Tdivisiones *divi) //punto 5
{
    double monto;
    int opcion;
    char region[15];
    char desde[7], hasta[7];

    printf("Ingrese el monto: $ ");
    scanf("%lf", &monto);
    
    do
    {
        printf("\nSeleccione la region:\n 1. Nacional\n 2. GBA\n 3. Pampeana\n 4. Cuyo\n 5. Noroeste\n 6. Noreste\n 7. Patagonia\n");
        scanf("%d", &opcion);
    }while(opcion<1||opcion>7)

    switch (opcion) 
    {
        case 1:
            strcpy(region, "Nacional");
            break;
        case 2:
            strcpy(region, "GBA");
            break;
        case 3:
            strcpy(region, "Pampeana");
            break;
        case 4:
            strcpy(region, "Cuyo");
            break;
        case 5: 
            strcpy(region, "Noroeste");
            break;
        case 6:
            strcpy(region, "Noreste");
            break;
        case 7: 
            strcpy(region, "Patagonia");
            break;
    }

    printf("\nIngrese el periodo desde (formato AAAAMM): ");
    scanf("%6s", desde);
    printf("Ingrese el periodo hasta (formato AAAAMM): ");
    scanf("%6s", hasta);
    
    //mi cara cuando leo el resto del punto 5 6 y 9 (⊙_⊙)


}

void leoTxtAperturas(FILE *pt, Taperturas *ap) //lectura segundo archivo
{
    char linea[LONGFILE];
    fgets(linea, LONGFILE, pt);
    char *act = strchr(linea, '\n');
    if(!act)
        act = strchr(linea, '\0');
    *act = '\0';

    act -= 9;
    strncpy(ap->region, act, 9);
    ap->region[9] = '\0';
    *act = '\0';

    act -= 16;
    sscanf(act, "%lf", &ap->v_i_a_IPC);
    *act = '\0';

    act -= 16;
    sscanf(act, "%lf", &ap->v_m_ipc);
    *act = '\0';

    act -= 16;
    /*
    strncpy(aux, act, 16);      PARA EL PUNTO 8 YO LO HARIA ASI
    aux[16] = '\0';
    comaApunto(aux);
    */
    sscanf(act, "%lf", &ap->Indice_ipc);
    *act = '\0';

    act -= 6;
    strncpy(ap->Periodo, act, 6);
    ap->Periodo[6] = '\0';
    *act = '\0';

    act -= 30;
    strncpy(ap->Clasificador, act, 30);
    ap->Clasificador[30] = '\0';
    *act = '\0';

    act -= 30;
    strncpy(ap->Descripcion_aperturas, act, 30);
    ap->Descripcion_aperturas[30] = '\0';
    *act = '\0';

    act -= 20;
    strncpy(ap->Codigo, act, 20);
    ap->Codigo[20] = '\0';
}
