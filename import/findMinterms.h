
/**
 * Verifica si un mintermino existe en una lista
 */
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

/**
 * Crea una instancia nueva en base a los valores de otro termino
 */
Minterm *TermCopy(Minterm *foo)
{
    return MintermCreate(foo->states, foo->undefined);
}

/**
 * realiza todas las convinaciones posibles con los elementos de la lista
 * los valores nuevos se agregan al final de los terminos, por lo que de
 * deben eliminar
 */
int TermsConvine(List *terms, List *minterms)
{
    int ac_total = 0; // uniones totales de los terminos
    int merged = 0;   // numero de uniones del termino i

    Minterm ter_i;
    Minterm ter_j;
    Minterm merge;

    for (int i = ListLenght(terms) - 1; i >= 0; i--)
    {
        merged = 0;

        for (int j = ListLenght(terms) - 1 - ac_total; j >= 0; j--)
        {
            ter_i = LIST_GET(Minterm, terms, i);
            ter_j = LIST_GET(Minterm, terms, j);

            if (!MintermAdjacent(ter_i, ter_j))
            {
                continue;
            }

            merge = MintermMerge(ter_i, ter_j);
            merged++;
            if (!TermExist(terms, merge))
            {
                ac_total++;
                ListInsert(terms, ListLenght(terms), TermCopy(&merge));
            }
        }

        if (merged == 0 && !TermExist(minterms, ter_i))
        {
            // si el termino no se unio a nada, agregar a los minterminos
            ListInsert(minterms, 0, TermCopy(&ter_i));
        }
    }

    // printf("%d nodos en la lista\n"
    //        "%d terminos creados \n",
    //        ListLenght(terms), ac_total);
    return ac_total;
}

void findMinterms(List *terms, List *minterms)
{
    int tanterior = ListLenght(terms); // tamaño anterior de la lista
    while (TermsConvine(terms, minterms))
        {
            // printMinterms(&terms, nvars);
            // printf("eliminar %d terminos\n\n", tanterior);
            for (int i = 0; i < tanterior; i++)
            {
                ListRemove(terms, 0);
            }

            // puts("----");
            // printMinterms(&terms, nvars);
            tanterior = ListLenght(terms);
        }
}