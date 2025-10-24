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
    *(fechaNum+i) = ' ';
    *(fechaNum+i+1) = '-';
    *(fechaNum+i+2) = ' ';
    i += 3;

    for(int j=0;j<4;j++)
    {
        *(fechaNum+i++)=(anio/auxi)+ '0';
        anio-=(anio/auxi)*auxi;
        auxi=auxi/10;
    }
    *(fechaNum+i) = '\0';
}

int leoTxtDivisiones(FILE *pt, Tdivisiones *divi)
{
    char linea[LONGFILE];

    if(!fgets(linea, LONGFILE, pt))
        return 0; // llegué al final o error

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

    return 1;
}

int bajarArchivoAVector(char *nombre, Vector *vec, cmp Comparar)
{
    Tdivisiones reg;
    FILE *pf= fopen(nombre,"r");
    if(!pf)
        return 1;

    while(leoTxtDivisiones(pf,&reg))
    {
        insertarVecEnOrd(vec,&reg,Comparar);//COMO ES GENERICO NECESITAMOS UNA FUNCION DE COMPARACION
    }
    fclose(pf);
    return 0;
}

int cmpCod(const void*a, const void*b)
{
    Tdivisiones reg1=*(Tdivisiones*)a; //CASTEO A PUNTERO DE ESTRUCTURA Y REG1 LE PONGO EL CONTENIDO DE ESE PUNTERO
    Tdivisiones reg2=*(Tdivisiones*)b;
    return strcmp(reg1.Codigo,reg2.Codigo);
}

void recorrerVector(Vector *vec, Accion accion, void *datosAccion)
{
    void * ult = vec->vec + (vec->ce-1)*vec->tamElem;


    for(void * ini = vec->vec ; ini <=ult ; ini+=vec->tamElem)
        accion(ini,datosAccion);

}

int crearVector(Vector * vec, size_t tamElem , int cap)
{
    vec->vec = malloc(cap*tamElem);

    if(!vec->vec)
        return 1;

    vec->cap = cap;
    vec->ce  = 0;
    vec->tamElem = tamElem;


    return 0;
}

int  insertarVecEnOrd(Vector *vec , const void *elem ,cmp cmp)
{
    //SI ESTA LLENO RE ASIGNA MEMORIA
    if(vec->cap == vec->ce)
    {
        int *aux;
        int ncap=vec->cap*2;
        aux = realloc(vec->vec, vec->tamElem * ncap);
        if(!aux)
            return 1;
        vec->vec=aux;
        vec->cap=ncap;
    }
   void *ult = vec->vec + (vec->ce - 1)* vec->tamElem;
   void *act = vec->vec;
   int comparo;

   while(act<=ult && (comparo=cmp(act,elem))<0) //funcion de comparacion para el generico
       act += vec->tamElem;

    if(act<=ult && comparo==0)
        return 1;

   /// Puede que salga del while porque llego al ultimo o
   memmove(act+vec->tamElem , act , ult - act + vec->tamElem);
   memcpy(act,elem,vec->tamElem);

   vec->ce++;
   return 0;
}

void destruirVector(Vector *vec)
{
    free(vec->vec);
    vec->ce=0;
}
