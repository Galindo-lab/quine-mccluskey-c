
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "import/list.h"
#include "import/minterm.h"
#include "import/macros.h"

#include "tests/utils.h"

int TermExist(List *terms, Minterm term)
{
    Minterm current;
    for (int i = ListLenght(terms) - 1; i >= 0; i--)
    {
        current = LIST_GET(Minterm, terms, i);
        if (MintermEquals(term, current))
        {
            return 1;
        }
    }

    return 0;
}

Minterm *TermCopy(Minterm *foo)
{
    return MintermCreate(foo->states, foo->undefined);
}

int TermsConvine(List *terms, List *minterms)
{
    int ac_total = 0;
    for (int i = ListLenght(terms) - 1; i >= 0; i--)
    {
        Minterm ter_i = LIST_GET(Minterm, terms, i);
        int merged = 0;

        for (int j =i - 1; j >= 0; j--)
        {
            Minterm ter_j = LIST_GET(Minterm, terms, j);

            if (!MintermAdjacent(ter_i, ter_j))
            {
                continue;
            }

            Minterm merge = MintermMerge(ter_i, ter_j);
            merged++;
            if (!TermExist(terms, merge))
            {
                ac_total++;
                ListInsert(terms, ListLenght(terms), TermCopy(&merge));
            }
        }

        if (!merged && !TermExist(minterms, ter_i))
        {
            // si el termino no se unio a nada, agregar a los minterminos
            ListInsert(minterms, 0, TermCopy(&ter_i));
        }

        // ListRemove(terms, i);
    }

    printf("%d nodos en la lista\n"
           "%d terminos creados \n", ListLenght(terms), ac_total);
    return ac_total;
}

void printMinterms(List* terms,int nvars)
{
    puts("");
    for (int i = 0; i < ListLenght(terms); i++)
    {
        Minterm current = LIST_GET(Minterm, terms, i);

        printf("%03d: ", i);
        MintermDisplay(nvars, current);
        puts("");
    }
}

int main()
{
    List terms = ListInit(&terms);
    List minterms = ListInit(&minterms);

    // int nvars = 2;
    // BIT_TYPE act[] = {0,1,2,3};

    //int nvars = 3;
    //BIT_TYPE act[] = {0, 1, 2,3, 4,5,6, 7};

    // int nvars = 3;
    // BIT_TYPE act[] = {0, 1, 2, 4, 7};

    // int nvars = 4;
    // BIT_TYPE act[] = {4,8,9,10,11,12,14,15};

    int nvars = 6;
    BIT_TYPE act[] = {
        0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
        51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
        61, 62, 63};

    //int nvars = 6;
    //BIT_TYPE act[] = {0, 1, 2, 3};

    // cargar minterminos
    for (int i = ARRAY_LENGHT(act) - 1; i >= 0; i--)
    {
        ListInsert(&terms, 0, MintermCreate(act[i], ~0));
    }

    int cnv = 0;
    int tanterior = ListLenght(&terms);
    while ((cnv = TermsConvine(&terms, &minterms)))
    {
        printf("eliminar %d terminos\n\n", tanterior);
        for (int i = 0; i < tanterior; i++)
        {
            ListRemove(&terms, 0);
        }
        
        // puts("----");
        // printMinterms(&terms, nvars);
        tanterior = ListLenght(&terms);
    }


    printf("\n> Minterminos");
    printMinterms(&terms, nvars);


    ListFree(&terms);
    ListFree(&minterms);
    return 0;
}
