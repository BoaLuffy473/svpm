#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct {
    int process_id;  
    int arrival_time;  
    int burst_time;    
    int remaining_time; 
    int completion_time;
    int turn_around_time; 
    int waiting_time; 
} Process;


void sjf_preemptive(Process processes[], int n) {
    int time = 0; 
    int completed = 0; 
    int min_index; 

    
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nSJF (Preemptive) Scheduling:\n");
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    
    while (completed < n) {
        min_index = -1;
        int min_remaining_time = 9999;
        
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                min_index = i;
            }
        }
        
        if (min_index == -1) {
            time++;
            continue;
        }
        
        processes[min_index].remaining_time--;
        time++;

        if (processes[min_index].remaining_time == 0) {
            processes[min_index].completion_time = time;
            processes[min_index].turn_around_time = processes[min_index].completion_time - processes[min_index].arrival_time;
            processes[min_index].waiting_time = processes[min_index].turn_around_time - processes[min_index].burst_time;
            completed++;
        }
    }

    float total_turnaround = 0, total_waiting = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);
        total_turnaround += processes[i].turn_around_time;
        total_waiting += processes[i].waiting_time;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
}

void round_robin(Process processes[], int n, int quantum) {
    int time = 0;
    int completed = 0;
    int i;
    
    int queue[MAX];
    int front = 0, rear = 0;

    for (i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > quantum) {
                    processes[i].remaining_time -= quantum;
                    time += quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = time;
                    processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
                    completed++;
                }
            }
        }
    }

    float total_turnaround = 0, total_waiting = 0;
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);
        total_turnaround += processes[i].turn_around_time;
        total_waiting += processes[i].waiting_time;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
}

int main() {
    int n, quantum;
    Process processes[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    printf("\nEnter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    sjf_preemptive(processes, n);

    round_robin(processes, n, quantum);

    return 0;
}

