
#include <stdlib.h>
#include <stdio.h>

#include "import/bit.h"
#include "import/utils.h"
#include "import/macros.h"

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
    char adjacency[MAX_VARS][MAX_VARS] = {0};

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

int main()
{
    BIT_TESTS(12, 4);

    BIT_TYPE minterms[] = {4, 8, 9, 10, 11, 12, 14, 15};
    ADJACENCY_TEST(ARRAY_LENGHT(minterms), minterms);

    return EXIT_SUCCESS;
}
