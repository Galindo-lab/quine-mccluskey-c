
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

Node *NodeCreate(void *data)
{
    Node *foo = malloc(sizeof(Node));
    if (foo == NULL)
        // Fallo al alocar memoria
        return NULL;

    foo->data = data;
    foo->next = NULL;
    return foo;
}

void NodeFree(Node *node)
{
    free(node->data);
    node->next = NULL;
}

typedef struct List
{
    Node *data;
    int lenght;
} List;

int ListLenght(List *list)
{
    return list->lenght;
}

/**
 * Validaciones comunes entre los metodos
 */
int ListValidIndex(List *list, int index)
{
    if (index < 0)
    {
        puts("idex < 0");
        return 0;
    }

    if (index > ListLenght(list))
    {
        puts("index > ListLenght");
        return 0;
    }

    return 1;
}

List ListInit(List *list)
{
    list->data = NULL;
    list->lenght = 0;
    return *list;
}

Node *ListGetNode(List *list, int index)
{
    assert(ListValidIndex(list, index));

    Node *node = list->data;
    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }

    return node;
}

void ListInsert(List *list, int index, void *data)
{
    assert(ListValidIndex(list, index));
    Node *new = NodeCreate(data);

    if (ListLenght(list) == 0 || index == 0)
    {
        new->next = list->data;
        list->data = new;
        list->lenght++;
        return;
    }
    
    // obtiene la posicion anterior
    Node *prev = ListGetNode(list, index - 1);
    Node *curret = prev->next;

    new->next = curret;
    prev->next = new;
    list->lenght++;
}

int main()
{
    List list = ListInit(&list);
    int *c = malloc(sizeof(int));
    *c = 2;

    ListInsert(&list, 0, c);

    c = malloc(sizeof(int));
    *c = 1;

    ListInsert(&list, 0, c);

    c = malloc(sizeof(int));
    *c = 0;

    ListInsert(&list, 0, c);

    c = malloc(sizeof(int));
    *c = 4;

    ListInsert(&list, 3, c);

    for (int i = 0; i < ListLenght(&list); i++)
    {
        int a = *((int *)(ListGetNode(&list, i)->data));
        printf("%d\n", a);
    }

    return 0;
}
