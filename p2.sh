#!/bin/bash

read -p "Space দিয়ে সংখ্যাগুলো লিখো: " -a nums

min=${nums[0]}
sum=0
even=0

for x in "${nums[@]}"; do
    if (( x < min )); then
        min=$x
    fi

    (( sum += x ))

    if (( x % 2 == 0 )); then
        (( even++ ))
    fi
done

echo "সবচেয়ে ছোট: $min"
echo "যোগফল: $sum"
echo "জোড় সংখ্যার পরিমাণ: $even"