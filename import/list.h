/**
 * AUTOR: Luis Eduardo Galindo Amaya                           FECHA: 23-04-2023
 *
 * DESCRIPCIÓN:
 * En este archivo se almacenan todos los métodos para controlar una lista
 * enlazada.
 */
#ifndef linkedList
#define linkedList

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * Obtener el valor en una posicion y converitirlo a su tipo
 */
#define LIST_GET(TYPE, LIST, INDEX) \
    (*((TYPE *)(ListGetNode(LIST, INDEX)->data)))

/**
 * Nodo de la lista
 */
typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

/**
 * Lista que contiene a los nodos
 */
typedef struct List
{
    Node *data;
    int lenght;
} List;

/**
 * Crear un nodo para la lista
 * @param puntero a cosa random
 */
Node *NodeCreate(void *data)
{
    Node *foo = (Node *)malloc(sizeof(Node));
    // if (foo == NULL)
    //     // Fallo al alocar memoria
    //     return NULL;

    foo->data = data;
    foo->next = NULL;
    return foo;
}

/**
 * liberar el nodo
 */
void NodeFree(Node *node)
{
    free(node->data);
    node->next = NULL;
}

/**
 * Validar si la lista esta vacia
 */
int ListEmpty(List *list)
{
    return list->data == NULL;
}

/**
 * Cantidad de nodos en la lista
 */
int ListLenght(List *list)
{
    return list->lenght;
}

/**
 * Inicializar lista
 */
List ListInit(List *list)
{
    list->data = NULL;
    list->lenght = 0;
    return *list;
}

/**
 * Obtener el puntero a un nodo de la lista
 */
Node *ListGetNode(List *list, int index)
{
    assert(index >= 0);
    assert(index <= ListLenght(list));

    Node *node = list->data;
    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }

    return node;
}

/**
 * Insertar un elemento en la lista
 */
void ListInsert(List *list, int index, void *data)
{
    assert(index >= 0);
    assert(index <= ListLenght(list));

    Node *newNode = NodeCreate(data);

    if (ListEmpty(list) || index == 0)
    {
        newNode->next = list->data;
        list->data = newNode;
        list->lenght++;
        return;
    }

    // obtiene la posicion anterior
    Node *prev = ListGetNode(list, index - 1);
    Node *curret = prev->next;

    newNode->next = curret;
    prev->next = newNode;
    list->lenght++;
}

void ListRemove(List *list, int index)
{
    assert(index >= 0);
    assert(index <= ListLenght(list));
    assert(!ListEmpty(list));

    if (index == 0)
    {
        Node *next = (list->data)->next;
        NodeFree(list->data);
        free(list->data);
        list->data = next;
        list->lenght -= 1;
        return;
    }

    // obtiene la posicion anterior
    Node *prev = ListGetNode(list, index - 1);
    Node *curret = prev->next;

    prev->next = curret->next;
    NodeFree(curret);
    free(curret);
    list->lenght -= 1;
}

void ListFree(List *list)
{
    while (!ListEmpty(list))
        ListRemove(list, 0);
}

#endif