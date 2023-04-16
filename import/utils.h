
/**
 * Coloca la representacion de value en stdout
 * @param value 
*/
void bitPrint(BIT_TYPE value)
{
    for (char i = MAX_VARS - 1; i >= 0; i--)
        printf(bitState(value, i) ? "1" : "_");
}
