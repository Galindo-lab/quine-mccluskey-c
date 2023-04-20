/**
 * AUTOR: Luis Eduardo Galindo Amaya                           FECHA: 03-04-2023
 *
 * DESCRIPCIÓN:
 * Bibloteca para representar grafos con una matriz de adyacensia en C
 */

#include <stdlib.h>
#include <stdio.h>

#define GRAPH_DATA_TYPE char

struct Graph
{
    GRAPH_DATA_TYPE *data;
    int lenght;
};

typedef struct Graph Graph;

int graphLenght(Graph *graph)
{
    return graph->lenght;
}

/**
 * Inicializacion del nodo
 * @param graph puntero al nodo
 * @param nodes numero de nodos del grafo
 */
void graphInit(Graph *graph, int nodes)
{
    int foo = (nodes * (nodes - 1)) >> 1;
    graph->data = (GRAPH_DATA_TYPE*) calloc(foo, sizeof(GRAPH_DATA_TYPE));

    graph->lenght = nodes;
}

/**
 * Liberar el espacio de los nodos
 * @param graph puntero al nodo
 */
void graphFree(Graph *graph)
{
    free(graph->data);
    graph->data = NULL;
    graph->lenght = 0;
}

/**
 * Determinar si un edge no esta conectado a si mismo o si el nodo existe
 * @param graph puntero al grafo
 * @param origin nodo
 * @param destiny nodo
 * @param boolean
 */
int graphValidPosition(Graph *graph, int origin, int destiny)
{
    // encontrar el minimo
    int minn = origin < destiny ? origin : destiny;
    // encontrar el maximo
    int maxn = origin > destiny ? origin : destiny;
    int nodes = graph->lenght;

    if (minn == maxn)
        // nodo conectado a si mismo
        return 0;

    if (maxn >= nodes || minn < 0)
        // nodo mas grande que la cantidad de espacio disponible
        return 0;

    return 1;
}

/**
 * Conveierte las posiciones de 2 nodos en el indice numerico
 * que representa su arista,
 *
 * @note el orden de origin y destiny no es importante.
 *
 * @param graph direccion al grafo
 * @param origin indice del nodo de origen
 * @param destiny indice del nodo destino
 * @return int
 */
int graphEdgeIndex(Graph *graph, int origin, int destiny)
{
    // encontrar el minimo
    int minn = origin < destiny ? origin : destiny;
    // encontrar el maximo
    int maxn = origin > destiny ? origin : destiny;
    int nodes = graph->lenght;

    if (!graphValidPosition(graph, maxn, minn))
    {
        puts("graphEdgeIndex: Posicion invalida");
        exit(EXIT_FAILURE);
    }

    
    int foo = minn * (minn + 1) >> 1;
    return minn * nodes - foo + (maxn - minn - 1);
}

/**
 * Cambiar el valor del edge entre dos nodos
 */
void graphSetEdgeWeight(Graph *graph, int origin, int destiny, GRAPH_DATA_TYPE weigth)
{
    graph->data[graphEdgeIndex(graph, origin, destiny)] = weigth;
}

/**
 * Obtener el valor del edge entre dos nodos
 */
GRAPH_DATA_TYPE graphGetEdgeWeight(Graph *graph, int origin, int destiny)
{
    return graph->data[graphEdgeIndex(graph, origin, destiny)];
}