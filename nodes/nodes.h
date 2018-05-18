#ifndef NODES_MODULE_H
#define NODES_MODULE_H

void show_nodes_data(struct node_struct *nodes, int num_of_nodes);
void create_nodes(struct node_struct *nodes, int num_of_nodes, int *graph_matrix);
void sort_nodes(struct node_struct *nodes, int num_of_nodes);

#endif