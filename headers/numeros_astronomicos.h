#ifndef NUMEROS_ASTRONOMICOS
#define NUMEROS_ASTRONOMICOS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <time.h>

#define LARGO_MAXIMO_NRO_ASTRO 100
#define LARGO_MAXIMO_CADENA 102

typedef struct {
    const char* entero;
    int longitudError;
} NumeroAstronomico;

typedef enum {
    Ninguno=0, // ABSURDO explicacion en guia
    CadenaNula=-1,
    CadenaInvalida=-2,
    Overflow=-3,
    PunteroNulo=-4,
} TipoDeError;

int menu(int opcionElegida);
void NumeroAstronomico_OpcionMostrar(NumeroAstronomico unNumeroAstronomico);
void NumeroAstronomico_MostrarCompleto(NumeroAstronomico unNumeroAstronomico);
void NumeroAstronomico_ResetNumeroAstronomico(NumeroAstronomico* unNumeroAstronomico);
NumeroAstronomico NumeroAstronomico_OpcionCrearDesdeCadena();
NumeroAstronomico NumeroAstronomico_OpcionCrearDesdeCifraSeguidaDeCeros();
NumeroAstronomico NumeroAstronomico_OpcionCrearAleatorio();
NumeroAstronomico NumeroAstronomico_OpcionSumar();
void NumeroAstronomico_OpcionSonIguales();
void NumeroAstronomico_OpcionEsMenor();
void OpcionLeerArchivos();
void NumeroAstronomico_OpcionMostrarPorGrupos(NumeroAstronomico unNumeroAstronomico);

#endif // NUMEROS_ASTRONOMICOS
