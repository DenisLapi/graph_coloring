#include <stdio.h>
#include <stdlib.h>

// Loading modules
#include "nodes/node_structure.h"
#include "nodes/nodes.h"

#include "algorithms/backtracking/backtracking.h"
#include "algorithms/welsh_powell/welsh_powell.h"

#include "graph/create_graph.h"
#include "graph/show_graph.h"

/// Functions declarations
void algorithm_menu(int *graph_matrix, int num_of_nodes, struct node_struct *nodes);

int main()
{
    int iterator_1;
    int iterator_2;
    int num_of_nodes = 0;
    int aux_sum_connection;
    int aux_color;
    int aux_id;
    int *graph_matrix;
    int *graph_matrix_init;

    /// Get how much number we will have in our graph
    printf("Enter the number of nodes: ");
    scanf("%d", &num_of_nodes);

    /// Allocate the memory for graph matrix with N rows and N columns
    graph_matrix = (int*)calloc(num_of_nodes * num_of_nodes, sizeof(int));

    /// Call the function to create the graph
    create_graph(graph_matrix, num_of_nodes);

    /// Show the graph_matrix;
    show_graph_matrix(graph_matrix, num_of_nodes);

    /// Create all nodes data with 3 properties
    struct node_struct node_detail[num_of_nodes];
    graph_matrix_init = graph_matrix;

    for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        node_detail[iterator_1].id = iterator_1;
        node_detail[iterator_1].color = -1;
        node_detail[iterator_1].sum_connection = 0;
        for(iterator_2 = 0; iterator_2 < num_of_nodes; iterator_2++) {
            if(*graph_matrix_init != 0) {
                node_detail[iterator_1].sum_connection++;
            }
            graph_matrix_init++;
        }
    }

    /// Show nodes before sort
    show_nodes_data(&node_detail[0], num_of_nodes);

    /// Sort the nodes in descending order by number of connections per node
    for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        for(iterator_2 = iterator_1 + 1; iterator_2 < num_of_nodes; iterator_2++) {
            if(node_detail[iterator_1].sum_connection < node_detail[iterator_2].sum_connection) {

                aux_id = node_detail[iterator_1].id;
                aux_color = node_detail[iterator_1].color;
                aux_sum_connection = node_detail[iterator_1].sum_connection;

                node_detail[iterator_1].id = node_detail[iterator_2].id;
                node_detail[iterator_1].color = node_detail[iterator_2].color;
                node_detail[iterator_1].sum_connection = node_detail[iterator_2].sum_connection;

                node_detail[iterator_2].id = aux_id;
                node_detail[iterator_2].color = aux_color;
                node_detail[iterator_2].sum_connection = aux_sum_connection;
            }
        }
    }

    /// Show nodes after sort
    printf("\n\nNodes sorted in descening order:\n");
    show_nodes_data(&node_detail[0], num_of_nodes);

    /// Show the menu to select the algorithm
    algorithm_menu(graph_matrix, num_of_nodes, &node_detail[0]);

    return 0;
}

void algorithm_menu(int *graph_matrix, int num_of_nodes, struct node_struct *nodes) {

    int min_colors = 0;
    int menu_decision = 0;

    printf("\nSelect the algorithm for solving graph coloring problem :\n1) - Backtracing\n2) - Welsh-Powell\n\nEnter algorithm number: ");
    scanf("%d", &menu_decision);

    switch(menu_decision) {
        case 1:
            printf("\nYou selected the Backtracing algorithm");
            min_colors = graph_min_colors_backtracing(graph_matrix, num_of_nodes);
            printf("\n\nWe need minimum %d colors to color the graph", min_colors);
            break;
        case 2:
            printf("\nYou selected the Welsh-Powell algorithm");
            //printf("\n\n[WARNING] Algorithm is not implemented yet");
            min_colors = graph_min_colors_welsh_powell(graph_matrix, num_of_nodes, nodes);
            printf("\n\nWe need minimum %d colors to color the graph", min_colors);
            break;
        default:
            printf("\n\n[ERROR] Option doesn't exist");
    }
}
