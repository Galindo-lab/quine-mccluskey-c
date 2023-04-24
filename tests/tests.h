

void BIT_TESTS(BIT_TYPE a, BIT_TYPE b)
{
    bitPrint(a);
    puts("");
    bitPrint(b);
    puts("");

    printf("diferencias: %d\n", bitDiff(a, b));
}

/**
 * Contruye una grafo donde los nodos solo tienen un bit de
 * diferencia
 */
void ADJACENCY_TEST(int len_minterms, BIT_TYPE minterms[])
{
    char adjacency[BIT_MAX_VARS][BIT_MAX_VARS] = {0};

    for (int i = 0; i < len_minterms; i++)
    {
        for (int j = 0; j < len_minterms; j++)
        {
            adjacency[i][j] = bitDiff(minterms[i], minterms[j]) == 1;
            printf(adjacency[i][j] == 1 ? "1 " : "- ");
        }
        puts("");
    }
}

void MAIN_TESTS()
{
    BIT_TESTS(12, 4);

    BIT_TYPE minterms[] = {4, 8, 9, 10, 11, 12, 14, 15};
    ADJACENCY_TEST(ARRAY_LENGHT(minterms), minterms);

    puts("aaa");

    // BIT_TYPE tabulacion[8] = {0};
}

void MINTERM_TEST()
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
}