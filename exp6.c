#include <stdio.h>
#define MAX 20
#define Q 3

int main() {
    int n, i, t;
    int pid[MAX], at[MAX], bt[MAX], pr[MAX];
    int ct[MAX], tat[MAX], wt[MAX], rt[MAX];
    float avg;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: "); scanf("%d", &at[i]);
        printf("Burst Time: "); scanf("%d", &bt[i]);
        printf("Priority: "); scanf("%d", &pr[i]);
    }

    // FCFS
    t = 0; avg = 0;
    printf("\n FCFS Scheduling \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        if (t < at[i]) t = at[i];
        ct[i] = t + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg += wt[i];
        t = ct[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    float fcfs_avg = avg / n;
    printf("Average Waiting Time of FCFS = %.2f\n",  fcfs_avg );

    // SJF Non-preemptive
    int done[MAX] = {0}, count = 0;
    t = 0; avg = 0;
    printf("\n SJF (Non-Preemptive) \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    while (count < n) {
        int idx = -1, min = 9999;
        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= t && bt[i] < min) {
                min = bt[i];
                idx = i;
            }
        }
        if (idx == -1) {
            t++;
        } else {
            ct[idx] = t + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avg += wt[idx];
            t = ct[idx];
            done[idx] = 1;
            count++;
        }
    }
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    float sjf_avg = avg / n;
    printf("Average Waiting Time of SJF= %.2f\n", sjf_avg);

    // Priority Non-preemptive
    for (i = 0; i < n; i++) done[i] = 0;
    count = 0; t = 0; avg = 0;
    printf("\nPriority Scheduling \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    while (count < n) {
        int idx = -1, high = -1;
        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= t && pr[i] > high) {
                high = pr[i];
                idx = i;
            }
        }
        if (idx == -1) {
            t++;
        } else {
            ct[idx] = t + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avg += wt[idx];
            t = ct[idx];
            done[idx] = 1;
            count++;
        }
    }
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    float priority_avg = avg / n;
    printf("Average Waiting Time of Priority Scheduling= %.2f\n", priority_avg);

    // Round Robin
    for (i = 0; i < n; i++) rt[i] = bt[i];
    t = 0; count = 0; avg = 0;
    printf("\n Round Robin (Quantum = 3) \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    while (count < n) {
        int idle = 1;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= t) {
                idle = 0;
                if (rt[i] > Q) {
                    t += Q;
                    rt[i] -= Q;
                } else {
                    t += rt[i];
                    ct[i] = t;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    avg += wt[i];
                    rt[i] = 0;
                    count++;
                }
            }
        }
        if (idle) t++;
    }
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    float rr_avg = avg / n;
    printf("Average Waiting Time of RR= %.2f\n", rr_avg);


// minimum value among all averages
    float min_avg = fcfs_avg;
    if (sjf_avg < min_avg) min_avg = sjf_avg;
    if (priority_avg < min_avg) min_avg = priority_avg;
    if (rr_avg < min_avg) min_avg = rr_avg;

    
    printf("\nMinimum Average Waiting Time: %.2f", min_avg);
    printf("\nAlgorithm with minimum average waiting time is: \n");

    
    if (fcfs_avg == min_avg) 
        printf("- FCFS\n");
    if (sjf_avg == min_avg) 
        printf("- SJF (Non-Preemptive)\n");
    if (priority_avg == min_avg) 
        printf("- Priority scheduling\n");
    if (rr_avg == min_avg) 
        printf("- Round Robin (Q=3)\n");
    
    
    return 0;
}
