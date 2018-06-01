/*!
 * \author Denis Lapadatovic
 * \version v0.1
 * \date 2018-05-30
 * \file main.c
 * \bug No common bugs in this project. Contact us if you find any of them
 * \mainpage Chromatic number - Graph coloring problem
 * \section intro_section Introduction
 * This code was developed in education purpose as a project for the university.
 *
 * Using this code we tried to resolve the problem of coloring undirected graph nodes.
 *
 * More about the graph coloring problem you can find on Wikipedia: <a href="https://en.wikipedia.org/wiki/Graph_coloring" target="_blank">Graph coloring</a>
 *
 * \section compilation_section Compilation
 * To compile this project you will need to use the <b>make</b> command. Follow the steps to compile the project:
 *
 * - Steps to compile the project
 *  1. Open the terminal and navigate to the project directory
 *
 *  2. In the <b>root</b> of the project directory using the terminal run the command: \code{.c} make \endcode
 *     Files that need to be compiled are added in to the <b>Makefile</b> file.
 *     \warning You don't need to modify this file. Please pay attention if you do it.
 *
 * Compilation process will generate the executable file: <b>Application</b>
 *
 * \section run_program Run the program
 * \subsection run_with_term Run using the terminal
 * To start this program using the <b>terminal</b> run the following command in to the root of the project directory:
 *
 * <b>Linux</b>: \code{.c} ./Application \endcode
 * <b>Windows</b>: \code{.c} Application \endcode
 *
 * \subsection run_user_frendly Run without the terminal
 * To start the program in user-frendly manner, open the project directory and click on <b>Application</b>
 *
 * \section open_source Open source
 * This project is <i>open source</i>. You can check the full project code on this link: <a href="https://github.com/DenisLapi/graph_coloring">Github</a>
*/

#include <stdio.h>
#include <stdlib.h>

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
    /// Variable used to save the number of nodes of our graph
    int num_of_nodes = 1;
    /// Pointer to the graph matrix. In this pointer we will initialize the grapg matrix
    int *graph_matrix;
    /// Variable used for the menu selection. To choose between <b>Test</b> and <b>Custom</b> environment
    int menu_option;
    /// Check if program environment is selected. If <b>TRUE</b> continue the program
    int is_env_selected = 0;

    /// Allocate the memory for graph matrix with N rows and N columns
    graph_matrix = (int*) calloc(num_of_nodes * num_of_nodes, sizeof(int));

    /*!
    * Let user to decide which environment wants to run
    * Test   - Load dummy data from files located in the folder <b>data</b>
    * Custom - Create own graph
    */

    printf("\nWhich environment you want to run: \n\n 1) - Test\n 2) - Custom\n\nEnter the number of environment: ");
    scanf("%d", &menu_option);

    /// Environment menu
    if(menu_option == 1) {
        /// If user select the first environment <b>Test</b> run the code below
        printf("\nYou chose the 'TEST' environment");
        /// Save the return value from the <b>load_graph</b> function in <b>graph_matrix</b> pointer
        graph_matrix = load_graph(graph_matrix, &num_of_nodes);
        /// Set variable to <b>1</b> - means that environment is selected
        is_env_selected = 1;

    } else if(menu_option == 2) {
        /// If user select the second environment <b>Custom</b> run the code below
        printf("\nYou chose the 'CUSTOM' environment");
        printf("\n\nEnter the number of nodes: ");
        /// Let user enter the number of nodes for the graph and save it in <b>num_of_nodes</b> variable
        scanf("%d", &num_of_nodes);
        /*!
        *   Call the function to create the graph
        *   \warning Graph matrix need to be created for this environment using the <b>create_graph</b> function
        *
        *   Save the created graph in <b>graph_matrix</b> pointer
        */
        graph_matrix = create_graph(graph_matrix, &num_of_nodes);
        /// Set variable to <b>1</b> - means that environment is selected
        is_env_selected = 1;

    } else {
        /// If user select the other number for environment
        ///\warning Environment options are <b>1</b> for <b>TEST</b> <b>2</b> for <b>CUSTOM</b>
        printf("\nYou chose the invalid environment");

    }

    if(is_env_selected) {

        /// Show the graph_matrix
        show_graph_matrix(graph_matrix, num_of_nodes);
        /// Show the menu to select the algorithm
        algorithm_menu(graph_matrix, num_of_nodes);

    }

    /// At the end of the program remove the <b>graph matrix</b> pointer from the memory
    free(graph_matrix);

    return 0;
}

/*!
*  \brief This function will be used to give the posibility to the user to select the algorithm that he/she wants to use for resolving the graph coloring problem.
*  \author Denis Lapadatovic
*  \param *graph_matrix This pointer parameter will be provided in to the functions for resolving graph problem. <b>*graph_matrix</b> is initialize out of this function.
*  \param num_of_nodes This variable will be provided in to the functions for resolving graph problem. <b>num_of_nodes</b> is initialize out of this function.
*  \return Nothing
*/
void algorithm_menu(int *graph_matrix, int num_of_nodes) {

    /// In this variable we are storing the minimum number of colors needed to color the graph
    int min_colors = 0;
    /// In this variable we are storing the menu decision for the desired algorithm for resolving the problem
    int menu_decision = 0;

    printf("\n\nSelect the algorithm for solving graph coloring problem :\n1) - Backtracing\n2) - Welsh-Powell\n\nEnter algorithm number: ");
    /// Let user to enter the decision about the algorithm and save it in the variable
    scanf("%d", &menu_decision);

    /// Check the user algorithm option
    if(menu_decision == 1) {
        /// If user enter <b>1</b> resolve the problem using the <b>Backtracing</b> algorithm
        printf("\nYou selected the Backtracing algorithm");
        /// Run the function and save the final result in to the variable
        min_colors = graph_min_colors_backtracing(graph_matrix, num_of_nodes);
        printf("\n\nWe need minimum %d colors to color the graph", min_colors);

    } else if(menu_decision == 2) {
        /// If user enter <b>2</b> resolve the problem using the <b>Welsh-Powell</b> algorithm
        printf("\nYou selected the Welsh-Powell algorithm\n");

        /// Create all nodes data with 3 properties (needed for <b>Welsh-Powell</b> algorithm )
        struct node_struct node_detail[num_of_nodes];
        /// Run the function to initialize the nodes with ID, Sum of connections and Color
        create_nodes(&node_detail[0], num_of_nodes, graph_matrix);

        /// Show nodes before sort
        printf("\n\nNodes created for the graph:\n");
        show_nodes_data(&node_detail[0], num_of_nodes);

        /// Sort the nodes in descending order by number of connections per node
        sort_nodes(&node_detail[0], num_of_nodes);

        /// Show nodes after sort
        printf("\n\nNodes sorted in descending order:\n");
        show_nodes_data(&node_detail[0], num_of_nodes);

        /// Run the function and save the final result in to the variable
        min_colors = graph_min_colors_welsh_powell(graph_matrix, num_of_nodes, &node_detail[0]);
        printf("\n\nWe need minimum %d colors to color the graph", min_colors);

        /// Show nodes after sort
        printf("\n\nNodes after coloring:\n");
        show_nodes_data(&node_detail[0], num_of_nodes);

    } else {
      /// If user select the other number for algorithm
      ///\warning Algorithm options are <b>1</b> for <b>Backtracing</b> <b>2</b> for <b>Welsh-Powell</b>
        printf("\n\n[ERROR] Option doesn't exist. Try again! \n");
        algorithm_menu(graph_matrix, num_of_nodes);
    }
}
