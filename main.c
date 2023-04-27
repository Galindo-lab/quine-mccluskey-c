
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "import/list.h"
#include "import/minterm.h"
#include "import/findMinterms.h"

#include "tests/utils.h"
#include "import/macros.h"

int main()
{
    List terms = ListInit(&terms);
    List minterms = ListInit(&minterms);

    // int nvars = 2;
    // BIT_TYPE act[] = {0,1,2,3};

    // int nvars = 3;
    // BIT_TYPE act[] = {0, 1, 2,3, 4,5,6, 7};

    // int nvars = 3;
    // BIT_TYPE act[] = {0, 1, 2, 4, 7};

    //int nvars = 4;
    //BIT_TYPE act[] = {4, 8, 9, 10, 11, 12, 14, 15};

    // int nvars = 4;
    // BIT_TYPE act[] = {4,12};

    int nvars = 6;
    BIT_TYPE act[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

    // int nvars = 6;
    // BIT_TYPE act[] = {0, 1, 2, 3};

    // cargar minterminos ----------------------------------------------------
    for (int i = ARRAY_LENGHT(act) - 1; i >= 0; i--)
    {
        ListInsert(&terms, 0, MintermCreate(act[i], ~0));
    }

    // reduce terminos -------------------------------------------------------
    findMinterms(&terms, &minterms);
    printf("\n> Minterminos -----------------------------------------------");
    printMinterms(&minterms, nvars);

    // crear expresion -------------------------------------------------------
    BIT_TYPE freq[ARRAY_LENGHT(act)] = {0};
    BIT_TYPE loq[ARRAY_LENGHT(act)] = {0};

    puts("> Minterminos Primos  -------------------------------------------");
    for (int i = 0; i < ListLenght(&minterms); i++)
    {
        Minterm min_i = LIST_GET(Minterm, &minterms, i);

        // Encontrar de que terminos forma parte
        for (int j = 0; j < ARRAY_LENGHT(act); j++)
        {
            Minterm a = MintermInit(&a, act[j], min_i.undefined);
            if (MintermEquals(a, min_i))
            {
                loq[j] = 1;
            }
        }

        // verificar que es un mintermino primo
        for (int k = 0; k < ListLenght(&minterms); k++)
        {

            if (i == k)
            {
                continue;
            }

            Minterm min_k = LIST_GET(Minterm, &minterms, k);
            for (int j = 0; j < ARRAY_LENGHT(act); j++)
            {
                Minterm a = MintermInit(&a, act[j], min_k.undefined);
                if (MintermEquals(a, min_k) && loq[j] == 1)
                {
                    loq[j] = 0;
                }
            }
        }
        
        for (int l = 0; l < ARRAY_LENGHT(loq); l++)
        {
            if (loq[l])
            {
                printf("%3d primo: ", act[l] );
                MintermDisplay(nvars, min_i);
                puts("");
            }
            
            loq[l] = 0;
        }
    }

    // for (int i = 0; i < ListLenght(&minterms); i++)
    // {
    //     Minterm min_i = LIST_GET(Minterm, &minterms, i);
    //     for (int j = 0; j < ARRAY_LENGHT(act); j++)
    //     {
    //         Minterm a = MintermInit(&a,act[j], min_i.undefined);
    //         if (MintermEquals(a, min_i))
    //         {
    //             freq[j] += 1;
    //         }
    //     }
    // }

    // printf("> Frecuencias\n");
    // for (int i = 0; i < ARRAY_LENGHT(act); i++)
    // {
    //     printf("%3d: %d\n", act[i], freq[i]);
    // }

    ListFree(&terms);
    ListFree(&minterms);
    return 0;
}
