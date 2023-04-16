
#include <stdlib.h>
#include <stdio.h>

#include "import/bit.h"
#include "import/utils.h"
#include "import/macros.h"

// #include "tests.h" // elimnar para el relase

/**
 * states estado 1 no negado, 0 es negado
 * undefined mascara del estado de las variables '1' activo '0' indefinido
 */
typedef struct Minterm
{
    BIT_TYPE states;
    BIT_TYPE undefined;
} Minterm;

void MintermInit(Minterm *var, BIT_TYPE state, BIT_TYPE undefineds)
{
    var->states = state;
    var->undefined = undefineds;
}

void MintermDisplay(char vars, Minterm *min)
{
    for (char i = vars - 1; i >= 0; i--)
    {
        if (bitState(min->undefined, i))
            printf(bitState(min->states, i) ? "1" : "0");
        else
            printf("-");
    }
}

char MintermAdjacent(Minterm *a, Minterm *b)
{
    // Implicante: numero de variables indefinidas
    char sameImplicantSize = (a->undefined == b->undefined);

    if (!sameImplicantSize)
    {
        return 0;
    }

    // aplicar la mascara y contar las diferencias
    BIT_TYPE implicantMask = a->undefined;
    BIT_TYPE aMask = a->states & implicantMask;
    BIT_TYPE bMask = b->states & implicantMask;

    return bitDiff(aMask, bMask) == 1;
}

Minterm MintermMerge(Minterm *a, Minterm *b)
{
    Minterm foo;
    BIT_TYPE diferences =  a->states & b->states;

    MintermInit(&foo, a->states & diferences, diferences);
    return foo;
}

int main()
{
    int n = 3; // numero de variables

    Minterm a;
    MintermInit(&a, 0b001, 0b101);

    Minterm b;
    MintermInit(&b, 0b101, 0b101);

    printf("los terminos '");
    MintermDisplay(n, &a);
    printf("' y '");
    MintermDisplay(n, &b);
    printf("' Son: ");

    printf(MintermAdjacent(&a, &b) ? "Adyacentes" : "NO Adyacentes");
    puts("");

    printf("El resultado de la union es: ");
    Minterm foo = MintermMerge(&a, &b);
    MintermDisplay(n, &foo);

    puts("");
    return 0;
}
