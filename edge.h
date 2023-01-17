#ifndef EDGE_H
#define EDGE_H

#include "node.h"

typedef struct Graph Graph;;

typedef struct Edge
{
    int weight;
    struct Graph *dst;
    struct Edge *next;

}Edge;

#endif //EDGE_H