
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
    int nvars = 6;
    BIT_TYPE minterms[] = {2, 4, 6};
    int lenght =  ARRAY_LENGHT(minterms);

    int array_size = nvars * lenght;
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
            for (int j = i+1; j < bar; j++)
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
        MintermDisplay(nvars, &(reducciones[i]));
        puts("");
    }

    return 0;
}
