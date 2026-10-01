#include <stdio.h>

int main() {
  int n=5;
  int bt[]={2,1,8,4,5}; // P1..P5
  char name[][3]={"P1","P2","P3","P4","P5"};
  int ct[5],tat[5],wt[5];
  int time=0;

  printf("Gantt Chart: ");
  for (int i=0; i<n; i++) {
    printf("| %s ",name[i]);
    time+=bt[i];
    ct[i]=time;
    tat[i]=ct[i]; // arrival time=0
    wt[i]=tat[i]-bt[i];
  }
  printf("|\n\n");

  printf("Process\tBT\tCT\tTAT\tWT\n");
  float totalWT=0;
  for (int i=0; i<n; i++) {
    printf("%s\t%d\t%d\t%d\t%d\n",name[i],bt[i],ct[i],tat[i],wt[i]);
    totalWT+=wt[i];
  }
  printf("\nAverage Waiting Time = %.2f\n",totalWT/n);
  return 0;
}
