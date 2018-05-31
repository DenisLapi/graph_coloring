#include <stdio.h>
#include "show_graph.h"

/*!
*  \fn void show_graph_matrix(int *graph_matrix, int num_of_nodes)
*  \brief This functions shows the graph matrix
*  \author Denis Lapadatovic
*  \param *graph_matrix Using this parameter we have the access to the graph matrix.
*  <b>*graph_matrix</b> is initialize out of this function.
*  \param num_of_nodes This variable will be provided in to the functions for resolving graph problem.
*  <b>num_of_nodes</b> is initialize out of this function.
*  \return Nothing
*/
void show_graph_matrix(int *graph_matrix, int num_of_nodes) {

    /// Iterator through the rows
    int row;
    /// Iterator through the columns
    int col;
    /// Copy of <b>graph_matrix</b>
    int *graph_matrix_init = graph_matrix;

    printf("\n|------ Graph Matrix ------|\n\n");
    for(row = 0; row < num_of_nodes; row++) {
        for(col = 0; col < num_of_nodes; col++) {
            /// Show the value of the graph matrix cell
            printf("%d ", *graph_matrix_init);
            // Increase the position of the graph matrix pointer
            graph_matrix_init++;
        }
        printf("\n");
    }
    printf("\n|--------------------------|\n\n");
}
