#include "../headers/ARCHIVOS_NRO_ASTRONOMICO.h"

void crearContadorArchivos(){
    FILE* archivoContador = fopen(ARCHIVO_CONTADOR,"w");
    CantidadArchivos cantArchivos={0,0};

    if(archivoContador)
        fwrite(&cantArchivos, sizeof(CantidadArchivos), 1, archivoContador);

    fclose(archivoContador);
}


void leerContadorArchivos(CantidadArchivos* cantArchivos){
    FILE* archivoContador = fopen(ARCHIVO_CONTADOR,"r");

    if(archivoContador)
        fread(cantArchivos, sizeof(CantidadArchivos), 1, archivoContador);
    fclose(archivoContador);
}

void incrementarContadorArchivos(int esTexto){
    FILE* archivoContador = fopen(ARCHIVO_CONTADOR,"r+");
    CantidadArchivos cantArchivos;

    if(archivoContador){
        fseek(archivoContador,0,SEEK_SET);
        fread(&cantArchivos, sizeof(CantidadArchivos), 1, archivoContador);
        if(esTexto)
            cantArchivos.texto++;
        else
            cantArchivos.binarios++;
        fseek(archivoContador,0,SEEK_SET);
        fwrite(&cantArchivos, sizeof(CantidadArchivos), 1, archivoContador);
    }
    fclose(archivoContador);
}

void archivador(NumeroAstronomico unNumeroAstronomico){
    int esTexto;
    FILE* archivo;

    printf("Ingrese donde quiere archivarlo:\n\tBinario = 0\n\tTexto = 1\n\tNo archivar = Ingrese otro numero . . .\n");
    scanf("%d",&esTexto);

    switch(esTexto){
        case ES_BINARIO:
            NumeroAstronomico_Write(unNumeroAstronomico,archivo);
            break;
        case ES_TEXTO:
            NumeroAstronomico_Print(unNumeroAstronomico,archivo);
            break;
    }
}

NumeroAstronomico desarchivador(int esTexto,char* nombreArchivo){
    FILE* archivo;

    if(esTexto){
        archivo = fopen(nombreArchivo,"r");
        if(archivo)
            return NumeroAstronomico_Scan(archivo);
    }
    else{
        archivo = fopen(nombreArchivo,"rb");
        if(archivo)
            return NumeroAstronomico_Read(archivo);
    }

    fclose(archivo);
}

char* CrearNombreArchivo(char* nombreArchivo, int cantArchivos, int esTexto){
    char* cantArchivosC = (char*) malloc(4);// 1 para el centinela y otros 3 para la posible cantidad maxima considerada 999
    char* aux;

    itoa(cantArchivos+1,cantArchivosC,10);
    aux = (char*) malloc(strlen(nombreArchivo)+strlen(cantArchivosC)+1);
    strcpy(aux,cantArchivosC);
    if(esTexto)
        strcat(aux,".txt");
    else
        strcat(aux,".data");
    cantArchivosC = (char*) malloc(strlen(nombreArchivo)+1);
    strcpy(cantArchivosC,nombreArchivo);
    //strcat(nombreArchivo,cantArchivosC);
    nombreArchivo = (char*) malloc(strlen(aux)+strlen(cantArchivosC)+1);
    strcpy(nombreArchivo,cantArchivosC);
    strcat(nombreArchivo,aux);

    free(cantArchivos);
    free(aux);

return nombreArchivo;
}

void NumeroAstronomico_Print(NumeroAstronomico unNumeroAstronomico, FILE* archivoTexto){
    char* nombreArchivo = ARCHIVO_TEXTO;
    CantidadArchivos cantArchivos;

    leerContadorArchivos(&cantArchivos);
    nombreArchivo = CrearNombreArchivo(nombreArchivo, cantArchivos.texto, ES_TEXTO);

    archivoTexto = fopen(nombreArchivo,"w+");

    if(archivoTexto){
        if(SubirNumeroAstronomico(archivoTexto, unNumeroAstronomico)){
            printf("El numero astronomico se archivo correctamente\n");
            incrementarContadorArchivos(ES_TEXTO);
        }
        else
            printf("El numero astronomico no se archivo correctamente ya que contiene error\n");
    }
    else
        printf("No se creo el archivo\n");

    fclose(archivoTexto);
    free(nombreArchivo);
}

NumeroAstronomico NumeroAstronomico_Scan(FILE* archivoTexto) {
return BajarNumeroAstronomico(archivoTexto);
}

NumeroAstronomico BajarNumeroAstronomico(FILE* archivo){
//------------ORDEN------------
	//1 -> longitudError
	//2 -> entero
	//-----------------------------
	int largoEntero;
	char* aux;
	int i=0;
	NumeroAstronomico unNumeroAstronomico = NumeroAstronomico_Inicializar();

    fread(&unNumeroAstronomico.longitudError,sizeof(int),1,archivo);
    if(NumeroAstronomico_EsOverflow(unNumeroAstronomico))
         aux = (char*) malloc(2 * LARGO_MAXIMO_CADENA); // Se da un margen por el overflow del doble
    else
        aux = (char*) malloc(LARGO_MAXIMO_CADENA+1); // +1 por el centinela

    while(fread(aux+i,1,1,archivo))
        i++;
    unNumeroAstronomico.entero = (char*) malloc(strlen(aux)+1);
    strcpy(unNumeroAstronomico.entero,aux);



return unNumeroAstronomico;
}

int SubirNumeroAstronomico(FILE* archivo, NumeroAstronomico unNumeroAstronomico) {
	//------------ORDEN------------
	//1 -> longitudError
	//2 -> entero
	//-----------------------------
    int largoEntero;

    if(NumeroAstronomico_EsError(unNumeroAstronomico) && !NumeroAstronomico_EsOverflow(unNumeroAstronomico))
        return unNumeroAstronomico.longitudError; // Si hay error devolvera el mismo y saldra

    fwrite(&unNumeroAstronomico.longitudError,sizeof(int),1,archivo);
    if(NumeroAstronomico_EsOverflow(unNumeroAstronomico))
        largoEntero = strlen(unNumeroAstronomico.entero)+1; // Por el centinela.
    else
        largoEntero = unNumeroAstronomico.longitudError+3; // Sera la longitud + 3 (2 de flags y 1 del centinela)
    fwrite(unNumeroAstronomico.entero,largoEntero,1,archivo);

return 1;
}

NumeroAstronomico LeerArchivo(int tipoArchivo){
    CantidadArchivos cantArchivos;
    char* nombreArchivo;
    int opcion;

    system("cls");

    leerContadorArchivos(&cantArchivos);
    switch(tipoArchivo){
        case ES_TEXTO:
            nombreArchivo = (char*) malloc(strlen(ARCHIVO_TEXTO)+1);
            strcpy(nombreArchivo,ARCHIVO_TEXTO);

            if(!cantArchivos.texto)
                return NumeroAstronomico_Inicializar();

            printf("Archivos de texto disponibles[1-%d].\n",cantArchivos.texto);
            do{
                printf("Ingrese que numero de archivo deseea abrir: ");
                scanf("%d",&opcion);
                if(opcion > cantArchivos.texto || opcion == 0)
                    printf("La opcion ingresada es incorrecta.\n");
            } while(opcion > cantArchivos.texto || opcion == 0);

            nombreArchivo = CrearNombreArchivo(nombreArchivo, cantArchivos.texto-1, ES_TEXTO);

            return desarchivador(ES_TEXTO, nombreArchivo);
            break;

        case ES_BINARIO:
            nombreArchivo = (char*) malloc(strlen(ARCHIVO_BINARIO)+1);
            strcpy(nombreArchivo,ARCHIVO_BINARIO);

            if(!cantArchivos.binarios)
                return NumeroAstronomico_Inicializar();

            printf("Archivos de binarios disponibles[1-%d].\n",cantArchivos.binarios);
            do{
                printf("Ingrese que numero de archivo deseea abrir: ");
                scanf("%d",&opcion);
                if(opcion > cantArchivos.texto || opcion == 0)
                    printf("La opcion ingresada es incorrecta.\n");
            } while(opcion > cantArchivos.binarios || opcion == 0);

            nombreArchivo = CrearNombreArchivo(nombreArchivo, cantArchivos.binarios-1, ES_BINARIO);

            return desarchivador(ES_BINARIO, nombreArchivo);
            break;

        case 2:
            ;
            FILE* archivo = fopen(ARCHIVO_GRUPOS,"r+");

            if(archivo){
                printf("Ahora mostraremos el numero guardado por grupos.\n");
                char aux;
                while(fread(&aux,1,1,archivo)){
                    printf("%c",aux);
                }
            }
            else
                printf("No hay archivo de numero por grupos.\n");
            break;
    }

    return NumeroAstronomico_Inicializar();

}

void resetArchivos(){
    CantidadArchivos cantArchivos={0,0};

    printf("Si hay archivos creados seran eliminados para no almacenar demasiados\n");

    leerContadorArchivos(&cantArchivos);
    if(cantArchivos.binarios || cantArchivos.texto){
        borrarArchivos(cantArchivos);
        return; // Si entro al if saldra por el return
    }
    // Por lo que no es necesario un else
    printf("No hay archivos\n");

}

void borrarArchivos(CantidadArchivos cantArchivos){
    FILE* archivo;
    if(cantArchivos.texto)
        for(int i=0;i<cantArchivos.texto;i++){
            char* nombreArchivo = ARCHIVO_TEXTO;
            nombreArchivo = CrearNombreArchivo(nombreArchivo, cantArchivos.texto-i-1, ES_TEXTO);

            archivo = fopen( nombreArchivo, "r" );
            printf("Archivo: %s", nombreArchivo );
            if(archivo){
                fclose(archivo);
                if(remove(nombreArchivo) == 0)
                    printf("\nBorrado\n");
                else
                    printf("\nNo pudo ser borrado\n");
            }
            else
                printf(", no encontrado\n");

        }

    if(cantArchivos.binarios)
        for(int i=0;i<cantArchivos.binarios;i++){
            char* nombreArchivo = ARCHIVO_BINARIO;
            nombreArchivo = CrearNombreArchivo(nombreArchivo, cantArchivos.binarios-i-1, ES_BINARIO);

            archivo = fopen( nombreArchivo, "rb" );
            printf("Archivo: %s", nombreArchivo );
            if(archivo){
                fclose(archivo);
                if(remove(nombreArchivo) == 0)
                    printf("\nBorrado\n");
                else
                    printf("\nNo pudo ser borrado\n");
            }
            else
                printf(", no encontrado\n");

        }
        archivo = fopen(ARCHIVO_GRUPOS,"r+");
        printf("Archivo: %s", ARCHIVO_GRUPOS);

        if(archivo){
            fclose(archivo);
            if(remove(ARCHIVO_GRUPOS) == 0)
                printf("\nBorrado\n");
            else
                printf("\nNo pudo ser borrado\n");
        }
        else
            printf(", no encontrado\n");
}

NumeroAstronomico NumeroAstronomico_Read(FILE* archivoBinario){
return BajarNumeroAstronomico(archivoBinario);
}

void NumeroAstronomico_Write(NumeroAstronomico unNumeroAstronomico, FILE* archivoBinario){
    char* nombreArchivo = ARCHIVO_BINARIO;
    CantidadArchivos cantArchivos;

    leerContadorArchivos(&cantArchivos);
    nombreArchivo = CrearNombreArchivo(nombreArchivo, cantArchivos.binarios, ES_BINARIO);

    archivoBinario = fopen(nombreArchivo,"wb");

    if(archivoBinario){
        if(SubirNumeroAstronomico(archivoBinario, unNumeroAstronomico)==1){
            printf("El numero astronomico se archivo correctamente\n");
            incrementarContadorArchivos(ES_BINARIO);
        }
        else
            printf("El numero astronomico no se archivo correctamente ya que contiene error\n");
    }
    else
        printf("No se creo el archivo\n");

    fclose(archivoBinario);
    free(nombreArchivo);
}

