#!/bin/bash

# 1. Declare an array where all elements are enclosed like "HELLO"
my_array=("HELLO" "WORLD" "OS" "LAB")

# 2. Add an element to this array using +=
my_array+=("BASH")

# 3. Print the number of elements and all array elements in one line
echo "Total elements: ${#my_array[@]} | All elements: ${my_array[@]}"

# 4. Print individual elements using an array index
echo "Element at index 0: ${my_array[0]}"
echo "Element at index 2: ${my_array[2]}"
echo "Element at index 4 (the newly added one): ${my_array[4]}"
