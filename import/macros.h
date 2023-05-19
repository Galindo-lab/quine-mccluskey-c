
/**
 * Longitud de un arreglo
 */
#define ARRAY_LENGHT(A) (sizeof(A) / sizeof(A[0]))


/**********************************************************************
 * Macros para manipular un array de char como un array de booleanos 
 * para no desperdiciar memoria
 * extraido de: https://stackoverflow.com/a/2530319
 *********************************************************************/

/**
 * @brief Obtener el bit en una posicion 
 * 
 */
#define GET_BIT(array, i) (array[i / 8] & (1 << (i % 8)))

/**
 * @brief Cambia el estado del bit a 1
 * 
 */
#define SET_BIT(array, i) (array[i / 8] |= (1 << (i % 8)))

/**
 * @brief Cambia el estado del bit a 0
 * 
 */
#define CLEAR_BIT(array, i) (array[i / 8] &= ~(1 << (i % 8)))