#include <stdio.h>

#define CARS 2

int rider[CARS] = {-1, -1};

void request_ride(int passenger) {
    for (int car = 0; car < CARS; car++) {
        if (rider[car] == -1) {
            rider[car] = passenger;
            printf("Car %d leaves with passenger %d.\n", car, passenger);
            return;
        }
    }

    printf("Passenger %d is BLOCKED because no car is available.\n",
           passenger);
}

void return_car(int car) {
    if (car < 0 || car >= CARS) {
        printf("Invalid car number.\n");
        return;
    }

    if (rider[car] == -1) {
        printf("Car %d is already available.\n", car);
        return;
    }

    printf("Car %d returns with passenger %d.\n", car, rider[car]);
    rider[car] = -1;
}

int main(void) {
    int events, choice, id;

    printf("1 = passenger requests ride, 2 = car returns\n");
    printf("Enter number of events: ");
    scanf("%d", &events);

    for (int i = 0; i < events; i++) {
        scanf("%d %d", &choice, &id);

        if (choice == 1) {
            request_ride(id);
        } else if (choice == 2) {
            return_car(id);
        } else {
            printf("Invalid event.\n");
        }
    }

    return 0;
}
