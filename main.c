#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// Node detail structure
struct node_struct {
    int id;
    int sum_connection;
    int color;
};

/// Functions declarations
void algorithm_menu(int *graph_matrix, int num_of_nodes, struct node_struct *nodes);
void create_graph(int *graph_matrix, int num_of_nodes);
void show_graph_matrix(int *graph_matrix, int num_of_nodes);
void show_nodes_data(struct node_struct *nodes, int num_of_nodes);
int graph_min_colors_backtracing(int *graph_matrix, int num_of_nodes);
int graph_min_colors_welsh_powell(int *graph_matrix, int num_of_nodes, struct node_struct *nodes);
int get_node_color(int node_id, struct node_struct *nodes, int num_of_nodes);

int main()
{
    int iterator_1;
    int iterator_2;
    int num_of_nodes = 0;
    int aux_sum_connection;
    int aux_color;
    int aux_id;
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
    graph_matrix_init = graph_matrix;

    for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        node_detail[iterator_1].id = iterator_1;
        node_detail[iterator_1].color = -1;
        node_detail[iterator_1].sum_connection = 0;
        for(iterator_2 = 0; iterator_2 < num_of_nodes; iterator_2++) {
            if(*graph_matrix_init != 0) {
                node_detail[iterator_1].sum_connection++;
            }
            graph_matrix_init++;
        }
    }

    /// Show nodes before sort
    show_nodes_data(&node_detail[0], num_of_nodes);

    /// Sort the nodes in descending order by number of connections per node
    for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        for(iterator_2 = iterator_1 + 1; iterator_2 < num_of_nodes; iterator_2++) {
            if(node_detail[iterator_1].sum_connection < node_detail[iterator_2].sum_connection) {

                aux_id = node_detail[iterator_1].id;
                aux_color = node_detail[iterator_1].color;
                aux_sum_connection = node_detail[iterator_1].sum_connection;

                node_detail[iterator_1].id = node_detail[iterator_2].id;
                node_detail[iterator_1].color = node_detail[iterator_2].color;
                node_detail[iterator_1].sum_connection = node_detail[iterator_2].sum_connection;

                node_detail[iterator_2].id = aux_id;
                node_detail[iterator_2].color = aux_color;
                node_detail[iterator_2].sum_connection = aux_sum_connection;
            }
        }
    }

    /// Show nodes after sort
    printf("\n\nNodes sorted in descening order:\n");
    show_nodes_data(&node_detail[0], num_of_nodes);

    /// Show the menu to select the algorithm
    algorithm_menu(graph_matrix, num_of_nodes, &node_detail[0]);

    return 0;
}

void create_graph(int *graph_matrix, int num_of_nodes) {

    int row;
    int col;
    int *graph_matrix_init = graph_matrix;

    printf("\nPress number: \n\n1 - Connected nodes\n0 - Not connected nodes\n\n");

    for(row = 0; row < num_of_nodes; row++) {
        for(col = 0; col < num_of_nodes; col++) {
            int is_connected;
            printf("Is node %d connected with node %d: ", row, col);
            scanf("%d", &is_connected);
            *graph_matrix_init = is_connected;
            graph_matrix_init++;
        }
    }
}

void show_graph_matrix(int *graph_matrix, int num_of_nodes) {

    int row;
    int col;
    int *graph_matrix_init = graph_matrix;

    printf("\n|----------- Graph Matrix -----------|\n\n");
    for(row = 0; row < num_of_nodes; row++) {
        for(col = 0; col < num_of_nodes; col++) {
            printf("%d ", *graph_matrix_init);
            graph_matrix_init++;
        }
        printf("\n");
    }
    printf("\n|------------------------------------|\n\n");
}


int graph_min_colors_backtracing(int *graph_matrix, int num_of_nodes) {

    /// Function returns the minimum number of colors used to color the graph
    int node_row;
    int col;
    int col_value;
    int node_color[num_of_nodes];
    int min_colors;
    int start_color;
    int *graph_matrix_init = graph_matrix;

    /// Set the color of the first node to be '1'
    //  NOTE: We can set any color to this node because its the first one who will be colored
    node_color[0] = 1;

    /// Set min_colors to be equal '1'
    //  NOTE: Because of the first node we know that we will use minimum one color
    min_colors = 1;

    /// Increase pointer start + number of nodes (columns)
    //  NOTE: We will skip the first row, so we need to increase the starting pointer
    graph_matrix_init += num_of_nodes;

    /// Start with searching and creating colors
    for(node_row = 1; node_row < num_of_nodes; node_row++) {

        start_color = 1;
        node_color[node_row] = start_color;

        for(col = 0; col < num_of_nodes; col++) {

            if(node_row != col) {

                col_value = *graph_matrix_init;

                if(col_value != 0) {
                    if(node_color[node_row] == node_color[col]) {
                        start_color++;
                        node_color[node_row] = start_color;
                        if(start_color > min_colors) {
                            min_colors = start_color;
                        }
                    }
                }
            }
            graph_matrix_init++;
        }

    }
    return min_colors;
}

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
            printf("\n");
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
                if(can_color == 1) {
                    nodes[i].color = min_colors;
                    colored_nodes++;
                }
                can_color = 1;
                graph_matrix_init = graph_matrix;
            }
        }
        //waitFor(20);
    }
    return min_colors;
}

int get_node_color(int node_id, struct node_struct *nodes, int num_of_nodes) {

    int color = -1;
    int iterator;

    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        if(nodes[iterator].id == node_id) {
            color = nodes[iterator].color;
            break;
        }
    }

    return color;
}

void algorithm_menu(int *graph_matrix, int num_of_nodes, struct node_struct *nodes) {

    int min_colors = 0;
    int menu_decision = 0;

    printf("\nSelect the algorithm for solving graph coloring problem :\n1) - Backtracing\n2) - Welsh-Powell\n\nEnter algorithm number: ");
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

void show_nodes_data(struct node_struct *nodes, int num_of_nodes) {
    int iterator;
    printf("\nID\tColor\tSum of connections");
    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        printf("\n%d\t%d\t\%d",nodes->id, nodes->color, nodes->sum_connection);
        nodes++;
    }
}

void waitFor(unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
