#ifndef OPERACIONES_NRO_ASTRONOMICO
#define OPERACIONES_NRO_ASTRONOMICO

#include "NUMEROS_ASTRONOMICOS.h"
#include "CREAR_NRO_ASTRONOMICO.h"
#include "ERRORES_NRO_ASTRONOMICO.h"

NumeroAstronomico NumeroAstronomico_Sumar(NumeroAstronomico numero1, NumeroAstronomico numero2);
int NumeroAstronomico_SonIguales(NumeroAstronomico numero1, NumeroAstronomico numero2);
int NumeroAstronomico_EsMenor(NumeroAstronomico numero1, NumeroAstronomico numero2);
NumeroAstronomico RealizarSumaEntero(char* entero1, char* entero2, NumeroAstronomico resultadoAstronomico);
int ValorCaracter(char caracter);
char EnteroACaracter(int numero);
int NroMax(int num1, int num2);
char SumarDigitos(int numEntero1, int numEntero2, int* carry);
char* InvertirCadena(char* cadena);
void NumeroAstronomico_Mostrar(NumeroAstronomico unNumeroAstronomico, int gruposEnPrimeraLinea, FILE* Flujo);
int* darGrupos(char* entero, int cantGruposEnEntero, int resto);
int darGrupo(char* entero, int digitos);

#endif // OPERACIONES_NRO_ASTRONOMICO
