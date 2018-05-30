///\file node_structure.h
///\brief C library with node structure details

#ifndef NODES_STRUCTURE_H
#define NODES_STRUCTURE_H

/*!
* \brief This is the structure of nodes that we are creating for Welsh-Powell algorithms
* We are using this structure to compare the properties between nodes such as id, sum_connection, colors
* When we are resolving the graph coloring problem with Welsh-Powell algorithm, we are coloring
* nodes starting from the nodes with bigger number of connections.
*/
typedef struct node_struct {
    int id;  /**< ID the the unique for every node. We are using this value to select the row in the <b>graph matrix</b> \warning ID represend one row in the graph matrix */
    int sum_connection; /**< Sum of connections shows us how many nodes we are connected with. */
    int color;  /**< Shows us the node color represented as a number. \warning Default is <b>-1</b> before coloring. */
} node_struct;

#endif // NODES_STRUCTURE_H
