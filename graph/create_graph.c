#include <stdio.h>
#include <stdlib.h>
#include "create_graph.h"

int *create_graph(int *graph_matrix, int *num_of_nodes) {

    int row;
    int col;
    int new_size = (*num_of_nodes) * (*num_of_nodes);
    int *graph_matrix_init;
    int *new_graph_matrix = (int*)realloc(graph_matrix, new_size * sizeof(int));

    graph_matrix = new_graph_matrix;
    graph_matrix_init = graph_matrix;

    printf("\nPress number: \n\n1 - Connected nodes\n0 - Not connected nodes\n\n");

    for(row = 0; row < (*num_of_nodes); row++) {
        for(col = 0; col < (*num_of_nodes); col++) {
            int is_connected;
            printf("Is node %d connected with node %d: ", row, col);
            scanf("%d", &is_connected);
            *graph_matrix_init = is_connected;
            graph_matrix_init++;
        }
    }
    return new_graph_matrix;
}