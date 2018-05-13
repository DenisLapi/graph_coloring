#ifndef WELSH_POWELL_H
#define WELSH_POWELL_H

int graph_min_colors_welsh_powell(int *graph_matrix, int num_of_nodes, struct node_struct *nodes);
int get_node_color(int node_id, struct node_struct *nodes, int num_of_nodes);

#endif