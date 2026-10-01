#include <stdio.h>

#define SLICES_PER_PIZZA 4

int slices = 0;
int pizzas_ordered = 0;

void deliver_pizza(void) {
    slices = SLICES_PER_PIZZA;
    pizzas_ordered++;
    printf("Delivery brings pizza %d with %d slices.\n",
           pizzas_ordered, SLICES_PER_PIZZA);
}

void student_takes_slice(int id) {
    if (slices == 0) {
        printf("Student %d finds an empty box and orders a pizza.\n", id);
        deliver_pizza();
    }

    slices--;
    printf("Student %d takes a slice (%d left).\n", id, slices);
}

int main(void) {
    int requests, student;

    printf("Enter number of slice requests: ");
    scanf("%d", &requests);

    printf("Enter the student number for each request:\n");
    for (int i = 0; i < requests; i++) {
        scanf("%d", &student);
        student_takes_slice(student);
    }

    printf("Total pizzas ordered = %d\n", pizzas_ordered);
    return 0;
}
