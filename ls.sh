#!/bin/bash

read -p "Elements লিখো: " -a arr
read -p "কোন element খুঁজবে? " key

found=0

for i in "${!arr[@]}"; do
    if [ "${arr[i]}" = "$key" ]; then
        echo "$key পাওয়া গেছে। Index: $i"
        found=1
        break
    fi
done

if [ "$found" -eq 0 ]; then
    echo "$key পাওয়া যায়নি"
fi