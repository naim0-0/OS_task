#include <stdio.h>

int main() {
  int n=5,quantum=2;
  char name[][3]={"P1","P2","P3","P4","P5"};
  int bt[]={2,1,8,4,5};
  int rem[5];
  for (int i=0; i<n; i++)
    rem[i]=bt[i];

  int queue[100],front=0,rear=0;
  for (int i=0; i<n; i++)
    queue[rear++]=i;

  int ct[5],time=0;
  printf("Gantt Chart: ");

  while (front<rear) {
    int p=queue[front++];
    if (rem[p]==0)
      continue;

    int run=(rem[p]>quantum) ? quantum : rem[p];
    printf("| %s ",name[p]);
    time+=run;
    rem[p]-=run;

    if (rem[p]>0)
      queue[rear++]=p; // send to back of queue
    else
      ct[p]=time; // process finished
  }
  printf("|\n\n");

  printf("Process\tBT\tCT\tTAT\tWT\n");
  float totalWT=0;
  for (int i=0; i<n; i++) {
    int tat=ct[i]; // arrival time=0
    int wt=tat-bt[i];
    printf("%s\t%d\t%d\t%d\t%d\n",name[i],bt[i],ct[i],tat,wt);
    totalWT+=wt;
  }
  printf("\nAverage Waiting Time = %.2f\n",totalWT/n);
  return 0;
}