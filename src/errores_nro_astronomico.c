#include "../headers/ERRORES_NRO_ASTRONOMICO.h"

int NumeroAstronomico_EsCadenaNula(NumeroAstronomico unNumeroAstronomico){
    if(unNumeroAstronomico.longitudError == CadenaNula || !unNumeroAstronomico.entero)
        return 1;
return 0;
}

int NumeroAstronomico_EsCadenaInvalida(NumeroAstronomico unNumeroAstronomico){
        if(unNumeroAstronomico.longitudError == CadenaInvalida)
            return 1;
return 0;
}

int NumeroAstronomico_EsOverflow(NumeroAstronomico unNumeroAstronomico){
    if(NumeroAstronomico_EsCadenaNula(unNumeroAstronomico))
        return 0;
    if(unNumeroAstronomico.longitudError == Overflow || unNumeroAstronomico.entero[0] == 1 || strlen(unNumeroAstronomico.entero) > LARGO_MAXIMO_CADENA)
        return 1; // Si el codigo es Overflow o tiene el flag de overflow o su longitud es mayor al maximo

return 0;
}

int NumeroAstronomico_GetTipoDeError(NumeroAstronomico unNumeroAstronomico){
    return unNumeroAstronomico.longitudError;
}

void ImprimirError(int error){
    switch(error){
        case CadenaNula:
            printf("es cadena nula.\n");
            break;
        case CadenaInvalida:
            printf("es cadena invalida.\n");
            break;
        case Overflow:
            printf("posee overflow.\n");
            break;
        case PunteroNulo:
            printf("es puntero nulo.\n");
            break;
    }
}

int NumeroAstronomico_EsError(NumeroAstronomico unNumeroAstronomico){
    if(unNumeroAstronomico.longitudError < 0)
        return 1;
    else
        return 0;
}

void NumeroAstronomico_EstablecerErroresNumAstronomico(NumeroAstronomico* unNumeroAstronomico){
    NumeroAstronomico_DefinirNulo(unNumeroAstronomico);
    if(unNumeroAstronomico->longitudError != CadenaNula){
        NumeroAstronomico_DefinirOverflow(unNumeroAstronomico); // Asignamos el error si tiene overflow
        NumeroAstronomico_DefinirInvalido(unNumeroAstronomico); // Asignamos el error si es invalida la cadena
    } // Primero se asigna el overflow y luego invalido porque si es invalida no importa si tiene overflow
}

void NumeroAstronomico_DefinirNulo(NumeroAstronomico* unNumeroAstronomico){
    if(!unNumeroAstronomico->entero)
        unNumeroAstronomico->longitudError = CadenaNula;
}

void NumeroAstronomico_DefinirOverflow(NumeroAstronomico* unNumeroAstronomico){
    if(strlen(unNumeroAstronomico->entero) > LARGO_MAXIMO_CADENA) {
        unNumeroAstronomico->longitudError = Overflow;
        memset(unNumeroAstronomico->entero,'1',1);
    }
}

void NumeroAstronomico_DefinirInvalido(NumeroAstronomico* unNumeroAstronomico){
    for(int i=0; i<strlen(unNumeroAstronomico->entero); i++){
        if(!EsDigito(unNumeroAstronomico->entero[i])){
            unNumeroAstronomico->longitudError = CadenaInvalida;
            return;
        }
    }
}

int EsDigito(char caracter){
    switch(caracter){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return 1;
        default:
            return 0;
    }
}
