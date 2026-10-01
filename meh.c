#include <stdio.h>

int room = 4;
int chopstick[5] = {1, 1, 1, 1, 1};

/* Take forks */
void take_fork(int i) {
  int right = (i + 1) % 5;

  // Check room
  if (room == 0) {
    printf("Philosopher %d is BLOCKED (Room Full).\n", i);
    return;
  }

  /* Enter room */
  room--;

  /* Check left chopstick */
  if (chopstick[i] == 0) {
    printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", i);
    return;
  }

  /* Take left chopstick */
  chopstick[i]--;

  /* Check right chopstick */
  if (chopstick[right] == 0) {
    /* Put back left chopstick because philosopher cannot eat */
    chopstick[i]++;

    printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", i);
    return;
  }

  /* Take right chopstick */
  chopstick[right]--;

  printf("Philosopher %d is EATING.\n", i);
}

/* Put forks */
void put_fork(int i) {
  int right = (i + 1) % 5;

  chopstick[i]++;
  chopstick[right]++;

  room++;
}

int main() {
  int M;
  int philosopher;

  /* Read number of events */
  scanf("%d", &M);

  /* Process each wake-up event */
  for (int i = 0; i < M; i++) {
    scanf("%d", &philosopher);

    take_fork(philosopher);
  }

  return 0;
}