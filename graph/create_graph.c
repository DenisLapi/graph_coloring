#include <stdio.h>
#include <stdlib.h>
#include "create_graph.h"

/*!
*  \fn int *create_graph(int *graph_matrix, int *num_of_nodes)
*  \brief This functions create the graph matrix. User enter the data for the graph. This funtion is used in <b>Custom</b> environment
*  \author Denis Lapadatovic
*  \param *graph_matrix Using this parameter we have the access to the graph matrix.
*  <b>*graph_matrix</b> is initialize out of this function.
*  \param num_of_nodes This parameter will be used to add the number of nodes.
*  <b>*num_of_nodes</b> is initialize in this function.
*  \return new_graph_matrix - Pointer to the new created graph matrix
*/
int *create_graph(int *graph_matrix, int *num_of_nodes) {

    int row;
    int col;
    /// Calculate the graph matrix size
    int new_size = (*num_of_nodes) * (*num_of_nodes);
    int *graph_matrix_init;
    /// Realloc the size of graph matrix
    int *new_graph_matrix = (int*) realloc(graph_matrix, new_size * sizeof(int));

    /// Create the helper variables
    graph_matrix = new_graph_matrix;
    graph_matrix_init = graph_matrix;

    printf("\nPress number: \n\n1 - Connected nodes\n0 - Not connected nodes\n\n");

    /// Iterate through the graph matrix row
    for(row = 0; row < (*num_of_nodes); row++) {
        /// Iterate through the graph matrix column
        for(col = 0; col < (*num_of_nodes); col++) {
            /// Ask user to enter if node is conneted with another node
            int is_connected;
            printf("Is node %d connected with node %d: ", row, col);
            scanf("%d", &is_connected);
            /// Save the value in the graph matrix
            *graph_matrix_init = is_connected;
            /// Increase the position of graph matrix pointer
            graph_matrix_init++;
        }
    }
    /// Return the pointer of the graph matrix.
    /// \warning Realloc() returns the pointer to the beginning of newly allocated memory.
    return new_graph_matrix;
}
