
/**
 * Coloca la representacion de value en stdout
 * @param value 
*/
void bitPrint(BIT_TYPE value)
{
    for (char i = BIT_MAX_VARS - 1; i >= 0; i--)
        printf(bitState(value, i) ? "1" : "_");
}


void MintermDisplay(char vars, Minterm *min)
{
    for (char i = vars - 1; i >= 0; i--)
    {
        if (bitState(min->undefined, i))
        {
            printf(bitState(min->states, i) ? "1" : "0");
        }
        else
        {
            printf("-");
        }
    }
}