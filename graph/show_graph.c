#include <stdio.h>
#include "show_graph.h"


void show_graph_matrix(int *graph_matrix, int num_of_nodes) {

    int row;
    int col;
    int *graph_matrix_init = graph_matrix;

    printf("\n|----------- Graph Matrix -----------|\n\n");
    for(row = 0; row < num_of_nodes; row++) {
        for(col = 0; col < num_of_nodes; col++) {
            printf("%d ", *graph_matrix_init);
            graph_matrix_init++;
        }
        printf("\n");
    }
    printf("\n|------------------------------------|\n\n");
}