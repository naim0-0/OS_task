#include <stdio.h>
int room=4;
int chopstick[5]={1,1,1,1,1};

void take_fork(int i)
{
    if (room==0){
        printf("Philosopher %d is BLOCKED (Room Full).\n", i);
        return;
    }

    room--;

    if (chopstick[i]==0){
        printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", i);
        return;
    }

    chopstick[i]--;

    if (chopstick[(i+1)%5]==0){
        printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", i);
        return;
    }

    chopstick[(i+1)%5]--;

    printf("Philosopher %d is EATING.\n", i);
}

void put_fork(int i){
    chopstick[i]++;
    chopstick[(i+1)%5]++;
    room++;
}

int main(){

    int M, philosopher;

    scanf("%d",&M);
    for (int i=0;i<M;i++){
        
        scanf("%d",&philosopher);

        take_fork(philosopher);
    }

    return 0;
}