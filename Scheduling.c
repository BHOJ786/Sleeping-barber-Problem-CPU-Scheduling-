#include<stdio.h> 
int main() 
{ 
  int cnt,j,n; //t_q is time quantum
  int tym,remain; // w_t is waiting time
  int fg=0,t_q=10; //t_a_t is turn around time
  int w_t=0,t_a_t=0,a_t[10],b_t[10],rt[10]; //a_t is arrival time
  printf("\n\nEnter Total number of Processes:\t "); //b_t is burst time 
  scanf("%d",&n); 
  remain=n; 
  for(cnt=0;cnt<n;cnt++) 
  { 
    printf("Enter Arrival time and Burst time for Process Process Number %d :",cnt+1); 
    scanf("%d",&a_t[cnt]); 
    scanf("%d",&b_t[cnt]); 
    rt[cnt]=b_t[cnt]; 
  } 
  printf("Enter time Quantum:%d\t",t_q); 

  printf("\n\nProcess\t|Turnaround Tym|Waiting Tym\n\n"); 
  for(tym=0,cnt=0;remain!=0;) 
  { 
    if(rt[cnt]<=t_q && rt[cnt]>0) 
    { 
      tym+=rt[cnt]; 
      rt[cnt]=0; 
      fg=1; 
    } 
    else if(rt[cnt]>0) 
    { 
      rt[cnt]-=t_q; 
      tym+=t_q; 
    } 
    if(rt[cnt]==0 && fg==1) 
    { 
      remain--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",cnt+1,tym-a_t[cnt],tym-a_t[cnt]-b_t[cnt]); 
      w_t+=tym-a_t[cnt]-b_t[cnt]; 
      t_a_t+=tym-a_t[cnt]; 
      fg=0; 
    } 
    if(cnt==n-1) 
      cnt=0; 
    else if(a_t[cnt+1]<=tym) 
      cnt++; 
    else 
      cnt=0; 
  } 
  printf("\nAverage Waiting Tym= %f\n",w_t*1.0/n); 
  printf("Avg Turnaround Tym = %f",t_a_t*1.0/n); 

  return 0; }
