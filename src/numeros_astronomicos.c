#include "../headers/NUMEROS_ASTRONOMICOS.h"
#include "../headers/CREAR_NRO_ASTRONOMICO.h"
#include "../headers/OPERACIONES_NRO_ASTRONOMICO.h"
#include "../headers/ARCHIVOS_NRO_ASTRONOMICO.h"

int menu(int opcionElegida) {
    NumeroAstronomico unNumeroAstronomico = NumeroAstronomico_Inicializar(); // Crearemos un numero astronomico

    system("cls");

    printf("**********************************************************************");
    printf("************************-------MENU-------****************************");
    printf("*                    1 - Crear desde cadena                          *");
    printf("*             2 - Crear desde cifra seguida de ceros                 *");
    printf("*                      3 - Crear aleatorio                           *");
    printf("*                      4 - Realizar suma                             *");
    printf("*                       5 - Son iguales                              *");
    printf("*                         6 - Es menor                               *");
    printf("*                      7 - Leer archivos                             *");
    printf("*                           0 - Salir                                *");
    printf("**********************************************************************");

    printf("Ingrese la opcion: ");
    scanf("%d",&opcionElegida);

    system("cls");

    switch (opcionElegida){
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
            unNumeroAstronomico = NumeroAstronomico_OpcionSumar();
            printf("Suma realizada. Se procede a mostrar el resultado\n");
            NumeroAstronomico_OpcionMostrar(unNumeroAstronomico);
            archivador(unNumeroAstronomico);
            break;
        case 5:
            NumeroAstronomico_OpcionSonIguales();
            break;
        case 6:
            NumeroAstronomico_OpcionEsMenor();
            break;
        case 7:
            OpcionLeerArchivos();
            break;
        case 0:
            return opcionElegida; // En el caso que se ponga la opcion salir directamente salir.
        default:
            printf("Opcion invalida.\n"); // En el caso de que por alguna razon se ingrese una opcion incorrecta se avisara.
            system("pause");
            return opcionElegida;
    }

    NumeroAstronomico_ResetNumeroAstronomico(&unNumeroAstronomico); // Una vez salidos del menu se reseteara el numero astronomico.

    system("pause");

return opcionElegida;
}

void NumeroAstronomico_OpcionMostrar(NumeroAstronomico unNumeroAstronomico){
    int opcion;

    printf("Como desea mostrar el numero astronomico?\n\t0.Completo\n\t1.Por grupos\n");
    scanf("%d",&opcion);

    if(opcion == 0)
        NumeroAstronomico_MostrarCompleto(unNumeroAstronomico);
    else if(opcion == 1)
        NumeroAstronomico_OpcionMostrarPorGrupos(unNumeroAstronomico);
    else{
        printf("La opcion %d es invalida por favor ingrese una correcta.\n", opcion);
        NumeroAstronomico_OpcionMostrar(unNumeroAstronomico);
    }
}


void NumeroAstronomico_MostrarCompleto(NumeroAstronomico unNumeroAstronomico){
    if(NumeroAstronomico_EsError(unNumeroAstronomico)){
        printf("El numero astronomico ");
        ImprimirError(unNumeroAstronomico.longitudError);
    }
    else{
        printf("El numero astronomico es %s\n", unNumeroAstronomico.entero+2);
        printf("Su longitud es de %d digitos.\n", unNumeroAstronomico.longitudError);
    }
    if(NumeroAstronomico_EsError(unNumeroAstronomico) && !NumeroAstronomico_EsCadenaNula(unNumeroAstronomico)){
        printf("El numero astronomico es %s\n", unNumeroAstronomico.entero+2);
        printf("Su codigo de error es %d.\n", unNumeroAstronomico.longitudError);
    }

}

void NumeroAstronomico_ResetNumeroAstronomico(NumeroAstronomico* unNumeroAstronomico){
    free(unNumeroAstronomico->entero);
    NumeroAstronomico_Inicializar(&unNumeroAstronomico);
}

NumeroAstronomico NumeroAstronomico_OpcionCrearDesdeCadena(){
    char* cadena = (char*) malloc(LARGO_MAXIMO_NRO_ASTRO+1);;

    do{
        printf("Introduzca la cadena: ");

        scanf("%s",cadena);

        if(cadena[0] == '0')
            printf("Los numeros decimales no pueden comenzar con 0.\nPor favor ingrese un numero valido.\n");
    }while(cadena[0] == '0');

return NumeroAstronomico_CrearDesdeCadena(cadena);
}

NumeroAstronomico NumeroAstronomico_OpcionCrearDesdeCifraSeguidaDeCeros(){
    char* cifra;
    int cantidadDeCeros;

    printf("Introduzca la cifra: ");
    cifra =  (char*) malloc(sizeof(char)*(LARGO_MAXIMO_NRO_ASTRO+1));
    scanf("%s",cifra);

    cantidadDeCeros = EleccionDeCeros(cifra); // Nos dara la cantidad de ceros que no supere en total con la cifra los 100 digitos

return NumeroAstronomico_CrearDesdeCifraSeguidaDeCeros(cifra,cantidadDeCeros);
}

int EleccionDeCeros(char* cifra){
    int cantidadDeCeros;

    do{
        printf("Introduzca la cantidad de ceros: ");
        scanf("%d",&cantidadDeCeros);
        if(cantidadDeCeros+strlen(cifra) > LARGO_MAXIMO_NRO_ASTRO) // Si en total la longitud sera de mas de 100 digitos
            printf("Debera indicar una cantidad de ceros menor o igual a %d.\n",LARGO_MAXIMO_NRO_ASTRO - strlen(cifra));
    }while(cantidadDeCeros+strlen(cifra) > LARGO_MAXIMO_NRO_ASTRO); // Hacer mientras la cantidad ingresada genere overflow

return cantidadDeCeros;
}


NumeroAstronomico NumeroAstronomico_OpcionCrearAleatorio(){

    printf("Se generara un numero astronomico de forma aleatoria.\n");

return NumeroAstronomico_CrearAleatorio();
}

NumeroAstronomico NumeroAstronomico_OpcionSumar(){
    NumeroAstronomico numero1 = NumeroAstronomico_CrearNumeroAstronomico();
    NumeroAstronomico numero2 = NumeroAstronomico_CrearNumeroAstronomico();

    system("cls");

    printf("Sumaremos %s con %s\n",numero1.entero+2,numero2.entero+2);

return NumeroAstronomico_Sumar(numero1,numero2);
}

void NumeroAstronomico_OpcionSonIguales(){
    NumeroAstronomico numero1 = NumeroAstronomico_CrearNumeroAstronomico();
    NumeroAstronomico numero2 = NumeroAstronomico_CrearNumeroAstronomico();

    system("cls");

    printf("Los numeros %s y %s ",numero1.entero+2,numero2.entero+2);

    if(NumeroAstronomico_SonIguales(numero1,numero2))
        printf("son iguales.\n");
    else
        printf("no son iguales.\n");
}

void NumeroAstronomico_OpcionEsMenor(){
    NumeroAstronomico numero1 = NumeroAstronomico_CrearNumeroAstronomico();
    NumeroAstronomico numero2 = NumeroAstronomico_CrearNumeroAstronomico();

    system("cls");
    printf("El numero %s ",numero1.entero+2);

    if(NumeroAstronomico_EsMenor(numero1,numero2))
        printf("es menor a %s.\n",numero2.entero+2);
    else
        printf("no es menor a %s.\n",numero2.entero+2);
}

void OpcionLeerArchivos(){
    int tipoArchivo;
    NumeroAstronomico unNumeroAstronomico;

    system("cls");

    printf("**********************************************************************");
    printf("************************-------MENU-------****************************");
    printf("*                     0 - Archivos binarios                          *");
    printf("*                     1 - Archivos de texto                          *");
    printf("*                2 - Archivo de numero por grupos                    *");
    printf("*                           9 - Salir                                *");
    printf("**********************************************************************");

    printf("Ingrese la opcion: ");
    scanf("%d",&tipoArchivo);

    if(tipoArchivo == 9)
        return;

    unNumeroAstronomico = LeerArchivo(tipoArchivo);

    if(tipoArchivo == 2)
        return;

    if(unNumeroAstronomico.entero)
        NumeroAstronomico_OpcionMostrar(unNumeroAstronomico);
    else
        printf("No hay archivos.\n");
    NumeroAstronomico_ResetNumeroAstronomico(&unNumeroAstronomico);
}


void NumeroAstronomico_OpcionMostrarPorGrupos(NumeroAstronomico unNumeroAstronomico){
    int gruposEnPrimeraLinea, tipoFlujo;
    void* flujo;
    do{
        printf("Quiere pasarlo por un archivo o por consola?\n(El archivo solo guarda un numero, el anterior se borrara)\n\t0.Archivo\n\t1.Consola\n");
        scanf("%d",&tipoFlujo);
        if(tipoFlujo!=0 && tipoFlujo!=1)
            printf("La opcion %d es invalida por favor ingrese una correcta.\n", tipoFlujo);
    }while(tipoFlujo!=0 && tipoFlujo!=1);

    if(tipoFlujo == 0){
        flujo = fopen(ARCHIVO_GRUPOS,"w+");
        printf("Ahora archivaremos el numero por grupo en:\n\t\"%s\"\n",ARCHIVO_GRUPOS);
    }
    else{
        flujo = stdout;
        printf("Ahora mostraremos el numero por grupos.\n");
    }


    printf("Introduzca la cantidad de grupos para la primera linea: ");

    scanf("%d",&gruposEnPrimeraLinea);

    if(NumeroAstronomico_EsError(unNumeroAstronomico)){
        printf("El numero astronomico ");
        ImprimirError(unNumeroAstronomico.longitudError);
    }
    else{
        NumeroAstronomico_Mostrar(unNumeroAstronomico, gruposEnPrimeraLinea, flujo);
        if(tipoFlujo == 0)
            printf("El numero astronomico %s se archivo correctamente por grupos.\n", unNumeroAstronomico.entero+2);
        printf("Su longitud es de %d digitos.\n", unNumeroAstronomico.longitudError);
    }
    if(NumeroAstronomico_EsError(unNumeroAstronomico) && !NumeroAstronomico_EsCadenaNula(unNumeroAstronomico)){
        NumeroAstronomico_Mostrar(unNumeroAstronomico, gruposEnPrimeraLinea, flujo);
        if(tipoFlujo == 0)
            printf("El numero astronomico %s se archivo correctamente por grupos.\n", unNumeroAstronomico.entero+2);
        printf("Su codigo de error es %d.\n", unNumeroAstronomico.longitudError);
    }

    if(tipoFlujo == 0)
        fclose(flujo);
}
