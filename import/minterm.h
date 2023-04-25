/**
 * AUTOR: Luis Eduardo Galindo Amaya                         FECHA: 15-04-2023
 *
 * DESCRIPCIÓN:
 * Bibloteca para trabajar los teminos del metodo de Quine-McCluskey y
 * algunas utilidades para trbajar numeros binarios.
 */
#ifndef minterm
#define minterm

/**
 * Tipo de parametro que se para a las funciones
 * limita la cantidad maxima de variables que puede usar el programa
 */
#define BIT_TYPE unsigned char

/**
 * Numero maximo de variables en el programa.
 * esta limitado por la longitud en bites del BIT_TYPE
 */
#define BIT_MAX_VARS 6

/**
 * States estado 1 no negado, 0 es negado
 * undefined mascara del estado de las variables '1' activo '0' indefinido
 */
typedef struct Minterm
{
    BIT_TYPE states : BIT_MAX_VARS;
    BIT_TYPE undefined : BIT_MAX_VARS;
} Minterm;

/**
 * Obtener el estado de un bit en una posicion
 * @param value
 * @param position
 * @return state
 */
int bitState(BIT_TYPE value, int position)
{
    int mask = (1 << position);
    int valueandmask = value & mask;
    int var = valueandmask ? 1 : 0;

    return var;
}

/**
 * Numero de diferencias entre dos numeros binarios
 * @return diferencias
 */
char bitDiff(BIT_TYPE a, BIT_TYPE b)
{
    int mask = a ^ b; // diferencias '1' valore iguales '0'
    int differences = 0;

    for (char i = BIT_MAX_VARS - 1; i >= 0; i--)
        differences += bitState(mask, i);

    return differences;
}

/**
 * Inicializar un mintermino
 * @param var direccion a un mintermino
 * @param state valor del mintermino
 * @param undefineds valores descartados del mintermino
 */
Minterm MintermInit(Minterm *var, BIT_TYPE state, BIT_TYPE undefineds)
{
    var->states = state;
    var->undefined = undefineds;
    return *var;
}

/**
 * Reserva la memoria para un termino
*/
Minterm* MintermCreate(BIT_TYPE state, BIT_TYPE undefineds)
{
    Minterm *foo = malloc(sizeof(Minterm));

    if (!foo)
        return NULL;
    
    MintermInit(foo, state, undefineds);
    
    return foo;
}

void MintermFree(Minterm *term)
{
    free(term);
}

/**
 * Determinar si dos minterminos son adyacentes
 * @param a
 * @param b
 * @return boolean
 */
char MintermAdjacent(Minterm a, Minterm b)
{
    if (a.undefined != b.undefined)
    {
        // Implicante: numero de variables indefinidas
        return 0;
    }

    // aplicar la mascara y contar las diferencias
    BIT_TYPE implicantMask = a.undefined;
    BIT_TYPE aMask = a.states & implicantMask;
    BIT_TYPE bMask = b.states & implicantMask;

    return bitDiff(aMask, bMask) == 1;
}

char MintermEquals(Minterm a, Minterm b)
{
    if (a.undefined != b.undefined)
    {
        return 0;
    }

    BIT_TYPE implicantMask = a.undefined;
    BIT_TYPE aMask = a.states & implicantMask;
    BIT_TYPE bMask = b.states & implicantMask;

    return bitDiff(aMask, bMask) == 0;
}

/**
 * Combinar dos minterminnos, este metodo no hace las validaciones si esto
 * es posible o no, para realizar las validaciones revisar 'MintermAdjacent'
 * @param a
 * @param b
 * @return Minterm
 */
Minterm MintermMerge(Minterm a, Minterm b)
{
    Minterm foo;
    BIT_TYPE diferences = (a.states ^ b.states) ^ a.undefined;
    MintermInit(&foo, a.states, diferences);
    return foo;
}

#endif