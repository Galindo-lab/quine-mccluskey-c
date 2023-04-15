
#include <stdlib.h>
#include <stdio.h>

/**
 * Tipo de parametro que se para a las funciones
 * limita la cantidad maxima de variables que puede usar el programa
 */
#define PARAMETER_TYPE char

/**
 * Numero maximo de variables en el programa.
 * esta limitado por la longitud en bites del PARAMETER_TYPE
 */
#define MAX_VARS 8

/**
 * @param value numero de interes 
 * @param position posicion 
 * @return estado del bit en la posicion
*/
char BitState(PARAMETER_TYPE value, char position)
{
    return (value & (1 << position)) ? 1 : 0;
}

/**
 * @return numero de diferencias 
*/
char BitDiff(PARAMETER_TYPE a, PARAMETER_TYPE b)
{
    int mask = a ^ b; // diferencias '1' valore iguales '0'
    int differences = 0;

    for (char i = MAX_VARS - 1; i >= 0; i--)
        differences += BitState(mask, i);

    return differences;
}

/**
 * Coloca la representacion de value en stdout}
 * @param value 
*/
void BitPrint(PARAMETER_TYPE value)
{
    for (char i = MAX_VARS - 1; i >= 0; i--)
        printf(BitState(value, i) ? "1" : "_");
}

int main()
{
    char a = 0b00001010;
    char b = 0b00000011;

    BitPrint(a);
    puts("");
    BitPrint(b);
    puts("");

    printf("diferencias: %d\n", BitDiff(a, b));

    return EXIT_SUCCESS;
}
