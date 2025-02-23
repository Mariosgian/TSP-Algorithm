# Title of the project : Jabbamaps

## Description

The program reads a file that contains a map with the distances of all pairs of cities 
that we want to visit and it calculates the least cost path for us. It basically deals 
with the known Travelling Salesman Problem (TSP) problem. You can learn more about this 
program [here.](https://en.wikipedia.org/wiki/Travelling_salesman_problem)

## About the Program

### <b> The program consists of three (3) functions :
<u>

1. The main function

2. The tsp function
3. The get_city_index function
</u>

### <u> <b> More specifically: </b> </u>


### The main function :

The main function in this program is responsible for the overall execution flow of solving the Travelling Salesman Problem (TSP). It starts by checking if the correct number of arguments is provided, expecting a filename containing city distance data. If the input is wrong it prints the following message  showing the user the correct way to use the program :
```c
Usage: ./jabbamaps <filename>
```
 The file is opened for reading, and if it fails, an error message is displayed("Error opening the file"). The function then reads each line of the file, extracting city names and the distances between them. Using the get_city_index function, it assigns city indices and populates a distance matrix, ensuring symmetry by updating both directions (city1 to city2 and city2 to city1). After reading the entire file, the program checks if any cities were found. If not, it prints an error message("Error: No data in the map."). The function then sets up the distance matrix, marking unconnected cities with INT_MAX (a very very large number). The tour starts with the first city, and the tsp function is called to find the optimal route. If no solution is found, an error is reported("No solution found."). Otherwise, the optimal city tour is printed with the corresponding distances and total cost. Finally, the dynamically allocated memory for city names is freed, and the program ends, with exit code of 0 if nothing was gone wrong.

 ### The tsp function :

The tsp function is a recursive implementation of the Travelling Salesman Problem (TSP) designed to find the optimal path that visits all cities exactly once, while having least total travel cost. It takes three parameters: pos (the current city position), cost (the accumulated travel cost), and count (the number of cities visited so far). The function first checks if all cities have been visited (count == n). If so, it compares the current travel cost with the minimum cost found so far (min_cost). If the current cost is lower, it updates the min_cost and stores the current tour as the best solution. If not, all cities have been visited, the function iterates through each city, marking it as visited, adding it to the current tour, and recursively calling tsp to visit the next city. After exploring all possible routes from the current city, it backtracks by unmarking the city as visited and it continues exploring other possible tours. By using the function recusrsively the best solution is guaranteed to be found.

 ### The get_city_index function :

The get_city_index function is responsible for finding the index of a city in the cities array or adding it tp the array if it does not already exist. It first loops through the cities array and compares the provided city_name with each city's name stored in the array. If a match is found, it returns the index of the city. If no match is found and the total number of cities (city_count) is less than the maximum allowed (MAX_CITIES which is 64), the function allocates memory to store the city's name, copies the city name to the new memory location, and then increments the city count. The function then returns the index of the newly added city. If the city count exceeds the maximum limit, it returns -1 to indicate an error. With this we can be sure that the cities are unique in the array and the memory is always correctly allocated without having any problems.


## Running the program 

###  <u> Compilation </u>

In order to compile the program , you can use the following command :

```c
gcc -m32 -Ofast -Wall -Wextra -Werror -pedantic -o jabbamaps jabbamaps.c
```
### <u> Excecution </u>

To run the program, use the following command :

```c
./jabbamaps <filename>
````

Replace the 'filename' with the name of the input file containing city connections and distances.

## Examples

### Example with wrong input
 If the user provides more arguments than acceptable then the program will output the following message :

 ```c
Usage: ./jabbamaps <filename>
 ```

 Or if the user provides a wrong file or a file that doesnt contain anything, then the program shows him the following message :

 ```c
Error opening the file
 ```

 or this message depending on the situation :

 ```c
Error: No data in the map.
 ```
In both these situations the programs terminates with exit code of 1, which we can check by using the following command :

```c
$ echo $?
1
```

### Example Input file
 Lets a file named map4.txt containts the following data :

```c
Athens-Thessaloniki: 501
Athens-Ioannina: 422
Athens-Patras: 224
Patras-Thessaloniki: 468
Patras-Ioannina: 223
Thessaloniki-Ioannina: 261
````
If we run the following command :

```c
./jabbamaps map4.txt
```

then after the execution, the program will print:

1. The order in which cities should be visited.
2. The distance between each pair of consecutive cities.
3. The total cost of the optimal route.

<br>
<b>like this :</b>

<br>

</b>

```c
We will visit the cities in the following order:
Athens -(224)-> Patras -(223)-> Ioannina -(261)-> Thessaloniki
Total cost: 708
````

Another example :

If the file map7.txt contains the following data :
```c
 Athens-Thessaloniki: 501
Athens-Ioannina: 422
Athens-Patras: 224
Patras-Thessaloniki: 468
Patras-Ioannina: 223
Thessaloniki-Ioannina: 261
Amfissa-Patras: 122
Athens-Amfissa: 211
Ioannina-Amfissa: 316
Amfissa-Thessaloniki: 360
Volos-Amfissa: 189
Volos-Thessaloniki: 211
Athens-Volos: 328
Ioannina-Volos: 246
Volos-Patras: 307
Trikala-Volos: 123
Trikala-Thessaloniki: 213
Trikala-Athens: 316
Trikala-Amfissa: 175
Trikala-Ioannina: 128
Trikala-Patras: 295
```

then the output will be like this if we use the followig command :

```c
./jabbamaps map7.txt
```
### Output

```c
Athens -(211)-> Amfissa -(122)-> Patras -(223)-> Ioannina -(128)-> Trikala -(123)-> Volos -(211)-> Thessaloniki
Total cost: 1018
```








