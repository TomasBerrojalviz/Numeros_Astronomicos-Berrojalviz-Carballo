#ifndef CREAR_NRO_ASTRONOMICO
#define CREAR_NRO_ASTRONOMICO

#include "NUMEROS_ASTRONOMICOS.h"
#include "CREAR_NRO_ASTRONOMICO.h"
#include "ERRORES_NRO_ASTRONOMICO.h"
#include "ARCHIVOS_NRO_ASTRONOMICO.h"

NumeroAstronomico NumeroAstronomico_Inicializar();
NumeroAstronomico NumeroAstronomico_CrearDesdeCadena(char* cadena);
NumeroAstronomico NumeroAstronomico_CrearDesdeCifraSeguidaDeCeros(char* cifra, int cantidadDeCeros);
NumeroAstronomico NumeroAstronomico_CrearAleatorio();
void darCeros(int cantidadDeCeros, char* ceros);
NumeroAstronomico NumeroAstronomico_CrearNumeroAstronomico();
NumeroAstronomico NumeroAstronomico_ObtenerDesdeArchivo();

#endif // CREAR_NRO_ASTRONOMICO
