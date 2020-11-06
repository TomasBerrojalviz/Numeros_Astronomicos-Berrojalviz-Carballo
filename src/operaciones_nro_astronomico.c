#include "../headers/OPERACIONES_NRO_ASTRONOMICO.h"

int NumeroAstronomico_SonIguales(NumeroAstronomico numero1, NumeroAstronomico numero2){
    return !strcmp(numero1.entero+2,numero2.entero+2);
}

int NumeroAstronomico_EsMenor(NumeroAstronomico numero1, NumeroAstronomico numero2){
    if(strcmp(numero1.entero+2,numero2.entero+2)<0)
        return 1;
return 0;
}

NumeroAstronomico NumeroAstronomico_Sumar(NumeroAstronomico numero1, NumeroAstronomico numero2){
    NumeroAstronomico resultadoAstronomico = NumeroAstronomico_Inicializar();

    resultadoAstronomico = RealizarSumaEntero(numero1.entero+2, numero2.entero+2, resultadoAstronomico); // Se les suma 2 para no tener los flags

    NumeroAstronomico_ResetNumeroAstronomico(&numero1);
    NumeroAstronomico_ResetNumeroAstronomico(&numero2);

return resultadoAstronomico;
}

NumeroAstronomico RealizarSumaEntero(char* entero1, char* entero2, NumeroAstronomico resultadoAstronomico){
    int i1=0, i2=0;
    int largo1=strlen(entero1), largo2=strlen(entero2);
    int numEntero1, numEntero2;
    int carry=0;
    char* aux[1];

    entero1 = InvertirCadena(entero1);
    entero2 = InvertirCadena(entero2);

    resultadoAstronomico.entero = (char*) malloc(NroMax(largo1,largo2)+4); // Se le suma 4 porque son 2 de flags, puede haber 1 digito mas por el carry y otro por el centinela

    while(i1 < largo1 && i2 < largo2){
        numEntero1 = ValorCaracter(entero1[i1]);
        numEntero2 = ValorCaracter(entero2[i2]);
        if(carry)
            numEntero1++;
        *aux = SumarDigitos(numEntero1, numEntero2, &carry);
        if(i1==0) // Solo la primera vez
            strcpy(resultadoAstronomico.entero,aux); // Se copiara
        else
            strcat(resultadoAstronomico.entero,aux); // El resto se ira concatenando
        i1++;
        i2++;
    }
    int carryAux = carry;
    while(carryAux){
        if(i1<largo1){
            entero1[i1] = SumarDigitos(ValorCaracter(entero1[i1]),1,&carryAux);
            *aux=entero1[i1];
            strcat(resultadoAstronomico.entero,aux);
            i1++;
        }
        else if(i2<largo2){
            entero2[i2] = SumarDigitos(ValorCaracter(entero2[i2]),1,&carryAux);
            *aux=entero2[i2];
            strcat(resultadoAstronomico.entero,aux);
            i2++;
        }
        else{
            aux[0]='1';
            strcat(resultadoAstronomico.entero,aux);
            carryAux = 0;
        }

    }
    if(i1<largo1)
        strcat(resultadoAstronomico.entero,entero1+i1);
    if(i2<largo2)
        strcat(resultadoAstronomico.entero,entero2+i2);

    // Agregar flags de overflow y de carry
    if(strlen(resultadoAstronomico.entero) > LARGO_MAXIMO_NRO_ASTRO) // Si es overflow
        strcpy(entero1,"1");
    else
        strcpy(entero1,"0");
    if(carry) // Si tuvo carry
        strcat(entero1,"1");
    else
        strcat(entero1,"0");

    resultadoAstronomico.entero = InvertirCadena(resultadoAstronomico.entero);

    resultadoAstronomico.longitudError = strlen(resultadoAstronomico.entero); // Es el largo sin los flags

    strcat(entero1,resultadoAstronomico.entero);
    strcpy(resultadoAstronomico.entero,entero1);

    NumeroAstronomico_EstablecerErroresNumAstronomico(&resultadoAstronomico);

return resultadoAstronomico;
}

int ValorCaracter(char caracter){
    return caracter - '0';
}

char EnteroACaracter(int numero){
    return numero + '0';
}

int NroMax(int num1, int num2){
   if (num1 > num2)
      return num1;
   else
      return num2;
}

char SumarDigitos(int numEntero1, int numEntero2, int* carry){
    int suma=numEntero1+numEntero2;

    if(suma>9){
        suma = suma - 10;
        *carry=1;
    }
    else
        *carry = 0;

return EnteroACaracter(suma);;
}

char* InvertirCadena(char* cadena){
  int longitud = strlen(cadena);
  char temporal;
  int izquierda = 0, derecha = longitud - 1;

  while(izquierda < (longitud / 2)) {
    temporal = cadena[izquierda];
    cadena[izquierda] = cadena[derecha];
    cadena[derecha] = temporal;

    izquierda++;
    derecha--;
  }

return cadena;
}

void NumeroAstronomico_Mostrar(NumeroAstronomico unNumeroAstronomico, int gruposEnPrimeraLinea, FILE* flujo){
    int cantGruposEnEntero;
    if(!NumeroAstronomico_EsError(unNumeroAstronomico)){ // Si no hay error
        cantGruposEnEntero = (unNumeroAstronomico.longitudError/3);
        if(unNumeroAstronomico.longitudError % 3) // si la longitud del numero posee resto al dividirla por 3
            cantGruposEnEntero++; // habra un grupo mas por la definicion de division con enteros
        // Ejemplo: 19/3 = 6. Pero habra 7 en realidad, hasta 18 serian 6, con que haya 19 serian esos 6 con 1 grupo de solo 1 digito.
    }
    else{ // Puede que tenga overflow pero igual queramos mostrarlo
        cantGruposEnEntero = (strlen(unNumeroAstronomico.entero+2)/3); // Como posee error el campo longitudError poseera el error
        if(strlen(unNumeroAstronomico.entero+2) % 3) // Por lo tanto se tomara su longitud sacando los 2 flags
            cantGruposEnEntero++;
    }
    int cantGruposEnEnteroRestantes = cantGruposEnEntero;

    int* grupos;
    char* aux = (char*) malloc(4);

    grupos = darGrupos(unNumeroAstronomico.entero+2, cantGruposEnEntero, unNumeroAstronomico.longitudError % 3); // nos dara todos los grupos
    int i2=0;
    for(int i=0;i<cantGruposEnEntero;i=cantGruposEnEntero-cantGruposEnEnteroRestantes){ // Este for servira para recorrer los renglones
        int entroAl2doFor = 0;
        fprintf(flujo,"\t\t");
        for(int j=0; j<gruposEnPrimeraLinea-i2  && cantGruposEnEnteroRestantes;j++){ // Este for servira para recorrer los grupos
            if(i || j){ // En los casos que sean 0 no entraran ya que en el que i=0 y j=0 sera el comienzo y en ese caso puede que este bien que no haya 3 digitos en el grupo
                switch(strlen(itoa(grupos[j+i],aux,10))){ // esto sera la cantidad de digitos del numero
                    case 1:
                        // si es 1 es porque el grupo solo tendra 1 digito lo cual significa que faltan dos 0.
                        // ejemplo: 000 dejara solo 0 y tendremos que agregarle los dos 0.

                        fprintf(flujo,"00");
                        break;
                    case 2:
                        // si es 2 es porque el grupo seran 2 numeros lo cual significa que falta un 0.
                        // ejemplo: 050 dejara solo el 50 y tendremos que agregarle el 0.

                        fprintf(flujo,"0");
                        break;
                }
            }
            fprintf(flujo,itoa(grupos[j+i],aux,10));
            fprintf(flujo,".");
            cantGruposEnEnteroRestantes--; // al haber mostrado un grupo ya habra uno menos restante que mostrar
            entroAl2doFor = 1; // Nos avisara si entro a este for, lo cual necesitaremos mas adelante
        }
        if(cantGruposEnEnteroRestantes && !entroAl2doFor){  // si todavia hay grupos restantes por mostrar y no entro al for
            if(i){
                switch(strlen(itoa(grupos[cantGruposEnEntero-cantGruposEnEnteroRestantes],aux,10))){
                    case 1:
                        fprintf(flujo,"00");
                        break;
                    case 2:
                        fprintf(flujo,"0");
                        break;
                }
            }
            fprintf(flujo,itoa(grupos[cantGruposEnEntero-cantGruposEnEnteroRestantes],aux,10));
            fprintf(flujo,".");
            cantGruposEnEnteroRestantes--;
        }
        fprintf(flujo,"\n");
        if(i==gruposEnPrimeraLinea || i==3*gruposEnPrimeraLinea-2 || i==4*gruposEnPrimeraLinea-4 || i==4*gruposEnPrimeraLinea-1) // Esto sera para cuando haya demasiados y no haya muchos grupos de 1 por renglon al final
            ; // no hacer nada
        else
            i2++;
    }

    free(grupos);
    free(flujo);
}

int* darGrupos(char* entero, int cantGruposEnEntero, int resto){
    int* grupos;
    int cantAvanzada=0;

    grupos = (char*) malloc(sizeof(int) * cantGruposEnEntero);

    for(int i = 0; i < cantGruposEnEntero; i++){
        if(i==0 && resto != 0){
            grupos[i]= darGrupo(entero+cantAvanzada,resto);
            cantAvanzada+=resto;
        }
        else{
            grupos[i] = darGrupo(entero+cantAvanzada,3);
            cantAvanzada+=3;
        }
    }

return grupos;
}

int darGrupo(char* entero, int digitos){
    int grupo = 0;
    for(int i = 0; i<digitos && entero[i]; i++)
        grupo = 10 * grupo + ValorCaracter(entero[i]);

return grupo;
}
