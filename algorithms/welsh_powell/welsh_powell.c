#include <stdio.h>
#include "./../../nodes/node_structure.h"
#include "./welsh_powell.h"


/*!
*  \fn int graph_min_colors_welsh_powell(int *graph_matrix, int num_of_nodes, struct node_struct *nodes)
*  \brief This functions resolve the <i><b>Chromatic number</b></i> - graph coloring problem using the <i><b>Welsh Powell</b></i> algorithm
*  \author Denis Lapadatovic
*  \param *graph_matrix Using this parameter we have the access to the graph matrix. <b>*graph_matrix</b> is initialize out of this function.
*  \param num_of_nodes This parameter will be used to add the number of nodes. <b>*num_of_nodes</b> is initialize in this function.
*  \param *nodes This variable is used for the iteration through the nodes with properties
*  \return min_colors - Minimum number of colors for coloring graph nodes determined by the algorithm
*/
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
                /// If node can be colored with min color set the color
                if(can_color == 1) {
                    nodes[i].color = min_colors;
                    colored_nodes++;
                }
                can_color = 1;
                graph_matrix_init = graph_matrix;
            }
        }
    }
    /// Return minumum number of colors when algorithm is finished
    return min_colors;
}

/*!
*  \fn int get_node_color(int node_id, struct node_struct *nodes, int num_of_nodes)
*  \brief This function return the value of the color for the node
*  \author Denis Lapadatovic
*  \param node_id Input variable used to identify the ID of the node we want to get the color
*  \param *nodes This variable is used for the iteration through the nodes with properties
*  \param num_of_nodes This parameter will be used to add the number of nodes. <b>*num_of_nodes</b> is initialize in this function.
*  \return color Return the color of the node with ID passed in the function
*/
int get_node_color(int node_id, struct node_struct *nodes, int num_of_nodes) {

    /// Default value for color
    int color = -1;
    int iterator;

    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        if(nodes[iterator].id == node_id) {
            color = nodes[iterator].color;
            break;
        }
    }
    /// Return the color of the node
    return color;
}
