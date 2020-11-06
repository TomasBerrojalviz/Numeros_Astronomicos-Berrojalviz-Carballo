#ifndef ERRORES_NRO_ASTRONOMICO
#define ERRORES_NRO_ASTRONOMICO

#include "OPERACIONES_NRO_ASTRONOMICO.h"
#include "NUMEROS_ASTRONOMICOS.h"

int NumeroAstronomico_EsCadenaNula(NumeroAstronomico unNumeroAstronomico);
int NumeroAstronomico_EsCadenaInvalida(NumeroAstronomico unNumeroAstronomico);
int NumeroAstronomico_EsOverflow(NumeroAstronomico unNumeroAstronomico);
int NumeroAstronomico_EsError(NumeroAstronomico unNumeroAstronomico);
void establecerErroresNumAstronomico(NumeroAstronomico* unNumeroAstronomico);
void NumeroAstronomico_DefinirNulo(NumeroAstronomico* unNumeroAstronomico);
void NumeroAstronomico_DefinirOverflow(NumeroAstronomico* unNumeroAstronomico);
void NumeroAstronomico_DefinirInvalido(NumeroAstronomico* unNumeroAstronomico);
int EsDigito(char caracter);

#endif // ERRORES_NRO_ASTRONOMICO
