#include <stdio.h>
#include "./backtracking.h"

int graph_min_colors_backtracing(int *graph_matrix, int num_of_nodes) {

    /// Function returns the minimum number of colors used to color the graph
    int node_row;
    int col;
    int col_value;
    int node_color[num_of_nodes];
    int min_colors;
    int start_color;
    int *graph_matrix_init = graph_matrix;

    /// Set the color of the first node to be '1'
    //  NOTE: We can set any color to this node because its the first one who will be colored
    node_color[0] = 1;

    /// Set min_colors to be equal '1'
    //  NOTE: Because of the first node we know that we will use minimum one color
    min_colors = 1;

    /// Increase pointer start + number of nodes (columns)
    //  NOTE: We will skip the first row, so we need to increase the starting pointer
    graph_matrix_init += num_of_nodes;

    /// Start with searching and creating colors
    for(node_row = 1; node_row < num_of_nodes; node_row++) {

        start_color = 1;
        node_color[node_row] = start_color;

        for(col = 0; col < num_of_nodes; col++) {

            if(node_row != col) {

                col_value = *graph_matrix_init;

                if(col_value != 0) {
                    if(node_color[node_row] == node_color[col]) {
                        start_color++;
                        node_color[node_row] = start_color;
                        if(start_color > min_colors) {
                            min_colors = start_color;
                        }
                    }
                }
            }
            graph_matrix_init++;
        }

    }
    return min_colors;
}
