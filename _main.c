
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "import/minterm.h"
#include "tests/utils.h"
#include "import/macros.h"

// #include "tests.h" // elimnar para el relase

int MintermExist(int last, Minterm *list, Minterm minterm)
{
    for (int i = 0; i < last; i++)
    {
        Minterm foo = list[i];
        if (MintermEquals(foo, minterm))
        {
            // si hay un termino igual
            return 1;
        }
    }

    return 0;
}

/*
 * Genera todas las convinaciones posibles con los elementos de reducciones
 * @param maxLenght tamaño maximo de la lista
 * @param lenght tamano de la lista
 * @param *reducciones
 */
void convineMinterms(int maxLenght, int *lenght, Minterm *reducciones)
{
    int last = *lenght;
    int convinaciones = 0;
    do
    {
        convinaciones = 0;
        for (int i = last - 1; i >= 0; i--)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                Minterm reducciones_i = reducciones[i];
                Minterm reducciones_j = reducciones[j];

                if (!MintermAdjacent(reducciones_i, reducciones_j))
                {
                    continue;
                }

                Minterm merge = MintermMerge(reducciones_j, reducciones_i);
                if (!MintermExist(last, reducciones, merge))
                {
                    assert(last < maxLenght);
                    reducciones[last] = merge;
                    last++;
                    convinaciones++;
                }
            }
        }
    } while (convinaciones > 0);

    *lenght = last;
}

int main()
{
    // int nvars = 3;
    // BIT_TYPE minterms[] = {0, 1, 2, 3, 4, 5, 6, 7};

    // int nvars = 3;
    // BIT_TYPE minterms[] = {0, 1, 2, 4, 7};

    // int nvars = 4;
    //   BIT_TYPE minterms[] = {0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    //  BIT_TYPE minterms[] = {0, 4, 5, 6, 7, 8, 9, 12, 13, 14, 15};

    // int nvars = 5;
    // BIT_TYPE minterms[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

    int nvars = 6;
    BIT_TYPE minterms[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

    // int nvars = 2;
    // BIT_TYPE minterms[] = {0,1,2,3};

    int lenght = ARRAY_LENGHT(minterms);

    int array_size = 800; // nvars * lenght;
    Minterm *reducciones = (Minterm *)calloc(array_size, sizeof(Minterm));
    int last = 0;

    Minterm *minterminos = (Minterm *)calloc(lenght, sizeof(BIT_TYPE));
    int minterminos_last = 0;

    for (int i = 0; i < lenght; i++)
    {
        // cargar los minterminos a la lista
        MintermInit(&(reducciones[i]), minterms[i], ~0);
        last++;
    }

    // for (int i = 0; i < lenght; i++)
    // {
    //     int convined = 0;
    //     for (int j = 0; j < lenght; j++)
    //     {
    //         Minterm reducciones_i = MintermInit(&reducciones_i, minterms[i], ~0);
    //         Minterm reducciones_j = MintermInit(&reducciones_j, minterms[j], ~0);

    //         if (MintermAdjacent(reducciones_i, reducciones_j))
    //         {
    //             Minterm merge = MintermMerge(reducciones_j, reducciones_i);
    //             if (!MintermExist(last, reducciones, merge))
    //             {
    //                 reducciones[last] = merge;
    //                 last++;
    //             }

    //             convined++;
    //         }
    //     }

    //     if (!convined)
    //     {
    //         Minterm reducciones_i;
    //         MintermInit(&reducciones_i, minterms[i], ~0);

    //         minterminos[minterminos_last] = reducciones_i;
    //         minterminos_last++;
    //     }
    // }

    convineMinterms(array_size, &last, reducciones);

    // -----------------------------------------

    for (int i = 0; i < last; i++)
    {
        printf("%3d: ", i);
        MintermDisplay(nvars, reducciones[i]);
        puts("");
    }

    printf("*** Minterminos ***\n");
    for (int i = 0; i < minterminos_last; i++)
    {
        printf("%3d: ", i);
        MintermDisplay(nvars, minterminos[i]);
        puts("");
    }

    printf("array size: %d\n", array_size);

    return 0;
}
