#!/bin/bash

read -p "একটি সংখ্যা লিখো: " number

if [ "$number" -gt 0 ]; then
    echo "সংখ্যাটি positive"
elif [ "$number" -lt 0 ]; then
    echo "সংখ্যাটি negative"
elif [ "$number" -eq 0]; then
    echo "সংখ্যাটি zero"
else
    echo "invalid number"
    fi