

#include "./import/list.h"


char* createInt(char a)
{
    char *c = malloc(sizeof(char));
    *c = a;
    return c;
}



int main()
{
    List list = ListInit(&list);

    ListInsert(&list, 0, createInt(0));
    ListRemove(&list, 0);

    ListInsert(&list, 0, createInt(1));
    ListInsert(&list, 1, createInt(2));
    ListInsert(&list, 0, createInt(3));

    for (int i = 0; i < ListLenght(&list); i++)
    {
        // int a = *((int *)(ListGetNode(&list, i)->data));
        int a = LIST_GET(int, &list, i);
        printf("%d\n", a);
    }

    ListFree(&list);
    return 0;
}
