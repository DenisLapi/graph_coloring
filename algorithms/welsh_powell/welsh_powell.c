#include <stdio.h>
#include "./../../nodes/node_structure.h"
#include "./welsh_powell.h"

int graph_min_colors_welsh_powell(int *graph_matrix, int num_of_nodes, struct node_struct *nodes) {

    int i;
    int can_color = 1;
    int col_iterator;
    int colored_nodes = 0; // Count the number of colored nodes. Increase when node is colored
    int min_colors = 0;    // Starting color is '1'
    int row_id;
    int cell_value;
    int node_color;
    int *graph_matrix_init = graph_matrix;

    while(colored_nodes < num_of_nodes) {
        min_colors++;
        /// Select the node from 0 - num_of nodes
        for(i = 0; i < num_of_nodes; i++) {
            /// If node doesn't have color set
            if(nodes[i].color <= 0) {
                /// Get the node ID (row number in the graph table)
                row_id = nodes[i].id;
                /// Go through the the row ID > columns
                for(col_iterator = 0; col_iterator < num_of_nodes; col_iterator++) {
                    /// Get the values from the column (row cell)
                    cell_value = *(graph_matrix_init + ((row_id * num_of_nodes) + col_iterator));
                    /// Check if nodes are conneted (row ID and column ID) : 0 - not connected; > 0 - connected
                    if(cell_value > 0) {
                        /// Nodes are connected get the color of the node that we compare
                        node_color = get_node_color(col_iterator, nodes, num_of_nodes);
                        /// Chech if color of the neighbor node is the same as current 'min_colors'
                        if(node_color == min_colors) {
                            can_color = 0;
                        }
                    }
                }
                if(can_color == 1) {
                    nodes[i].color = min_colors;
                    colored_nodes++;
                }
                can_color = 1;
                graph_matrix_init = graph_matrix;
            }
        }
    }
    return min_colors;
}

int get_node_color(int node_id, struct node_struct *nodes, int num_of_nodes) {

    int color = -1;
    int iterator;

    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        if(nodes[iterator].id == node_id) {
            color = nodes[iterator].color;
            break;
        }
    }

    return color;
}
