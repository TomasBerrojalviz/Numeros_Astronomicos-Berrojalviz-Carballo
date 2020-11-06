//#include "..\headers\NUMEROS_ASTRONOMICOS.h"
#include "..\headers\CREAR_NRO_ASTRONOMICO.h"
//#include "..\headers\ERRORES_NRO_ASTRONOMICO.h"
//#include "..\headers\OPERACIONES_NRO_ASTRONOMICO.h"

NumeroAstronomico NumeroAstronomico_Inicializar(){
    NumeroAstronomico unNumeroAstronomico;

    unNumeroAstronomico.entero = NULL;
    unNumeroAstronomico.longitudError = CadenaNula;

return unNumeroAstronomico;
}

NumeroAstronomico NumeroAstronomico_CrearDesdeCadena(char* cadena){
    NumeroAstronomico unNumeroAstronomico;

    unNumeroAstronomico.longitudError = strlen(cadena);
    unNumeroAstronomico.entero = malloc(strlen(cadena)+3);
    strcpy(unNumeroAstronomico.entero,"00");
    strcat(unNumeroAstronomico.entero,cadena);

    NumeroAstronomico_EstablecerErroresNumAstronomico(&unNumeroAstronomico);

    archivador(unNumeroAstronomico);

    free(cadena);

return unNumeroAstronomico;
}

NumeroAstronomico NumeroAstronomico_CrearDesdeCifraSeguidaDeCeros(char* cifra, int cantidadDeCeros){
    NumeroAstronomico unNumeroAstronomico;

    darCeros(cantidadDeCeros, cifra);

    unNumeroAstronomico.longitudError = strlen(cifra);
    unNumeroAstronomico.entero = (char*) malloc(strlen(cifra)+3);
    strcpy(unNumeroAstronomico.entero,"00");
    strcat(unNumeroAstronomico.entero,cifra);

    NumeroAstronomico_EstablecerErroresNumAstronomico(&unNumeroAstronomico);

    archivador(unNumeroAstronomico);

    free(cifra);

return unNumeroAstronomico;
}
NumeroAstronomico NumeroAstronomico_CrearAleatorio(){
    int numeroRandom;
    NumeroAstronomico unNumeroAstronomico;
    char* aux;

    unNumeroAstronomico.entero = (char*) malloc(103); // 100 para los digitos + 2 de los flags + 1 del centinela

    strcpy(unNumeroAstronomico.entero,"00");

    for(int i = 0; i < 100; i++){
        if(rand()%2){ // el selector dara de forma "random" 1 o 0 entonces de forma random entrara al if (dara un digito)
            if(i == 0) // solo al comienzo
                numeroRandom = rand()%9+1; // se generara un nro del 1 al 9 osea un digito
            else
                numeroRandom = rand()%10; // se generara un nro del 0 al 9 osea un digito
            aux = (char*) malloc(1);
            aux=itoa(numeroRandom,aux,10);
            strcat(unNumeroAstronomico.entero,aux);
            free(aux);
        }

    }
    unNumeroAstronomico.longitudError = strlen(unNumeroAstronomico.entero)-2; // la longitud - 2 por los flags

    NumeroAstronomico_EstablecerErroresNumAstronomico(&unNumeroAstronomico);

    archivador(unNumeroAstronomico);

return unNumeroAstronomico;
}


void darCeros(int cantidadDeCeros, char* cifra){
    for(int i=0;i<cantidadDeCeros;i++){
        strcat(cifra,"0");
    }
}

NumeroAstronomico NumeroAstronomico_CrearNumeroAstronomico(){
    int opcion;
    NumeroAstronomico unNumeroAstronomico = NumeroAstronomico_Inicializar();

    printf("**********************************************************************");
    printf("************************-------MENU-------****************************");
    printf("*                    1 - Crear desde cadena                          *");
    printf("*             2 - Crear desde cifra seguida de ceros                 *");
    printf("*                      3 - Crear aleatorio                           *");
    printf("*                     4 - Obtener de archivo                         *");
    printf("**********************************************************************");

    printf("Ingrese la opcion: ");
    scanf("%d",&opcion);

    switch (opcion) {
        case 1:
            unNumeroAstronomico = NumeroAstronomico_OpcionCrearDesdeCadena();
            NumeroAstronomico_OpcionMostrar(unNumeroAstronomico);
            break;
        case 2:
            unNumeroAstronomico = NumeroAstronomico_OpcionCrearDesdeCifraSeguidaDeCeros();
            NumeroAstronomico_OpcionMostrar(unNumeroAstronomico);
            break;
        case 3:
            unNumeroAstronomico = NumeroAstronomico_OpcionCrearAleatorio();
            NumeroAstronomico_OpcionMostrar(unNumeroAstronomico);
            break;
        case 4:
            unNumeroAstronomico = NumeroAstronomico_ObtenerDesdeArchivo(); // El leer ya muestra el numero elegido.
            break;
    }

    while(NumeroAstronomico_EsCadenaNula(unNumeroAstronomico)){
        printf("No se ha creado el numero astronomico, por favor cree un numero\nastronomico correctamente.\n");
        unNumeroAstronomico = NumeroAstronomico_CrearNumeroAstronomico();
    }
    system("pause");

return unNumeroAstronomico;
}

NumeroAstronomico NumeroAstronomico_ObtenerDesdeArchivo(){
    int tipoArchivo;
    char* tipoArch = malloc(10);
    NumeroAstronomico unNumeroAstronomico;

    system("cls");

    printf("**********************************************************************");
    printf("************************-------MENU-------****************************");
    printf("*                     0 - Archivos binarios                          *");
    printf("*                     1 - Archivos de texto                          *");
    printf("**********************************************************************");

    do{
        printf("Ingrese la opcion deseada: ");
        scanf("%d",&tipoArchivo);
        if(tipoArchivo != 0 && tipoArchivo != 1)
            printf("La opcion ingresada es incorrecta.\n");
    }while(tipoArchivo != 0 && tipoArchivo != 1);

    if(tipoArchivo == ES_TEXTO)
        strcpy(tipoArch,"texto");
    else
        strcpy(tipoArch,"binario");

    unNumeroAstronomico = LeerArchivo(tipoArchivo);

    if(unNumeroAstronomico.entero)
        NumeroAstronomico_OpcionMostrar(unNumeroAstronomico);
    else
        printf("No hay archivos de tipo %s.\n", tipoArch);


return unNumeroAstronomico;
}
