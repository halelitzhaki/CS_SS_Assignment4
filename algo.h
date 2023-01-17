#ifndef ALGO_H
#define ALGO_H

#include "edge.h"

#define NEW_GRAPH 'A'
#define NEW_NODE 'B'
#define SHORTEST_PATH 'S'
#define SHORTEST_PATH_NODE 'T'
#define DELETE_NODE 'D'
#define END '\n'
#define INSERT_NEW_NODE 'n'
#define NOT_FOUND -1
#define TRUE 1
#define FALSE 0
#define INFINITY 2147483640

typedef struct Graph
{
    int visited;
    struct Node node;
    struct Edge *edges;
    struct Graph *next;
}Graph;

void build_graph(Graph *head, char *choice);
void insert_node(Graph *head, Graph *node, char *choice);
void new_node(Graph *head, char *choice);
Graph* deleteNode(Graph * head, char *choice);
Edge* deleteEdges(Graph *head);
void printGraph(Graph *head); 
Graph* deleteGraph(Graph **head);
int shortestPath(Graph * head, char u, char v);
Edge* minNode(Edge * node);
Edge* isFound(Edge * node, int dst);
int fact(int num);
int** permute(int ** result, int *arr, int l, int r, int *count);
void swap(int *a, int *b);
void TSP(Graph *head, char * choice);

#endif //ALGO_H