
/**
 * Aqui se guardan todas las funciones para trabajr los bits
 * 15/04/2023
 */

/**
 * Tipo de parametro que se para a las funciones
 * limita la cantidad maxima de variables que puede usar el programa
 */
#define BIT_TYPE short

/**
 * Numero maximo de variables en el programa.
 * esta limitado por la longitud en bites del PARAMETER_TYPE
 */
#define BIT_MAX_VARS 16

/**
 * @param value numero de interes
 * @param position posicion
 * @return estado del bit en la posicion
 */
char bitState(BIT_TYPE value, char position)
{
    return (value & (1 << position)) ? 1 : 0;
}

/**
 * @return numero de diferencias
 */
char bitDiff(BIT_TYPE a, BIT_TYPE b)
{
    int mask = a ^ b; // diferencias '1' valore iguales '0'
    int differences = 0;

    for (char i = BIT_MAX_VARS - 1; i >= 0; i--)
        differences += bitState(mask, i);

    return differences;
}
