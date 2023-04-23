
#include <stdlib.h>
#include <stdio.h>

#include "import/graph.h"
#include "import/minterm.h"
#include "import/utils.h"
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

int main()
{
    //int nvars = 3;
    //BIT_TYPE minterms[] = {0, 1, 2, 3, 4, 5, 6, 7};

    int nvars = 4;
    //BIT_TYPE minterms[] = {0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    BIT_TYPE minterms[] = {0, 4, 5, 6, 7, 8, 9, 12, 13, 14, 15};

    //int nvars = 5;
    //BIT_TYPE minterms[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

    //int nvars = 6;
    //BIT_TYPE minterms[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63};

    //int nvars = 2;
    //BIT_TYPE minterms[] = {0,1,2,3};

    int lenght = ARRAY_LENGHT(minterms);

    int array_size = 800;//nvars * lenght;
    Minterm *reducciones = (Minterm *)calloc(array_size, sizeof(Minterm));
    // Minterm reducciones[15] = {0};
    int last = 0;

    for (int i = 0; i < lenght; i++)
    {
        // cargar los minterminos a la lista
        MintermInit(&(reducciones[i]), minterms[i], ~0);
        last++;
    }

    int convinaciones = 0;
    do
    {
        convinaciones = 0;
        int bar = last;
        for (int i = 0; i < bar; i++)
        {
            for (int j = i + 1; j < bar; j++)
            {
                Minterm reducciones_i = reducciones[i];
                Minterm reducciones_j = reducciones[j];
                Minterm merge;

                if (MintermAdjacent(reducciones_i, reducciones_j))
                {
                    merge = MintermMerge(reducciones_j, reducciones_i);
                    if (!MintermExist(last, reducciones, merge))
                    {
                        reducciones[last] = merge;
                        last++;
                        convinaciones++;
                    }
                }
            }
        }

    } while (convinaciones > 0);

    // -----------------------------------------

    for (int i = 0; i < last; i++)
    {
        printf("%3d: ", i);
        MintermDisplay(nvars, reducciones[i]);
        puts("");
    }

    printf("array size: %d\n", array_size);

    return 0;
}
