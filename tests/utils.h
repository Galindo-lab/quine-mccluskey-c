
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
}