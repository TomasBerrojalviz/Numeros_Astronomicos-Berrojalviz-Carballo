#ifndef ARCHIVOS_NRO_ASTRONOMICO
#define ARCHIVOS_NRO_ASTRONOMICO

#include "OPERACIONES_NRO_ASTRONOMICO.h"

#define ARCHIVO_CONTADOR "archivos/archivo_contador.cont"
#define ARCHIVO_TEXTO "archivos/texto/numero_astronomico"
#define ARCHIVO_BINARIO "archivos/binarios/numero_astronomico"
#define ARCHIVO_GRUPOS "archivos/numero_astronomico-Grupos.txt"

#define ES_TEXTO 1
#define ES_BINARIO 0

typedef struct {
    int binarios;
    int texto;
} CantidadArchivos; // Creamos una estructura para poder tener un contador fiable de los archivos que vamos creando.

// En el enunciado devuelve el flujo pero no tiene sentido ya que lo pasamos como FILE* y si llega a haber cambios
// se vera afectado directamente
// Tambien notamos que piden dividir las operaciones de texto y binario pero no tiene mucho sentido, ya que al pasarle el flujo
// lo que deben hacer es exactamente igual ya sea de texto o binario. Intentamos hacerlos diferentes para no duplicar codigo
// de forma innecesaria para seguir con el enunciado.


// ------------ FUNCIONES REQUERIDAS ---------------
//------------------ POR ENUNCIADO  ---------------------
NumeroAstronomico NumeroAstronomico_Read(FILE* archivoBinario);
void NumeroAstronomico_Write(NumeroAstronomico unNumeroAstronomico, FILE* archivoTexto);
NumeroAstronomico NumeroAstronomico_Scan(FILE* archivoTexto);
void NumeroAstronomico_Print(NumeroAstronomico unNumeroAstronomico, FILE* archivoTexto);
// ---------------------------------------------------
//---------------------------------------------------------

// --------------------EXTRAS--------------------------
//----------------------------------------------------------

void contadorArchivos();
void leerContadorArchivos(CantidadArchivos* cantArchivos);
void incrementarContadorArchivos(int esTexto);
void archivador(NumeroAstronomico unNumeroAstronomico);
NumeroAstronomico desarchivador(int esTexto,char* nombreArchivo);
char* CrearNombreArchivo(char* nombreArchivo, int cantArchivos, int esTexto);
int SubirNumeroAstronomico(FILE* archivo, NumeroAstronomico unNumeroAstronomico);
NumeroAstronomico BajarNumeroAstronomico(FILE* archivo);
NumeroAstronomico LeerArchivo(int tipoArchivo);
void resetArchivos(); // Se encarga de enviar la orden de borrar los archivos
void borrarArchivos(CantidadArchivos cantArchivos); // Se encargara de borrar todos los archivos creados en la ejecucion anterior



#endif // ARCHIVOS_NRO_ASTRONOMICO
