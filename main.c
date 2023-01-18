#include "algo.h"

int main () {
    char choice = fgetc(stdin), u = fgetc(stdin), v;
    Graph * head = NULL, *temp = NULL;
    while(choice != END && choice != CHAR_NULL) {
        switch (choice) {
            case NEW_GRAPH:
                if(head != NULL) head = deleteGraph(&head);
                head = (Graph*)malloc(sizeof(Graph));
                temp = head;
                build_graph(head, &choice);
                break;
            case NEW_NODE:
                head = new_node(&head, &choice);
                temp = head;
                break;
            case DELETE_NODE:
                temp = deleteNode(head, &choice);
                break;
            case SHORTEST_PATH:
                u = fgetc(stdin); //src
                char space = fgetc(stdin);
                v = fgetc(stdin); //dst
                space = fgetc(stdin);

                printf("Dijsktra shortest path: %d\n", shortestPath(head, u, v));
                if(space == END || space == CHAR_NULL) {
                    choice = space;
                    break;
                }
                choice = fgetc(stdin);
                if(choice == END || choice == CHAR_NULL) break;
                space = fgetc(stdin);
                break;
            case SHORTEST_PATH_NODE:
                TSP(head, &choice);
                break;
            default:
                break;
        }
        head = temp;
    }
    head = deleteGraph(&head);
    return 0;
}