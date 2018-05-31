#include <stdio.h>
#include "./node_structure.h"
#include "nodes.h"

/*!
*  \fn void show_nodes_data(struct node_struct *nodes, int num_of_nodes)
*  \brief This function shows the details for the nodes in one list
*  \author Denis Lapadatovic
*  \param *nodes This variable is used for the iteration and showing the nodes with properties
*  \param num_of_nodes This variable will be provided in to the functions for resolving graph problem.
  <b>num_of_nodes</b> is initialize out of this function.
*  \return Nothing
*/
void show_nodes_data(struct node_struct *nodes, int num_of_nodes) {
    /// Helper variable used for iteration through the nodes
    int iterator;

    printf("\nNode ID\tColor\tNumber of connections");
    /// Iterate and show the nodes
    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        printf("\n%d\t%d\t\%d",nodes->id, nodes->color, nodes->sum_connection);
        /// Increase the position of the pointer
        nodes++;
    }
}

/*!
*  \fn void create_nodes(struct node_struct *nodes, int num_of_nodes, int *graph_matrix)
*  \brief This function initialize/create the nodes with default values
*  \author Denis Lapadatovic
*  \param *nodes This variable is used for the iteration and showing the nodes with properties
*  \param num_of_nodes This variable will be provided in to the functions for resolving graph problem.
*  <b>num_of_nodes</b> is initialize out of this function.
*  \param *graph_matrix Using this parameter we have the access to the graph matrix.
*  \return Nothing
*/
void create_nodes(struct node_struct *nodes, int num_of_nodes, int *graph_matrix) {

  /// Iterator_1 - Iterate through the nodes
	int iterator_1;
  /// Iterator_2 - Iterate through the rows and columns of the graph matrix
	int iterator_2;
  /// Copy of the 'graph_matrix'
	int *graph_matrix_init = graph_matrix;

  // Iterate through the all nodes
	for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        /// Set node <b>ID</b>
        nodes[iterator_1].id = iterator_1;
        /// Set node default color <b>-1</b> - not colored
        nodes[iterator_1].color = -1;
        /// Set the sum of connections to <b>0</b> - default
        nodes[iterator_1].sum_connection = 0;
        /// Iterate through the graph matrix and check for number of connections of the node
        for(iterator_2 = 0; iterator_2 < num_of_nodes; iterator_2++) {
            /// If matrix value is not 0 - means that nodes are connected
            if(*graph_matrix_init != 0) {
                /// Increase the number of connections
                nodes[iterator_1].sum_connection++;
            }
            // Increase the position of the graph_matrix_init pointer
            graph_matrix_init++;
        }
    }
}

/*!
*  \fn void sort_nodes(struct node_struct *nodes, int num_of_nodes)
*  \brief This function sort the nodes in descending order by sum of connections.
*  \author Denis Lapadatovic
*  \param *nodes This variable is used for the iteration and showing the nodes with properties
*  \param num_of_nodes This variable will be provided in to the functions for resolving graph problem.
*  <b>num_of_nodes</b> is initialize out of this function.
*  \param *graph_matrix Using this parameter we have the access to the graph matrix.
*  \return Nothing
*/
void sort_nodes(struct node_struct *nodes, int num_of_nodes) {

    /// Iterate through the all nodes
	  int iterator_1;
    /// Iterate through the all nodes to compare with selected node
    int iterator_2;
    /// Save the sum of connections for the node
    int aux_sum_connection;
    /// Save the color for the node
    int aux_color;
    /// Save ID for the node
    int aux_id;

    /// <b>SELECTED NODE</b>: Iterate through the node and compare with other nodes
    for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        /// Iteratete through the rest of nodes and compare with <b>SELECTED NODE</b>
        for(iterator_2 = iterator_1 + 1; iterator_2 < num_of_nodes; iterator_2++) {
            /// If number of connections of the <b>SELECTED NODE</b> is smaller then other node change the positions of the nodes
            if(nodes[iterator_1].sum_connection < nodes[iterator_2].sum_connection) {
                /// Save the values for the <b>SELECTED NODE</b> in aux variables
                aux_id = nodes[iterator_1].id;
                aux_color = nodes[iterator_1].color;
                aux_sum_connection = nodes[iterator_1].sum_connection;

                /// Replace the values of the first node with the second node
                nodes[iterator_1].id = nodes[iterator_2].id;
                nodes[iterator_1].color = nodes[iterator_2].color;
                nodes[iterator_1].sum_connection = nodes[iterator_2].sum_connection;

                /// Replace the values of the second node with aux variables
                nodes[iterator_2].id = aux_id;
                nodes[iterator_2].color = aux_color;
                nodes[iterator_2].sum_connection = aux_sum_connection;
            }
        }
    }
}
