
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

void TermsConvine(List *terms, List *minterms)
{
    for (int i = ListLenght(terms) - 1; i >= 0; i--)
    {
        Minterm ter_i = LIST_GET(Minterm, terms, i);
        int merged = 0;

        for (int j = ListLenght(terms) - 1; j >= 0; j--)
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
                ListInsert(
                    terms,
                    ListLenght(terms),
                    MintermCreate(merge.states, merge.undefined));
            }
        }

        
        if (!merged && !TermExist(minterms, ter_i))
        {
            // si el termino no se unio a nada, agregar a los minterminos
            ListInsert(
                minterms, 0,
                MintermCreate(ter_i.states, ter_i.undefined));
        }

        // ListRemove(terms, i);
    }
}

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

    int nvars = 4;
    BIT_TYPE act[] = {
        4,
        8,
        9,
        10,
        11,
        12,
        14,
        15,
    };

    // int nvars = 6;
    // BIT_TYPE act[] = {
    //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    //     11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    //     21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    //     31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    //     41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
    //     51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    //     61, 62, 63};

    // cargar minterminos
    for (int i = ARRAY_LENGHT(act) - 1; i >= 0; i--)
    {
        ListInsert(&terms, 0, MintermCreate(act[i], ~0));
    }

    TermsConvine(&terms, &minterms);
    TermsConvine(&terms, &minterms);
    TermsConvine(&terms, &minterms);
    TermsConvine(&terms, &minterms);

    puts("> Terminos");
    for (int i = 0; i < ListLenght(&terms); i++)
    {
        Minterm current = LIST_GET(Minterm, &terms, i);

        printf("%3d: ", i);
        MintermDisplay(nvars, current);
        puts("");
    }

    puts("> Minterminos");
    for (int i = 0; i < ListLenght(&minterms); i++)
    {
        Minterm current = LIST_GET(Minterm, &minterms, i);

        printf("%3d: ", i);
        MintermDisplay(nvars, current);
        puts("");
    }

    ListFree(&terms);
    ListFree(&minterms);
    return 0;
}
