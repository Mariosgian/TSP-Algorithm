// This is the algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 64 // Maximum number of cities that can be handled (64)
#define MAX_CITY_NAME_LEN 256 // Maximum length for city names (adjust as needed)

typedef struct city {
    char *name;                 // Pointer to dynamically allocated city name
} city;

int dist[MAX_CITIES][MAX_CITIES];   // Array to store distances between two cities
city cities[MAX_CITIES];            // Array to store the city names
int visited[MAX_CITIES];            // Array to track the visited cities
int tour[MAX_CITIES];               // Array to store the current order we visit the cities
int n;                              // Number of cities
long long min_cost = INT_MAX;       // Variable to store the minimum cost of the tour
int best_tour[MAX_CITIES];          // Array to store the best series with which we will visit the cities found
int current_tour[MAX_CITIES];       // Array to store the current tour being evaluated

// Declaration of the functions used in the program
void tsp(int pos, int cost, int count); // Finds the most efficient way to visit the cities with the minimum cost
int get_city_index(char *city_name, int *city_count); // Finds the index of a city or adds it if it doesn't exist

int main(int argc, char *argv[]) {
    if (argc != 2) { // Check if the correct number of arguments is provided
        fprintf(stderr, "Usage: ./jabbamaps <filename>\n");
        return 1;
    }
    const char *filename = argv[1];      // Get the filename from the arguments
    FILE *file = fopen(filename, "r");   // Open the file for reading
    if (file == NULL) {                  // Check if the file was opened successfully
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    int city_count = 0;                  // Initialize the variable that keeps count of the cities
    char city1[MAX_CITY_NAME_LEN], city2[MAX_CITY_NAME_LEN]; // Buffers to store city names from the file
    long long distance;                  // Variable to store the distance between cities

    while (fscanf(file, "%255[^-]-%255[^:]: %lld\n", city1, city2, &distance) == 3) { 
        // We read each line using fscanf and allow city names of arbitrary size
        int index1 = get_city_index(city1, &city_count);        // Get or add the index for the first city
        int index2 = get_city_index(city2, &city_count);        // Get or add the index for the second city
        if (index1 != -1 && index2 != -1) {         // Check if both cities were found or added successfully
            dist[index1][index2] = distance;        // Set the distance between the two cities
            dist[index2][index1] = distance;        // Ensure symmetry
        }
    }
    fclose(file); // Close the file

    if (city_count == 0) { // Check if no cities were found in the file
        fprintf(stderr, "Error: No data in the map.\n");
        return 1;
    }
    n = city_count; // Update the number of cities

    for (int i = 0; i < n; i++) { // Initialize distances for unconnected cities
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] == 0) {
                dist[i][j] = INT_MAX; // Set distance to INT_MAX if no direct path is specified
            }
        }
    }

    memset(visited, 0, sizeof(visited)); // Mark all cities as not visited
    current_tour[0] = 0; // Start the tour from the first city
    visited[0] = 1; // Mark the first city as visited
    tsp(0, 0, 1); // Start solving the TSP from the first city

    if (min_cost == INT_MAX) { // If no solution was found
        fprintf(stderr, "No solution found.\n");
        return 1;
    }

    // We print the best tour and its total cost
    printf("We will visit the cities in the following order:\n");
    for (int i = 0; i < n; i++) {
        printf("%s", cities[best_tour[i]].name); // Print the name of the city
        if (i < n - 1) {
            printf(" -(%d)-> ", dist[best_tour[i]][best_tour[i + 1]]); // Print the distance to the next city
        }
    }
    printf("\n");
    printf("Total cost: %lld\n", min_cost);

    // We free dynamically allocated memory for city names
    for (int i = 0; i < city_count; i++) {
        free(cities[i].name);
    }

    return 0;
}

// Recursive function to solve the Travelling Salesman Problem (TSP)
void tsp(int pos, int cost, int count) {
    if (count == n) { // If all cities have been visited
        if (cost < min_cost) { // Check if the current tour cost is the minimum
            min_cost = cost; // Update the minimum cost
            memcpy(best_tour, current_tour, sizeof(int) * n); // Copy current tour to best tour
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[pos][i] != INT_MAX) { // If the city is not visited and has a valid distance
            visited[i] = 1; // Mark the city as visited
            current_tour[count] = i; // Add the city to the current tour
            tsp(i, cost + dist[pos][i], count + 1); // Recursively visit the next city
            visited[i] = 0; // Unmark the city as visited
        }
    }
}

// Function to get the index of a city or add it if it does not exist
int get_city_index(char *city_name, int *city_count) {
    for (int i = 0; i < *city_count; i++) { // Loop through the cities array
        if (strcmp(city_name, cities[i].name) == 0) { // Check if the city already exists
            return i; // Return the index if the city is found
        }
    }
    
    if (*city_count < MAX_CITIES) { // If the city is not found, add it to the cities array
        cities[*city_count].name = malloc(strlen(city_name) + 1); // Allocate memory for the city name
        if (cities[*city_count].name == NULL) { // Check for memory allocation failure
            fprintf(stderr, "Memory allocation failed for city name.\n");
            exit(1);
        }
        strcpy(cities[*city_count].name, city_name); // Copy the city name to the array
        (*city_count)++; // Increment the city count
        return *city_count - 1; // Return the new index
    }
    return -1; // Return an error code if the city count exceeds the limit
}
