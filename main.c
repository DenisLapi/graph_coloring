#include <stdio.h>
#include <stdlib.h>

// Loading modules
#include "nodes/node_structure.h"
#include "nodes/nodes.h"

#include "algorithms/backtracking/backtracking.h"
#include "algorithms/welsh_powell/welsh_powell.h"

#include "graph/create_graph.h"
#include "graph/show_graph.h"
#include "graph/load_graph.h"

void algorithm_menu(int *graph_matrix, int num_of_nodes);

int main()
{
    int num_of_nodes = 1;
    int *graph_matrix;
    int menu_option;
    int is_env_selected = 0;

    /// Allocate the memory for graph matrix with N rows and N columns
    graph_matrix = (int*) calloc(num_of_nodes * num_of_nodes, sizeof(int));

    /// Let user to decide which environment wants to run
    //  TEST   - Load dummy data from files located in the folder 'data'
    //  CUSTOM - Create own graph 

    printf("\nWhich environment you want to run: \n\n 1) - Test\n 2) - Custom\n\nEnter the number of environment: ");
    scanf("%d", &menu_option);

    /// Environment menu

    if(menu_option == 1) {

        printf("\nYou chose the 'TEST' environment");
        graph_matrix = load_graph(graph_matrix, &num_of_nodes);
        is_env_selected = 1; 

    } else if(menu_option == 2) {

        printf("\nYou chose the 'CUSTOM' environment");   
        printf("\n\nEnter the number of nodes: ");
        scanf("%d", &num_of_nodes);
        /// Call the function to create the graph (graph matrix need to be created every time)
        graph_matrix = create_graph(graph_matrix, &num_of_nodes);
        is_env_selected = 1;

    } else {

        printf("\nYou chose the invalid environment");

    }

    if(is_env_selected) {

        /// Show the graph_matrix;
        show_graph_matrix(graph_matrix, num_of_nodes);
        /// Show the menu to select the algorithm
        algorithm_menu(graph_matrix, num_of_nodes);

    }

    /// At the end of the program remove the 'graph matrix' pointer from the memory
    free(graph_matrix);

    return 0;
}


void algorithm_menu(int *graph_matrix, int num_of_nodes) {

    int min_colors = 0;
    int menu_decision = 0;

    printf("\n\nSelect the algorithm for solving graph coloring problem :\n1) - Backtracing\n2) - Welsh-Powell\n\nEnter algorithm number: ");
    scanf("%d", &menu_decision);


    if(menu_decision == 1) {
        
        printf("\nYou selected the Backtracing algorithm");
        min_colors = graph_min_colors_backtracing(graph_matrix, num_of_nodes);
        printf("\n\nWe need minimum %d colors to color the graph", min_colors);
    
    } else if(menu_decision == 2) {

        printf("\nYou selected the Welsh-Powell algorithm\n");

        /// Create all nodes data with 3 properties (needed for 'Welsh-Powell' algorithm )
        struct node_struct node_detail[num_of_nodes];

        create_nodes(&node_detail[0], num_of_nodes, graph_matrix);
        
        /// Show nodes before sort
        printf("\n\nNodes created for the graph:\n");
        show_nodes_data(&node_detail[0], num_of_nodes);

        /// Sort the nodes in descending order by number of connections per node
        sort_nodes(&node_detail[0], num_of_nodes);

        /// Show nodes after sort
        printf("\n\nNodes sorted in descending order:\n");
        show_nodes_data(&node_detail[0], num_of_nodes);

        min_colors = graph_min_colors_welsh_powell(graph_matrix, num_of_nodes, &node_detail[0]);
        printf("\n\nWe need minimum %d colors to color the graph", min_colors);   

        /// Show nodes after sort
        printf("\n\nNodes after coloring:\n");
        show_nodes_data(&node_detail[0], num_of_nodes);

    } else {

        printf("\n\n[ERROR] Option doesn't exist. Try again! \n");
        algorithm_menu(graph_matrix, num_of_nodes);

    }
}