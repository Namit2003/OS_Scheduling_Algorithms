#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_processes(const char *filename)
{
  FILE *file = fopen(filename, "r");
  int count = 1;
  char c;
  if (file)
  {
    while ((c = getc(file)) != EOF)
    {
      if (c == '\n')
      {
        count++;
      }
    }
    fclose(file);
  }
  else
  {
    printf("File not found!\n");
  }
  return count;
}
void FCFS()
{
  int n;
  int time = 0;
  char time_unit[7];
  float avg_waiting = 0, avg_tat = 0;
  FILE *fp;
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening file!!!");
  }
  else
  {
    n = count_processes("input.txt") - 1;
    fscanf(fp, "%s", &time_unit);
    int process[n];
    int waiting[n], turnaround[n], arrival[n],
        burst[n];
    for (int a = 0; a < n; a++)
    {
      fscanf(fp, "%d %d", &arrival[a],
             &burst[a]);
    }
    fclose(fp);
    waiting[0] = 0;
    turnaround[0] = burst[0];
    fp = fopen("output.txt", "w");
    for (int a = 1; a < n; a++)
    {
      int sum = 0;
      for (int b = 0; b < a; b++)
        sum += burst[b];
      waiting[a] = sum - arrival[a];
      if (waiting[a] < 0)
        waiting[a] = 0;
      turnaround[a] = waiting[a] + burst[a];
    }
    for (int a = 0; a < n; a++)
    {
      avg_waiting += waiting[a];
      avg_tat += turnaround[a];
    }
    avg_waiting /= n;
    avg_tat /= n;
fprintf(fp, "Average Waiting Time is: %0.2f%s", avg_waiting, time_unit);
fprintf(fp, "\nAverage Turnaround Time: %0.2f%s", avg_tat, time_unit);
fprintf(fp, "\nGantt Chart:\n");
fprintf(fp, "|");
for (int a = 0; a < n; a++)
{
      for (int b = 0; b < burst[a]; b++)
      {
        fprintf(fp, "P%d|", a + 1);
        time++;
      }
}
fclose(fp);
  }
  printf("\n");
}
void SJF()
{
  int n, smallest, time = 0, completed = 0;
  char time_unit[7];
  float avg_waiting = 0, avg_tat = 0;
  FILE *fp;
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening file!!!");
  }
  else
  {
    n = count_processes("input.txt") - 1;
    fscanf(fp, "%s", &time_unit);
    int burst[n], waiting[n], turnaround[n],
        arrival[n], remaining[n];
    for (int a = 0; a < n; a++)
    {
      fscanf(fp, "%d %d", &arrival[a],
             &burst[a]);
      remaining[a] = burst[a];
    }
    fclose(fp);
    fp = fopen("output.txt", "w");
    fprintf(fp, "Gantt Chart:\n");
    while (completed != n)
    {
      smallest = -1;
      for (int a = 0; a < n; a++)
      {
        if (remaining[a] > 0 && (smallest == -1 || remaining[a] < remaining[smallest]) &&
            arrival[a] <= time)
        {
          smallest = a;
        }
      }
      if (smallest == -1)
      {
        fprintf(fp, "| idle ");
        time++;
      }
      else
      {
        fprintf(fp, "| P%d ", smallest + 1);
        remaining[smallest]--;
        time++;
        if (remaining[smallest] == 0)
        {
          completed++;
          waiting[smallest] = time -
                              arrival[smallest] - burst[smallest];
          if (waiting[smallest] < 0)
            waiting[smallest] = 0;
          turnaround[smallest] =
              waiting[smallest] + burst[smallest];
        }
      }
    }
    fprintf(fp, "|\n");
    for (int a = 0; a < n; a++)
    {
      avg_waiting += waiting[a];
      avg_tat += turnaround[a];
    }
    fprintf(fp, "Average Waiting Time: %.2f %s\n",
            avg_waiting / n, time_unit);
fprintf(fp, "Average Turnaround Time: %.2f%s\n", avg_tat / n, time_unit);
fclose(fp);
  }
  printf("\n");
}
void RRS()
{
  int n;
  float avg_waiting = 0, avg_tat = 0;
  char time_unit[7];
  FILE *fp;
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening file!!!");
  }
  else
  {
    n = count_processes("input.txt") - 1;
    fscanf(fp, "%s", &time_unit);
    printf("Number of processes: %d\n", n);
    int burst[n], waiting[n], turnaround[n],
        arrival[n], time_quantum, remaining[n], time = 0,
                                                completed = 0, flag;
    for (int a = 0; a < n; a++)
    {
      fscanf(fp, "%d %d", &arrival[a],
             &burst[a]);
printf("Process %d Arrival Time: %d BurstTime: %d\n", a + 1, arrival[a], burst[a]);
remaining[a] = burst[a];
    }
    fclose(fp);
    fp = fopen("output.txt", "w");
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    fprintf(fp, "Gantt Chart:\n");
    while (completed != n)
    {
      flag = 0;
      for (int a = 0; a < n; a++)
      {
        if (remaining[a] > 0 && arrival[a] <=
                                    time)
        {
          if (remaining[a] <= time_quantum)
          {
            fprintf(fp, "| P%d ", a + 1);
            time += remaining[a];
            remaining[a] = 0;
            completed++;
            waiting[a] = time - arrival[a] - burst[a];
            if (waiting[a] < 0)
              waiting[a] = 0;
            turnaround[a] = waiting[a] +
                            burst[a];
          }
          else
          {
            fprintf(fp, "| P%d ", a + 1);
            remaining[a] -= time_quantum;
            time += time_quantum;
          }
          flag = 1;
        }
      }
      if (flag == 0)
      {
        fprintf(fp, "| idle ");
        time++;
      }
    }
    fprintf(fp, "|\n");
    for (int a = 0; a < n; a++)
    {
      avg_waiting += waiting[a];
      avg_tat += turnaround[a];
    }
    fprintf(fp, "Average Waiting Time: %.2f %s\n",
            avg_waiting / n, time_unit);
fprintf(fp, "Average Turnaround Time: %.2f%s\n", avg_tat / n, time_unit);
fclose(fp);
  }
  printf("\n");
}
void PS()
{
  int n;
  float avg_waiting = 0, avg_tat = 0;
  char time_unit[7];
  FILE *fp;
  fp = fopen("priority.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening file!!!");
  }
  else
  {
    n = count_processes("input.txt") - 1;
    fscanf(fp, "%s", &time_unit);
    int burst[n], priority[n], waiting[n],
        turnaround[n], arrival[n], temp, min, time = 0,
                                              completed = 0;
    for (int a = 0; a < n; a++)
    {
      fscanf(fp, "%d %d %d", &arrival[a],
             &burst[a], &priority[a]);
    }
    fclose(fp);
    fp = fopen("output.txt", "w");
    for (int a = 0; a < n - 1; a++)
    {
      min = a;
      for (int b = a + 1; b < n; b++)
      {
        if (priority[b] < priority[min])
          min = b;
      }
      temp = priority[a];
      priority[a] = priority[min];
      priority[min] = temp;
      temp = burst[a];
      burst[a] = burst[min];
      burst[min] = temp;
      temp = arrival[a];
      arrival[a] = arrival[min];
      arrival[min] = temp;
    }
    fprintf(fp, "Gantt Chart:\n");
    fprintf(fp, "0");
    for (int a = 0; a < n; a++)
    {
      time += burst[a];
      turnaround[a] = time - arrival[a];
      waiting[a] = turnaround[a] - burst[a];
      avg_waiting += waiting[a];
      avg_tat += turnaround[a];
      fprintf(fp, " | P%d | %d", a + 1, time);
    }
    fprintf(fp, "\n");
    fprintf(fp, "Average Waiting Time: %.2f %s\n",
            avg_waiting / n, time_unit);
fprintf(fp, "Average Turnaround Time: %.2f%s\n", avg_tat / n, time_unit);
fclose(fp);
  }
  printf("\n");
}
void SRTF()
{
  int n;
  float avg_waiting = 0, avg_tat = 0;
  char time_unit[7];
  FILE *fp;
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening file!!!");
  }
  else
  {
    n = count_processes("input.txt") - 1;
    int burst[n], remaining[n], waiting[n],
        turnaround[n], arrival[n], time = 0, completed = 0,
                                   min_index;
    fscanf(fp, "%s", &time_unit);
    for (int a = 0; a < n; a++)
    {
      fscanf(fp, "%d %d", &arrival[a],
             &burst[a]);
      remaining[a] = burst[a];
    }
    fclose(fp);
    fp = fopen("output.txt", "w");
    fprintf(fp, "Gantt Chart:\n");
    fprintf(fp, "0");
    while (completed != n)
    {
      min_index = -1;
      for (int a = 0; a < n; a++)
      {
        if (arrival[a] <= time && remaining[a] > 0)
        {
          if (min_index == -1)
          {
            min_index = a;
          }
          else if (remaining[a] <
                   remaining[min_index])
          {
            min_index = a;
          }
        }
      }
      if (min_index != -1)
      {
        remaining[min_index]--;
        time++;
        if (remaining[min_index] == 0)
        {
          completed++;
          turnaround[min_index] = time -
                                  arrival[min_index];
          waiting[min_index] =
              turnaround[min_index] - burst[min_index];
          avg_waiting += waiting[min_index];
          avg_tat += turnaround[min_index];
          fprintf(fp, " | P%d | %d",
                  min_index + 1, time);
        }
      }
      else
      {
        time++;
      }
    }
    fprintf(fp, "\n");
    fprintf(fp, "Average Waiting Time: %.2f %s\n",
            avg_waiting / n, time_unit);
fprintf(fp, "Average Turnaround Time: %.2f%s\n", avg_tat / n, time_unit);
fclose(fp);
  }
  printf("\n");
}
void LRTF()
{
  int n;
  float avg_waiting = 0, avg_tat = 0;
  char time_unit[7];
  FILE *fp;
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening file!!!");
  }
  else
  {
    n = count_processes("input.txt") - 1;
    int burst[n], remaining[n], waiting[n],
        turnaround[n], arrival[n], time = 0, completed = 0,
                                   max_index, max_value = -1;
    fscanf(fp, "%s", &time_unit);
    for (int a = 0; a < n; a++)
    {
      fscanf(fp, "%d %d", &arrival[a],
             &burst[a]);
      remaining[a] = burst[a];
    }
    fclose(fp);
    fp = fopen("output.txt", "w");
    fprintf(fp, "Gantt Chart:\n");
    fprintf(fp, "0");
    while (completed != n)
    {
      max_value = -1;
      for (int a = 0; a < n; a++)
      {
        if (arrival[a] <= time && remaining[a] > max_value)
        {
          max_value = remaining[a];
          max_index = a;
        }
      }
      if (max_value != -1)
      {
        remaining[max_index]--;
        time++;
        if (remaining[max_index] == 0)
        {
          completed++;
          turnaround[max_index] = time -
                                  arrival[max_index];
          waiting[max_index] =
              turnaround[max_index] - burst[max_index];
          avg_waiting += waiting[max_index];
          avg_tat += turnaround[max_index];
          fprintf(fp, " | P%d | %d",
                  max_index + 1, time);
        }
      }
      else
      {
        time++;
      }
    }
    fprintf(fp, "\n");
    fprintf(fp, "Average Waiting Time: %.2f %s\n",
            avg_waiting / n, time_unit);
fprintf(fp, "Average Turnaround Time: %.2f%s\n", avg_tat / n, time_unit);
fclose(fp);
  }
  printf("\n");
}
int main()
{
  int choice;
st:
printf("1. First-Come First-Served \n2. ShortestJob First \n3. Round Robin Scheduling \n4.PriorityScheduling\n5. Shortest Remaining Time First \n6.Longest remaining time first \n7. Exit");
printf("\nEnter choice: ");
scanf("%d", &choice);
switch (choice)
{
  case 1:
  {
    FCFS();
    goto st;
  }
  case 2:
  {
    SJF();
    goto st;
  }
  case 3:
  {
    RRS();
    goto st;
  }
  case 4:
  {
    PS();
    goto st;
  }
  case 5:
  {
    SRTF();
    goto st;
  }
  case 6:
  {
    LRTF();
    goto st;
  }
  case 7:
  {
    return 0;
  }
  default:
  {
    printf("Enter valid choice!!!");
    goto st;
  }
}
}
