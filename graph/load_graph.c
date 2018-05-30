#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./load_graph.h"

int *load_graph(int *graph_matrix, int *num_of_nodes) {

	// *graph_matrix - In this pointer we will add the data from our file
	// *num_of_nodes - In this pointer we will add the number of nodes from the file data, so this number can be accessible outside the function

	FILE *data;
	int new_size;
	int *new_graph_matrix;
	int *graph_matrix_init;
	char file_name[100];
	char data_file[100];
	char file_data[256];
	char temp;

	printf("\n\nWhich file (.txt) do you want to load from \"data\" folder:");
	printf("\nEnter the file name without extension: ");

	/*

		Solution for fixing the problem with the string with 'space'
		LINK: https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx

	*/

	scanf("%c",&temp); // temp statement to clear buffer
	scanf("%[^\n]",file_name);

	// Add path to variable
	strcpy(data_file, "./data/");

	// Add extension to the file_name
	strcat(file_name, ".txt");

	// Concat path folder with file name
	strcat(data_file, file_name);

	printf("\nData path: %s | File name: %s\n", data_file, file_name);

	// Open file with graph data
	data = fopen(data_file, "r");

	if (data) {

		// First string (number) in the file is represents the number of nodes
		fscanf(data, "%s", file_data);
		*num_of_nodes = atoi(file_data);

		// Calculate the size of new graph matrix
		new_size = (*num_of_nodes) * (*num_of_nodes);

		// Realloc the 'graph_matrix' variable and increase the size of it
		new_graph_matrix = (int*) realloc(graph_matrix, new_size * sizeof(int));

		// Initialite the primary graph matrix pointer with new created pointer
		graph_matrix = new_graph_matrix;

		// Crete the pointer for iteration
		graph_matrix_init = graph_matrix;

		// Go through the graph matrix from file and create the 'graph_matrix_init'
	    while( !feof(data) ) {

	    	// Get the value from file as a string
	    	fscanf(data, "%s", file_data);

	    	// Show matrix string as a number using 'atoi()'
	    	// printf("%d,", atoi(file_data));

	    	// Convert string value to integer and add to matrix
	    	*graph_matrix_init = atoi(file_data);

	    	// Increment the position of pointer
	    	graph_matrix_init++;

	    }

	    // Close the file when reading is finished
	    fclose(data);

	} else {

		printf("File doesn't exist");
		exit(0);

	}

	graph_matrix_init = graph_matrix;

	return graph_matrix;
}
