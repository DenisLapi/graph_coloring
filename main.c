#include <stdio.h>
#include <stdlib.h>

/// Functions declarations
void algorithm_menu(int *graph_matrix, int num_of_nodes);
void create_graph(int *graph_matrix, int num_of_nodes);
void show_graph_matrix(int *graph_matrix, int num_of_nodes);
int graph_min_colors_backtracing(int *graph_matrix, int num_of_nodes);

/// Node detail structure
struct node_struct {
    int id;
    int sum_connection;
    int color;
};

int main()
{
    int iterator;
    int iterator_col;
    int iterator_1;
    int iterator_2;
    int num_of_nodes = 0;
    int cell_value;
    int aux_sum_connection;
    int aux_color;
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

    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        node_detail[iterator].id = iterator;
        node_detail[iterator].color = 0;
        node_detail[iterator].sum_connection = 0;
        for(iterator_col = 0; iterator_col < num_of_nodes; iterator_col++) {
            cell_value = *graph_matrix_init;
            if(cell_value != 0) {
                node_detail[iterator].sum_connection++;
            }
            graph_matrix_init++;
        }
    }

    printf("\nID\tColor\tSum of connections");
    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        printf("\n%d\t%d\t\%d",node_detail[iterator].id, node_detail[iterator].color, node_detail[iterator].sum_connection);
    }

    /// Sort the nodes in descending order by number of connections per node
    for(iterator_1 = 0; iterator_1 < num_of_nodes; iterator_1++) {
        for(iterator_2 = iterator_1 + 1; iterator_2 < num_of_nodes; iterator_2++) {
            if(node_detail[iterator_1].sum_connection < node_detail[iterator_2].sum_connection) {

                aux_color = node_detail[iterator_1].color;
                aux_sum_connection = node_detail[iterator_1].sum_connection;

                node_detail[iterator_1].color = node_detail[iterator_2].color;
                node_detail[iterator_1].sum_connection = node_detail[iterator_2].sum_connection;

                node_detail[iterator_2].color = aux_color;
                node_detail[iterator_2].sum_connection = aux_sum_connection;
            }
        }
    }

    printf("\nModified:\n");
    printf("\nID\tColor\tSum of connections");
    for(iterator = 0; iterator < num_of_nodes; iterator++) {
        printf("\n%d\t%d\t\%d",node_detail[iterator].id, node_detail[iterator].color, node_detail[iterator].sum_connection);
    }

    /// Show the menu to select the algorithm
    algorithm_menu(graph_matrix, num_of_nodes);

    return 0;
}

void create_graph(int *graph_matrix, int num_of_nodes) {

    int row;
    int col;
    int *graph_matrix_init = graph_matrix;

    printf("\n\nPress number: \n\n1 - Connected nodes\n0 - Not connected nodes\n\n");

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

    printf("\n\n|----------- Graph Matrix -----------|\n\n");
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

void algorithm_menu(int *graph_matrix, int num_of_nodes) {

    int min_colors = 0;
    int menu_decision = 0;

    printf("\nSelect the algorithm for solving graph coloring problem :\n1) - Backtracing\n2) - Welsh-Powell\n\nEnter algorithm number: ");
    scanf("%d", &menu_decision);

    switch(menu_decision) {
        case 1:

            printf("You selected the Backtracing algorithm");
            min_colors = graph_min_colors_backtracing(graph_matrix, num_of_nodes);
            printf("\n\nWe need minimum %d colors to color the graph", min_colors);
            break;
        case 2:
            printf("\n\n[WARNING] Algorithm is not implemented yet");
            break;
        default:
            printf("\n\n[ERROR] Option doesn't exist");
    }
}
