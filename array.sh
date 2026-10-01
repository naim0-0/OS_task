#!/bin/bash

fruits=("apple" "banana" "cherry" "mango")

fruits+=("orange")

unset 'fruits[1]'

echo "সব elements: ${fruits[@]}" 
echo "সব indices: ${!fruits[@]}"
echo "Element সংখ্যা: ${#fruits[@]}"
echo "দুইটি element-এর slice: ${fruits[@]:1:2}"
echo "fruits[2]-এর দৈর্ঘ্য: ${#fruits[2]}"