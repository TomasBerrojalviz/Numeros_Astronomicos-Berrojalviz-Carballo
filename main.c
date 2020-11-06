#include "headers\NUMEROS_ASTRONOMICOS.h"
#include "headers\CREAR_NRO_ASTRONOMICO.h"
#include "headers\ERRORES_NRO_ASTRONOMICO.h"
#include "headers\OPERACIONES_NRO_ASTRONOMICO.h"
#include "headers\ARCHIVOS_NRO_ASTRONOMICO.h"
#include "headers\ARCHIVOS_NRO_ASTRONOMICO.h"


int main(){
    srand(time(NULL));

    int opcionElegida;

    printf("Presentamos una posible ayuda con los numeros astronomicos.\n");

    resetArchivos(); // Resetearemos los archivos borrando los de la ejecucion anterior para que no se generen demasiados.
    system("pause");
    crearContadorArchivos(); // En el caso de que no se haya creado el archivo contador se creara sino se pondra en 0.

    do {
        opcionElegida=menu(opcionElegida); // Entrara al menu donde podran elegir que acciones realizar.
    } while(opcionElegida != 0);

return 0;
}
