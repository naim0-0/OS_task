#include <stdio.h>

#define CHAIRS 3

int waiting_students = 0;
int ta_sleeping = 1;

void student_arrives(int id) {
    if (waiting_students == CHAIRS) {
        printf("Student %d found no empty chair and left.\n", id);
        return;
    }

    waiting_students++;
    printf("Student %d sits down (%d waiting).\n", id, waiting_students);

    if (ta_sleeping) {
        ta_sleeping = 0;
        printf("Student %d wakes up the TA.\n", id);
    }
}

void ta_helps_student(void) {
    if (waiting_students == 0) {
        ta_sleeping = 1;
        printf("No students are waiting. The TA sleeps.\n");
        return;
    }

    waiting_students--;
    printf("The TA helps a student (%d still waiting).\n", waiting_students);

    if (waiting_students == 0) {
        ta_sleeping = 1;
        printf("The TA goes back to sleep.\n");
    }
}

int main(void) {
    int students;

    printf("Enter number of arriving students: ");
    scanf("%d", &students);

    for (int i = 1; i <= students; i++) {
        student_arrives(i);
    }

    printf("\nTA starts helping students:\n");
    while (waiting_students > 0) {
        ta_helps_student();
    }

    return 0;
}
