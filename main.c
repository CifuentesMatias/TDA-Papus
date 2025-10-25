#include "Desarrollo.h"
//PUNTOS QUE ANDAN BIEN, BIEN A PELO = {(1),(2),(3),(4),(5)}
int main()
{
    Vector vec;
    crearVector(&vec,sizeof(Tdivisiones),50);
    bajarArchivoAVector("serie_ipc_divisiones.csv",&vec,cmpCod);
//    recorrerVector(&vec,mostrarCliente,NULL);
    calcularMontoAjustado(&vec);
    destruirVector(&vec);
    return 0;
}
