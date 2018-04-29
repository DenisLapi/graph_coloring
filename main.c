#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num_of_nodes = 0;
    int *graph_matrix;

    /// Get how much number we will have in our graph
    printf("Enter the number of nodes: ");
    scanf("%d", &num_of_nodes);

    /// Allocate the memory for graph matrix with N rows and N columns
    graph_matrix = (int*)calloc(num_of_nodes * num_of_nodes, sizeof(int));



    return 0;
}
