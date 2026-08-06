#!/bin/bash

echo "Enter the number of elements you want to store:"
read n

echo "Enter $n numbers (press Enter after each):"
sum=0

# Read the first element to initialize the array and the max value
read arr[0]
max=${arr[0]}
sum=$((sum + arr[0]))

# Loop to read the rest of the elements
for (( i=1; i<n; i++ ))
do
    read arr[$i]
    sum=$((sum + arr[$i]))
    
    # Check if current element is greater than max
    if [ ${arr[$i]} -gt $max ]; then
        max=${arr[$i]}
    fi
done

# Calculate average
average=$((sum / n))

echo "------------------------"
echo "Highest element: $max"
echo "Average of all elements: $average"
