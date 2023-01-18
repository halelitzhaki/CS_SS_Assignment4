#include "algo.h"

void build_graph(Graph *head, char *choice) {
    Graph *temp = head;
    *choice = fgetc(stdin);
    char space = fgetc(stdin); 
    for(int i = 0; i < *choice - '0'; i++) {
        head->node.number = i;
        head->visited = FALSE;
        if(i == (*choice - '0') - 1) {
            head->next = NULL;
            break;
        }
        head->next = (Graph*)malloc(sizeof(Graph));
        head = head->next;
    }
    head = temp;
    if(space == END) return;
    if(space != INSERT_NEW_NODE) {
        *choice = fgetc(stdin);
        space = fgetc(stdin);
    }
    else{
        *choice = space;
        space = fgetc(stdin);
    }

    if(*choice != INSERT_NEW_NODE) {
        *choice = END;
        return;
    }

    while (*choice != NEW_GRAPH && *choice != NEW_NODE && *choice != SHORTEST_PATH 
        && *choice != SHORTEST_PATH_NODE && *choice != DELETE_NODE && *choice != END && *choice != CHAR_NULL) {

        *choice = fgetc(stdin); 
        space = fgetc(stdin);
        while(head != NULL) {
            if(head->node.number == *choice - '0') break;
            head = head->next;
        }
        *choice = fgetc(stdin); 
        if(*choice == INSERT_NEW_NODE || *choice == NEW_GRAPH || *choice == NEW_NODE 
            || *choice == SHORTEST_PATH || *choice == SHORTEST_PATH_NODE || *choice == DELETE_NODE || *choice == END || *choice == CHAR_NULL) {
            head = temp;
            if(*choice != END && *choice != CHAR_NULL) space = fgetc(stdin);
            break;
        }
        space = fgetc(stdin);
        head->edges = (Edge*)malloc(sizeof(Edge));
        insert_node(temp, head, choice);
        head = temp;
    }
}

void insert_node(Graph *head, Graph *node, char *choice) {
    Edge * temp1 = node->edges;
    Graph * temp2 = head;
    char space;
    while(*choice != INSERT_NEW_NODE && *choice != NEW_GRAPH && *choice != NEW_NODE  
        && *choice != SHORTEST_PATH && *choice != SHORTEST_PATH_NODE && *choice != DELETE_NODE && *choice != END && *choice != CHAR_NULL) {

        while(temp2 != NULL) {
            if(temp2->node.number == *choice - '0') break;
            temp2 = temp2->next;
        }
        node->edges->dst = temp2;
        temp2 = head;

        *choice = fgetc(stdin);
        space = fgetc(stdin);
        
        node->edges->weight = *choice - '0';
        
        
        if(space == END) {
            *choice = END;
            break;
        }
        else if(space == CHAR_NULL) {
            *choice = CHAR_NULL;
            break;
        }
        *choice = fgetc(stdin);
        space = fgetc(stdin);
        if(*choice == INSERT_NEW_NODE || *choice == NEW_GRAPH || *choice == NEW_NODE 
            || *choice == SHORTEST_PATH || *choice == SHORTEST_PATH_NODE || *choice == DELETE_NODE || *choice == END || *choice == CHAR_NULL) {
            node->edges->next = NULL;
            break;
        }

        node->edges->next = (Edge*)malloc(sizeof(Edge));
        node->edges = node->edges->next;
    }
    node->edges = temp1;
}

Graph* new_node(Graph **head, char *choice) {
    Graph *temp = *head, *ttemp = temp;
    *choice = fgetc(stdin);
    char space = fgetc(stdin);
    if(space == END || space == CHAR_NULL) return ttemp;
     
    while(temp != NULL) {
        if(temp->node.number == *choice - '0') {
            temp->edges = deleteEdges(temp);
            break;
        }
        if(temp->next == NULL) {
            temp->next = (Graph*)malloc(sizeof(Graph));
            temp = temp->next;
            temp->node.number = *choice - '0';
            temp->edges = NULL;
            break;
        }
        temp = temp->next;
    }
    *choice = fgetc(stdin); 
    
    if(*choice == INSERT_NEW_NODE || *choice == NEW_GRAPH || *choice == NEW_NODE 
        || *choice == SHORTEST_PATH || *choice == SHORTEST_PATH_NODE || *choice == DELETE_NODE) {
        space = fgetc(stdin);
        return ttemp;
    }
    space = fgetc(stdin);
    temp->edges = (Edge*)malloc(sizeof(Edge));
    insert_node(ttemp, temp, choice);
    return ttemp;
}

Graph* deleteNode(Graph * head, char *choice) {
    Graph *temp = head;
    *choice = fgetc(stdin);
    char space = fgetc(stdin); 

    while (head != NULL) {
        Edge * edge = head->edges;
        while(head->edges != NULL) {
            if(head->node.number == *choice - '0') break;
            if(head->edges->dst->node.number == *choice - '0') {
                edge = head->edges->next;
                Edge * temp2 = head->edges;
                free(temp2);
                break;
            }
            else if(head->edges->next != NULL && head->edges->next->dst->node.number == *choice - '0') {
                Edge * temp2 = head->edges->next;
                head->edges->next = head->edges->next->next;
                free(temp2);
                break;
            }
            else if (head->edges != NULL) head->edges = head->edges->next;
        }
        head->edges = edge;
        head = head->next;
    }
    head = temp;
    while(head != NULL) {
        if(head->node.number == *choice - '0') {
            head->edges = deleteEdges(head);
            temp = head->next;
            Graph * temp1 = head;
            free(temp1);
            break;
        }
        else if(head->next != NULL && head->next->node.number == *choice - '0') {
            head->next->edges = deleteEdges(head->next);
            Graph * temp1 = head->next;
            head->next = head->next->next;
            free(temp1);
            break;
        }
        else if(head != NULL) head = head->next;
    }
    head = temp;

    if(space == END || space == CHAR_NULL) {
        *choice = END;
        return head;
    }
    *choice = fgetc(stdin);
    space = fgetc(stdin);
    return head;
}

Edge* deleteEdges(Graph *head) {
    Edge ** pEdge = &head->edges, *temp = head->edges, *next = NULL;
    while(temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    *pEdge = NULL;
    return *pEdge;
}

Graph* deleteGraph(Graph** head) {
    Graph *temp = *head, *next = NULL;
    while(temp != NULL) {
        temp->edges = deleteEdges(temp);
        next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    return *head;
}

void printGraph(Graph * head) {
    while(head != NULL) {
        if(head->edges == NULL) printf("%d \n",head->node.number);
        else {
            Edge * temp = head->edges;
            while(head->edges != NULL) {
                printf("%d ----%d----> %d \n",head->node.number, head->edges->weight, head->edges->dst->node.number);
                head->edges = head->edges->next;
            }
            head->edges = temp;
        }
        head = head->next;
    }
}

int shortestPath(Graph * head, char u, char v) {
    int minWeight = 0, minWeightFound = 0, found = FALSE;
    Graph * temp = head;

    if(u == v) return minWeight;
    else {
        while (head != NULL) {
            if(head->node.number == u - '0') break;
            head = head->next;
        }
        if(head->edges == NULL) return NOT_FOUND;
        else{
            while(head != NULL) {
                Edge *edgeTemp = head->edges, *minEdge = NULL, *edgeFound = NULL;
                if(head->edges != NULL) {
                    minEdge = minNode(head->edges);
                    head->visited = TRUE;
                    edgeFound = isFound(head->edges, v - '0');
                }
                if(minEdge->dst->node.number == v - '0') {
                    minWeight += minEdge->weight;
                    head = temp;
                    while(temp != NULL) {
                        temp->visited = FALSE;
                        temp = temp->next;
                    }
                    return minWeight;
                }
                if(edgeFound != NULL) {
                    found = TRUE;
                    minWeightFound = minWeight + edgeFound->weight;
                }
                if((minEdge->dst == NULL || minEdge->dst->edges == NULL || head->edges == NULL || minEdge->dst->visited == TRUE) && found == TRUE) {
                    head = temp;
                    while(temp != NULL) {
                        temp->visited = FALSE;
                        temp = temp->next;
                    }
                    return minWeightFound;
                }
                if((minEdge->dst == NULL || minEdge->dst->edges == NULL || head->edges == NULL || minEdge->dst->visited == TRUE) && found == FALSE) {
                    head = temp;
                    while(temp != NULL) {
                        temp->visited = FALSE;
                        temp = temp->next;
                    }
                    return NOT_FOUND;
                }
                minWeight += minEdge->weight;
                head->edges = edgeTemp;
                head = minEdge->dst;
            }
        head = temp;
        }
    }
    while(temp != NULL) {
        temp->visited = FALSE;
        temp = temp->next;
    }
    return NOT_FOUND;
}


Edge* minNode(Edge * node) {
    Edge * min = node;
    while(node != NULL) {
        if(min->weight > node->weight) min = node;
        node = node->next;
    }
    return min;
}

Edge* isFound(Edge * edge, int dst) {
    Edge * found = NULL, *temp = edge;
    while(edge != NULL) {
        if(edge->dst->node.number == dst) {
            found = edge;
            edge = temp;
            break;
        }
        edge = edge->next;
    }
    return found;
}

void TSP(Graph *head, char * choice) {
    *choice = fgetc(stdin);
    char space = fgetc(stdin);
    int len = *choice - '0', nodes[len], **permutation, paths[fact(len)], min = INFINITY, count = 0;
    Graph * headTemp = head;

    for(int i = 0; i < len; i++) {
        nodes[i] = fgetc(stdin) - '0';
        space = fgetc(stdin);
        if(space == END) {
            *choice = space;
        }
    }

    permutation = (int**)malloc(fact(len) * sizeof(int*));
    for(int i = 0; i < fact(len); i++) {
        for(int j = 0; j < len; j++) permutation[i] = (int*)malloc(len*sizeof(int));
    }
    permutation = permute(permutation, nodes, 0, len - 1, &count);

    for(int i = 0; i < fact(len); i++) {
        int src = 0, dst = 1;
        paths[i] = 0;
        while(dst < len) {
            int path = shortestPath(head, permutation[i][src] + '0', permutation[i][dst] + '0');
            if(path == NOT_FOUND || path == 0) {
                    paths[i] = INFINITY;
                    break;
                }
            else paths[i] += path;
            src++;
            dst++;
        }
    }
    
    for(int i = 0; i < fact(len); i++) {
        if(paths[i] < min) min = paths[i];
    }

    if(min >= INFINITY) min = NOT_FOUND;
    printf("TSP shortest path: %d ", min);
    head = headTemp;
    for (int i = 0; i < fact(len); i++) {
        int* p = permutation[i];
        free(p);
    }
    if(*choice == END || *choice == CHAR_NULL) return;
    else if( space == END || space == CHAR_NULL) return;
    *choice = fgetc(stdin);
    space = fgetc(stdin);
}

int fact(int num) {
    int fact = 1;
    for(int i = 1; i <= num; i++) fact*=i;
    return fact;
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int** permute(int ** result, int *arr, int l, int r, int *count) {
    if (l == r) {
        for (int i = 0; i <= r; i++) {
            result[*count][i] = arr[i];
        }
        (*count)++;
    } else {
        for (int i = l; i <= r; i++) {
            swap(&arr[l], &arr[i]);
            result = permute(result, arr, l + 1, r, count);
            swap(&arr[l], &arr[i]);
        }
    }
    return result;
}