#include <stdio.h>
#include "./node_structure.h"
#include "nodes.h"

void show_nodes_data(struct node_struct *nodes, int num_of_nodes) {

    int iterator;
    
    printf("\nNode ID\tColor\tNumber of connections");

    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        printf("\n%d\t%d\t\%d",nodes->id, nodes->color, nodes->sum_connection);
        nodes++;
    }
}

void create_nodes(struct node_struct *nodes, int num_of_nodes, int *graph_matrix) {

	int iterator_1;
	int iterator_2;
	int *graph_matrix_init = graph_matrix;

	for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        nodes[iterator_1].id = iterator_1;
        nodes[iterator_1].color = -1;
        nodes[iterator_1].sum_connection = 0;
        for(iterator_2 = 0; iterator_2 < num_of_nodes; iterator_2++) {
            if(*graph_matrix_init != 0) {
                nodes[iterator_1].sum_connection++;
            }
            graph_matrix_init++;
        }
    }
}

void sort_nodes(struct node_struct *nodes, int num_of_nodes) {

	int iterator_1;
    int iterator_2;
    int aux_sum_connection;
    int aux_color;
    int aux_id;

    for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        for(iterator_2 = iterator_1 + 1; iterator_2 < num_of_nodes; iterator_2++) {
            if(nodes[iterator_1].sum_connection < nodes[iterator_2].sum_connection) {

                aux_id = nodes[iterator_1].id;
                aux_color = nodes[iterator_1].color;
                aux_sum_connection = nodes[iterator_1].sum_connection;

                nodes[iterator_1].id = nodes[iterator_2].id;
                nodes[iterator_1].color = nodes[iterator_2].color;
                nodes[iterator_1].sum_connection = nodes[iterator_2].sum_connection;

                nodes[iterator_2].id = aux_id;
                nodes[iterator_2].color = aux_color;
                nodes[iterator_2].sum_connection = aux_sum_connection;
            }
        }
    }
}

