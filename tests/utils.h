
/**
 * Coloca la representacion de value en stdout
 * @param value
 */
void bitPrint(BIT_TYPE value)
{
    for (char i = BIT_MAX_VARS - 1; i >= 0; i--)
        printf(bitState(value, i) ? "1" : "_");
}

void MintermDisplay(int vars, Minterm min)
{
    for (int i = vars - 1; i >= 0; i--)
    {
        if (bitState(min.undefined, i))
        {
            int state = bitState(min.states, i);
            printf(state ? "1" : "0");
        }
        else
        {
            printf("-");
        }
    }

    printf("  |  states:%3u  undefined:%3u", min.states, min.undefined);
}

void printMinterms(List *terms, int nvars)
{
    puts("");
    for (int i = 0; i < ListLenght(terms); i++)
    {
        Minterm current = LIST_GET(Minterm, terms, i);

        printf("%3d: ", i);
        MintermDisplay(nvars, current);
        puts("");
    }
}