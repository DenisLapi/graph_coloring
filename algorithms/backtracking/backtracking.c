#include <stdio.h>
#include "./backtracking.h"

/*!
*  \fn graph_min_colors_backtracing(int *graph_matrix, int num_of_nodes)
*  \brief This functions resolve the <i><b>Chromatic number</b></i> - graph coloring problem using the <i><b>Backtracking</b></i> algorithm
*  \author Denis Lapadatovic
*  \param *graph_matrix Using this parameter we have the access to the graph matrix.
*  <b>*graph_matrix</b> is initialize out of this function.
*  \param num_of_nodes This parameter will be used to add the number of nodes.
*  <b>*num_of_nodes</b> is initialize in this function.
*  \return min_colors - Minimum number of colors for coloring graph nodes determined by the algorithm
*/

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
    /// NOTE: We can set any color to this node because its the first one who will be colored
    node_color[0] = 1;

    /// Set min_colors to be equal '1'
    /// NOTE: Because of the first node we know that we will use minimum one color
    min_colors = 1;

    /// Increase pointer start + number of nodes (columns)
    /// NOTE: We will skip the first row, so we need to increase the starting pointer
    graph_matrix_init += num_of_nodes;

    /// Start with searching and creating colors
    for(node_row = 1; node_row < num_of_nodes; node_row++) {
        /// Set the first color to the node
        start_color = 1;
        node_color[node_row] = start_color;
        /// To through the graph matrix columns
        for(col = 0; col < num_of_nodes; col++) {
            /// We don't need to compare the same row and column
            if(node_row != col) {
                /// Get the column value from the graph matrix
                col_value = *graph_matrix_init;
                /// Check if value is not <b>0</b>
                /// \warning If value is 0 means that nodes are not conneted so we don't need to compare the colors
                if(col_value != 0) {
                    if(node_color[node_row] == node_color[col]) {
                        /// If colors are the same, increase the start color
                        start_color++;
                        /// Set the color to the node
                        node_color[node_row] = start_color;
                        if(start_color > min_colors) {
                            /// If start color is bigger then min colors means that we need more colors, so we need to increase the variable <b>min_colors</b>
                            min_colors = start_color;
                        }
                    }
                }
            }
            /// Increase the position of the pointer
            graph_matrix_init++;
        }

    }
    /// Return minumum number of colors when algorithm is finished
    return min_colors;
}
