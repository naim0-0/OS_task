#include <stdio.h>

int main() {
    int n, i;
    int sum = 0, max;
    float average;
    int arr[100]; // Assuming a maximum of 100 elements for simplicity

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum = sum + arr[i]; // Add to total sum
    }

    // Assume the first element is the highest to start
    max = arr[0];

    // Loop through the array to find the actual highest element
    for(i = 1; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    // Calculate the average (casting sum to float for decimal precision)
    average = (float)sum / n;

    printf("------------------------\n");
    printf("Highest element: %d\n", max);
    printf("Average: %.2f\n", average);

    return 0;
}
