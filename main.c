#include <stdio.h>
#include <stdlib.h>

// Loading modules
#include "nodes/node_structure.h"
#include "nodes/nodes.h"

#include "algorithms/backtracking/backtracking.h"
#include "algorithms/welsh_powell/welsh_powell.h"

#include "graph/create_graph.h"
#include "graph/show_graph.h"

/// Functions declarations
void algorithm_menu(int *graph_matrix, int num_of_nodes, struct node_struct *nodes);

int main()
{
    int num_of_nodes;
    int *graph_matrix;
    int *graph_matrix_init;

    /// Get how much number we will have in our graph
    printf("Enter the number of nodes: ");
    scanf("%d", &num_of_nodes);

    /// Allocate the memory for graph matrix with N rows and N columns
    graph_matrix = (int*)calloc(num_of_nodes * num_of_nodes, sizeof(int));

    /// Call the function to create the graph
    create_graph(graph_matrix, num_of_nodes);

    /// Show the graph_matrix;
    show_graph_matrix(graph_matrix, num_of_nodes);

    /// Create all nodes data with 3 properties
    struct node_struct node_detail[num_of_nodes];

    create_nodes(&node_detail[0], num_of_nodes, graph_matrix);
    
    /// Show nodes before sort
    show_nodes_data(&node_detail[0], num_of_nodes);

    /// Sort the nodes in descending order by number of connections per node
    sort_nodes(&node_detail[0], num_of_nodes);

    /// Show nodes after sort
    printf("\n\nNodes sorted in descending order:\n");
    show_nodes_data(&node_detail[0], num_of_nodes);

    /// Show the menu to select the algorithm
    algorithm_menu(graph_matrix, num_of_nodes, &node_detail[0]);

    /// Show nodes after coloring
    printf("\n\nNodes after coloring\n");
    show_nodes_data(&node_detail[0], num_of_nodes);

    return 0;
}

void algorithm_menu(int *graph_matrix, int num_of_nodes, struct node_struct *nodes) {

    int min_colors = 0;
    int menu_decision = 0;

    printf("\n\nSelect the algorithm for solving graph coloring problem :\n1) - Backtracing\n2) - Welsh-Powell\n\nEnter algorithm number: ");
    scanf("%d", &menu_decision);

    switch(menu_decision) {
        case 1:
            printf("\nYou selected the Backtracing algorithm");
            min_colors = graph_min_colors_backtracing(graph_matrix, num_of_nodes);
            printf("\n\nWe need minimum %d colors to color the graph", min_colors);
            break;
        case 2:
            printf("\nYou selected the Welsh-Powell algorithm");
            //printf("\n\n[WARNING] Algorithm is not implemented yet");
            min_colors = graph_min_colors_welsh_powell(graph_matrix, num_of_nodes, nodes);
            printf("\n\nWe need minimum %d colors to color the graph", min_colors);
            break;
        default:
            printf("\n\n[ERROR] Option doesn't exist");
    }
}
