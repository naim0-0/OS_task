#include <stdio.h>

int main(){
  int n=5;
  char name[][3]={"P1","P2","P3","P4","P5"};
  int bt[]={2,1,8,4,5};
  int priority[]={2,1,4,2,3};
  int idx[5]={0,1,2,3,4};

  // stable sort by priority descending (higher number = higher priority)
  for (int i=0; i<n-1; i++)
    for (int j=0; j<n-1-i; j++)
      if (priority[idx[j]]<priority[idx[j+1]]){
        int t=idx[j];
        idx[j]=idx[j+1];
        idx[j+1]=t;
      }

  int ct[5],tat[5],wt[5],time=0;
  printf("Gantt Chart: ");
  for (int i=0; i<n; i++){
    int p=idx[i];
    printf("| %s ",name[p]);
    time+=bt[p];
    ct[p]=time;
    tat[p]=ct[p];
    wt[p]=tat[p]-bt[p];
  }
  printf("|\n\n");

  printf("Process\tBT\tPriority\tCT\tTAT\tWT\n");
  float totalWT=0;
  for (int i=0; i<n; i++){
    int p=idx[i];
    printf("%s\t%d\t%d\t\t%d\t%d\t%d\n",name[p],bt[p],priority[p],ct[p],
           tat[p],wt[p]);
    totalWT+=wt[p];
  }
  printf("\nAverage Waiting Time = %.2f\n",totalWT/n);
  return 0;
}