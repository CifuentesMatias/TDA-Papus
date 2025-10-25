#include "Desarrollo.h"

void decodificarFecha(char *periodo) //punto 1
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

void reescribirFecha(char *fechaNum) //punto 2
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

void normalizarDescripcion(char *cadena) //punto 3
{
    char *aux=cadena;
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

void comaAPunto(char *cadena) //punto 4 y 8
{
    char *aux = cadena;
    while(*aux != '\0')
    {
        if(*aux == ',')
            *aux = '.';
        aux++;
    }
}

double calcularMontoAjustado(Vector *vec) //punto 5
{
    double monto, indiceDesde, indiceHasta, montoAjustado, variacion;
    int opcion;
    char region[10];
    char periodoDesde[7], periodoHasta[7];
    //pido monto al usuario
    printf("Ingrese el monto inicial(en pesos):");
    scanf("%lf", &monto);

    do
    {
        printf("\nSeleccione la region:\n 1. Nacional\n 2. GBA\n 3. Pampeana\n 4. Cuyo\n 5. Noroeste\n 6. Noreste\n 7. Patagonia\n");
        scanf("%d", &opcion);
    }while(opcion<1 || opcion>7);

    switch (opcion)
    {
        case 1: strcpy(region, "Nacional"); break;
        case 2: strcpy(region, "GBA"); break;
        case 3: strcpy(region, "Pampeana"); break;
        case 4: strcpy(region, "Cuyo"); break;
        case 5: strcpy(region, "Noroeste"); break;
        case 6: strcpy(region, "Noreste"); break;
        case 7: strcpy(region, "Patagonia"); break;
    }

    printf("\nIngrese el periodo desde (formato AAAAMM): ");
    scanf("%6s", periodoDesde);
    reescribirFecha(periodoDesde);
    printf("Ingrese el periodo hasta (formato AAAAMM): ");
    scanf("%6s", periodoHasta);
    reescribirFecha(periodoHasta);

    for(int i=0;i<vec->ce;i++)
    {
        Tdivisiones *dato=(Tdivisiones*)((char*)vec->vec+i*vec->tamElem);
        if(strcmp(dato->Descripcion,"Nivel general")==0 && strcmp(dato->region,region)==0)
        {
            if(strcmp(dato->Periodo_codificado, periodoDesde)==0)
                indiceDesde=dato->Indice_ipc;
            else if(strcmp(dato->Periodo_codificado,periodoHasta)==0)
                indiceHasta=dato->Indice_ipc;
        }
    }

    montoAjustado=monto*(indiceHasta/indiceDesde);
    variacion=(indiceHasta/(indiceDesde-1))*100;
    system("cls");
    printf("\nRegion: %s\nPeriodo desde: %s\tIndice desde: %.2f\nPeriodo hasta: %s\tIndice hasta: %.2f\nMonto inicial: $%.2lf\nMonto ajustado: $%.2lf\nVariacion(porcentual): %.2lf", region, periodoDesde, indiceDesde, periodoHasta, indiceHasta, monto, montoAjustado, variacion);

    return montoAjustado;
}

int leoTxtDivisiones(FILE *pt, Tdivisiones *divi)
{
    char linea[LONGFILE];
    char *aux;

    if(!fgets(linea, LONGFILE, pt))
        return ERROR;

    aux = strchr(linea, '\n');
    if(aux)
        *aux = '\0';

    aux = strrchr(linea, ';');
    printf("%s",aux);
    if(!aux) return ERROR;
    sscanf(aux + 1, "%s", divi->Periodo_codificado);
    *aux = '\0';

    aux = strrchr(linea, ';');
    if(!aux) return ERROR;
    sscanf(aux + 1, "%s", divi->region);
    *aux = '\0';

    aux = strrchr(linea, ';');
    if(!aux) return ERROR;
    sscanf(aux + 1, "%lf", &divi->v_i_a_IPC);
    *aux = '\0';

    aux = strrchr(linea, ';');
    if(!aux) return ERROR;
    sscanf(aux + 1, "%lf", &divi->v_m_ipc);
    *aux = '\0';

    aux = strrchr(linea, ';');
    if(!aux) return ERROR;
    sscanf(aux + 1, "%lf", &divi->Indice_ipc);
    *aux = '\0';

    aux = strrchr(linea, ';');
    if(!aux) return ERROR;
    sscanf(aux + 1, "%s", divi->Clasificador);
    *aux = '\0';

    aux = strrchr(linea, ';');
    if(!aux) return ERROR;
    sscanf(aux + 1, "%s", divi->Descripcion);
    *aux = '\0';

    sscanf(linea, "%s", divi->Codigo);

    return OK;
}

int bajarArchivoAVector(char *nombre, Vector *vec, cmp Comparar)
{
    Tdivisiones reg;
    FILE *pf= fopen(nombre,"r");
    if(!pf)
        return ERROR;

    while(leoTxtDivisiones(pf,&reg)==OK)
    {
        insertarVecEnOrd(vec,&reg,Comparar);//COMO ES GENERICO NECESITAMOS UNA FUNCION DE COMPARACION
    }
    fclose(pf);
    return OK;
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
        return ERROR;

    vec->cap = cap;
    vec->ce  = 0;
    vec->tamElem = tamElem;

    return OK;
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
            return ERROR;
        vec->vec=aux;
        vec->cap=ncap;
    }
   void *ult = vec->vec + (vec->ce - 1)* vec->tamElem;
   void *act = vec->vec;
   int comparo;

   while(act<=ult && (comparo=cmp(act,elem))<0) //funcion de comparacion para el generico
       act += vec->tamElem;

    if(act<=ult && comparo==0)
        return ERROR;

   /// Puede que salga del while porque llego al ultimo o
   memmove(act+vec->tamElem , act , ult - act + vec->tamElem);
   memcpy(act,elem,vec->tamElem);

   vec->ce++;
   return OK;
}

void destruirVector(Vector *vec)
{
    free(vec->vec);
    vec->ce=0;
}
