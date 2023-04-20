
#include <stdlib.h>
#include <stdio.h>

#include "import/graph.h"
#include "import/minterm.h"
#include "import/utils.h"
#include "import/macros.h"

// #include "tests.h" // elimnar para el relase

char MintermExist(int last, Minterm *list, Minterm *minterm)
{
    for (int i = 0; i < last; i++)
    {
        if (MintermEquals(&(list[i]), minterm))
        {
            // si hay un termino igual
            return 1;
        }
    }

    return 0;
}

int main()
{
    int nvars = 3;
    BIT_TYPE minterms[] = {0,2,4,6,7};
    int lenght = ARRAY_LENGHT(minterms);

    int array_size = nvars * lenght;
    Minterm *reducciones = (Minterm *)calloc(array_size, sizeof(Minterm));
    int last = 0;

    Minterm ac;
    for (int i = 0; i < lenght; i++)
    {
        MintermInit(&ac, minterms[i], ~0);
    }

    for (int i = 0; i < last; i++)
    {
        MintermDisplay(nvars, &(reducciones[i]));
        puts("");
    }
    

    return 0;
}
