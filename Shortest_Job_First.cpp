//Shortest Job First Scheduling Algorithm in C

#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 20

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int total_around_time;
    int completion_time;
};

typedef struct process Process;

//global data members
double average_waiting_time;
int total_waiting_time;

double average_total_around_time;
int total__around_time;

//global member function
void given_table( Process p[],int n);
void sort_process_by_burst_time(Process p[], int n);
void calculate_completion_time(Process p[], int n);
void calculate_waiting_time(Process p[], int n);
void calculate_total_around_time(Process p[], int n);
void print_gantt_chart(Process p[], int n);
void table( Process p[],int n);
int main()
{
    Process p[MAX_PROCESS];
    int n, i, j;
    puts("\n\t\t\t::Shortest Job First Scheduling Algorithm::");
    puts("\t\t\t=======================================");

    printf("Enter total process: ");
    scanf("%d", &n);
    printf("Enter burst time for each process:\n");
    for(i=0; i<n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i+1;
    }
    printf("Enter arrival time for each process:\n");
    for(i=0; i<n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d", &p[i].arrival_time);
        p[i].pid = i+1;
    }
    given_table( p, n);
    
    sort_process_by_burst_time(p, n);
    calculate_completion_time(p, n);
   
    printf("\nGantt Chart:\n");    //gantt chart of compeletion
    print_gantt_chart(p, n);
    
    calculate_total_around_time(p, n);
    calculate_waiting_time(p, n);
    table( p, n);                   // final table formed
    average_total_around_time = (double) ( (double)total__around_time / (double) n );
    
  
    average_waiting_time = (double) ( (double)total_waiting_time / (double) n );

    puts("");
    printf("=> Average Total Around Time: %.2lf\n",average_total_around_time);
    printf("=> Average Waiting Time: %.2lf\n",average_waiting_time);



    return 0;
}

void given_table( Process p[],int n)
{
    printf("\n given Table below:");
    printf("\n\t _________ ____________ ____________");
    printf("\n\t| Process |Arrival Time| Burst Time |");
    
for(int i=0;i<n;i++)

{

printf("\n\t  p%d\t        %d            %d      ",p[i].pid,p[i].arrival_time,p[i].burst_time);

}
 printf("\n\t|_________|____________|____________|\n");
    
}

void sort_process_by_burst_time(Process p[], int n)
{
    int i, j ;
    Process temp;
    for(i=0; i<n-1; i++) {
        for(j=0; j<n-1-i; j++) {
            
            if(p[j].burst_time > p[j+1].burst_time) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
               
            }
        }
    }
}

void calculate_completion_time(Process p[], int n)
{
    int i;
   int total_completion_time = 0;
    //p[0].completion_time  = p[0].arrival_time;
    for(i=0; i<n; i++) {
        total_completion_time+=p[i].burst_time;
        p[i].completion_time = total_completion_time;
       
    }
}
void print_gantt_chart(Process p[], int n)
{
    int i, j;
    int last = p[n-1].burst_time + ( n== 1 ? 0 : p[n-1].completion_time);
    // printing top bar
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<8; j++) printf("--");
          printf(" ");
    }
    printf("\n|");
    // middle position
    for(i=0; i<n; i++) {
        for(j=0; j<8-1; j++) printf(" ");
        printf("p%d", p[i].pid);
        for(j=0; j<8-1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<8; j++) printf("--");
        printf(" ");
    }
    printf("\n");

     printf("%d \t\t ", 0);
    
    for(i=0; i<n; i++) {
       
        printf("%d \t\t ", p[i].completion_time);    // printing completion time
        
    }
}
    void calculate_total_around_time(Process p[], int n)
{
    int i;
    total__around_time = 0;
    
    for(i=0; i<n; i++) {
         p[i].total_around_time= abs(p[i].completion_time - p[i].arrival_time);
    
         total__around_time+=p[i].total_around_time;
    }

}
void calculate_waiting_time(Process p[], int n)
{
    int i;
    total_waiting_time = 0;
   
    for(i=0; i<n; i++) {
         p[i].waiting_time = 0;
        p[i].waiting_time =abs( p[i].total_around_time - p[i].burst_time);
        total_waiting_time += p[i].waiting_time;
    }
}

void table( Process p[],int n)
{  printf("\n\nTable formed below:");
    printf("\n\t _________ ____________ ____________ ________________ _____________");
    printf("\n\t| Process |Arrival Time| Burst Time | Turnaround Time| Waiting Time|");
    
for(int i=0;i<n;i++)

{

printf("\n\t  p%d\t        %d            %d          %d\t\t \t%d     ",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].total_around_time,p[i].waiting_time);

}
printf("\n\t|_________|____________|____________|________________|_____________|\n");
}
