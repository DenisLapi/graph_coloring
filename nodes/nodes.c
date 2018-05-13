#include <stdio.h>
#include "nodes.h"


void show_nodes_data(struct node_struct *nodes, int num_of_nodes) {
    int iterator;
    printf("\nID\tColor\tSum of connections");
    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        printf("\n%d\t%d\t\%d",nodes->id, nodes->color, nodes->sum_connection);
        nodes++;
    }
}

